#include "qsquare.h"
#include "qboard.h"
#include "gui.h"
#include <iostream>

using namespace stratego;
using namespace std;

QBoard::QBoard(QController &controller, Game &game, QWidget * parent)
    : QWidget {parent}, game_ {game}, controller_ {controller}, selectedPawn_ {} {
    QVBoxLayout * container = new QVBoxLayout();
    QWidget * board = new QWidget();
    message_ = new QLabel();
    message_->setText("");
    message_->setStyleSheet("color: red; "
                            "font-size: 20px;");
    message_->setAlignment(Qt::AlignCenter);
    container->addWidget(message_);
    board_ = new QGridLayout();
    board_->setContentsMargins(0,0,0,0);
    board_->setSpacing(1);
    board->setLayout(board_);
    container->addWidget(board);
    setLayout(container);
    initialize();
    updateBoard();
    parent->setWindowTitle("Play");
    static_cast<QView *>(parent)->addBackgroundColor();
}

void QBoard::clicked_on_pawn(QPawn * pawn) {
    if(message_->isVisible()) {
        message_->setText("");
    }
    if(selectedPawn_ != nullptr) {
        if(selectedPawn_->getColor() != pawn->getColor()) {
            if(selectedPawn_->getRole() == SCOUT) {
                moveScout(pawn->getPosition());
            } else {
                if(isNeighbor(selectedPawn_->getPosition(), pawn->getPosition())) {
                    Direction direction = deduceDirection(selectedPawn_->getPosition(), pawn->getPosition());
                    Position pos {selectedPawn_->getPosition().getX(), selectedPawn_->getPosition().getY()};
                    controller_.move(pos, direction);
                    selectedPawn_ = nullptr;
                } else {
                    displayMessage("Pawn is not your neighbor");
                    selectedPawn_ = nullptr;
                }
            }
        } else {
            displayMessage("Can't attack your own pawn");
            selectedPawn_ = nullptr;
        }
    } else {
        if(game_.getCurrentPlayer() == pawn->getColor()) {
            if(pawn->getRole() != FLAG && pawn->getRole() != BOMB) {
                selectedPawn_ = pawn;
            } else {
                displayMessage("Can't select BOMB or FLAG");
                selectedPawn_ = nullptr;
            }
        } else {
            displayMessage("Can't select enemy pawn");
            selectedPawn_ = nullptr;
        }
    }
}

void QBoard::clicked_on_square(Position position) {
    if(selectedPawn_ != nullptr) {
        if((!isNeighbor(selectedPawn_->getPosition(), position) && (selectedPawn_->getRole() != SCOUT))
                || game_.isWater(position)) {
            selectedPawn_ = nullptr;
        } else if(selectedPawn_->getRole() == SCOUT) {
            moveScout(position);
        } else {
            Direction direction = deduceDirection(selectedPawn_->getPosition(), position);
            Position pos {selectedPawn_->getPosition().getX(), selectedPawn_->getPosition().getY()};
            controller_.move(pos, direction);
            selectedPawn_ = nullptr;
        }
    }
}

void QBoard::updateBoard() {
    bool hide = (game_.getLevel() == 1) ? false : true;
    if(board_->count() != 0) {
        clearBoard();
        initialize();
    }
    for(unsigned row = 0; row < game_.getPawns().size(); row++) {
        for(unsigned column = 0; column < game_.getPawns()[row].size(); column++) {
            optional<Pawn> pawn = game_.getPawns()[row][column];
            if(pawn->isValide() && !game_.isWater(Position(row, column))) {
                if(game_.getCurrentPlayer() == pawn->getColor()) {
                    QPawn * qpawn = new QPawn(pawn->getColor(), pawn->getRole(), pawn->getPosition(), false);
                    connect(qpawn, SIGNAL(clicked(stratego::QPawn*)), this, SLOT(clicked_on_pawn(stratego::QPawn*)));
                    board_->addWidget(qpawn, row, column);
                } else {
                    QPawn * qpawn = new QPawn(pawn->getColor(), pawn->getRole(), pawn->getPosition(), hide);
                    connect(qpawn, SIGNAL(clicked(stratego::QPawn*)), this, SLOT(clicked_on_pawn(stratego::QPawn*)));
                    board_->addWidget(qpawn, row, column);
                }
            }
        }
    }
}

void QBoard::initialize() {
    QSquare * square;
    for(unsigned row = 0; row < 10; row++) {
        for(unsigned column = 0; column < 10; column++) {
            if(game_.isWater(Position(row, column))) {
                square = new QSquare("water", Position(row,column));
            } else {
                square = new QSquare("grass", Position(row,column));
            }
            connect(square, SIGNAL(clicked(stratego::Position)), this, SLOT(clicked_on_square(stratego::Position)));
            board_->addWidget(square, row, column);
        }
    }
}

Direction QBoard::deduceDirection(Position initial, Position next) {
    Position pos {initial.getX(), initial.getY()};
    Position up {pos.getX() - 1, pos.getY()};
    Position right {pos.getX(), pos.getY() + 1};
    Position left {pos.getX(), pos.getY() - 1};
    Position down {pos.getX() + 1, pos.getY()};
    if(next == up) {
        return FORWARD;
    } else if(next == down) {
        return BACKWARD;
    } else if(next == left) {
        return LEFT;
    } else {
        return RIGHT;
    }
}

void QBoard::moveScout(Position position) {
    Position pos {selectedPawn_->getPosition().getX(), selectedPawn_->getPosition().getY()};
    Pawn qpawn {selectedPawn_->getRole(), selectedPawn_->getColor(), selectedPawn_->getPosition(), true};
    // if the both pawns are in the same X axis
    if(selectedPawn_->getPosition().getX() == position.getX()) {
        // deduces the distance between both
        int moves = selectedPawn_->getPosition().getY() - position.getY();
        // if positive value -> mean that it is left else right
        if(moves > 0) {
            Direction direction = Direction::LEFT;
            if(game_.canScoutMove(qpawn, direction, moves)) {
                controller_.move(pos, direction, moves);
            }
        } else {
            Direction direction = Direction::RIGHT;
            if(game_.canScoutMove(qpawn, direction, moves)) {
                controller_.move(pos, direction, moves);
            }
        }
        selectedPawn_ = nullptr;
        // if the both pawns are in the same Y axis
    } else if(selectedPawn_->getPosition().getY() == position.getY()) {
        // deduces the distance between both
        int moves = selectedPawn_->getPosition().getX() - position.getX();
        // if positive value -> mean that it is forward else backward
        if(moves > 0) {
            Direction direction = Direction::FORWARD;
            if(game_.canScoutMove(qpawn, direction, moves)) {
                controller_.move(pos, direction, moves);
            }
        } else {
            Direction direction = Direction::BACKWARD;
            if(game_.canScoutMove(qpawn, direction, moves)) {
                controller_.move(pos, direction, moves);
            }
        }
        selectedPawn_ = nullptr;
    } else {
        displayMessage("Scout can't go there");
    }
}

bool QBoard::isNeighbor(Position first, Position second) {
    Position up {first.getX() - 1, first.getY()};
    Position right {first.getX(), first.getY() + 1};
    Position left {first.getX(), first.getY() - 1};
    Position down {first.getX() + 1, first.getY()};
    return (second == up) || (second == right)
            || (second == left) || (second == down);
}

void QBoard::clearBoard() {
    while(board_->count() != 0) {
        QLayoutItem * item = board_->itemAt(0);
        if(item->widget()) {
            delete item->widget();
        }
    }
}

void QBoard::displayMessage(QString message) {
    message_->setText(message);
    message_->show();
}
