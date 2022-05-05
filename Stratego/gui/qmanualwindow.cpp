#include <QMessageBox>

#include "qmanualwindow.h"
#include "qsquare.h"

using namespace stratego;
using namespace std;

QManualWindow::QManualWindow(Game &game, Color player, QWidget * parent)
    : QWidget {parent}, player_ {player}, game_ {game}, selectedPawn_ {} {
    placedPawns_ = 0;
    player_ = (game_.getState() == RED_TURN) ? RED : BLUE;
    QVBoxLayout * menu = new QVBoxLayout();
    QHBoxLayout * container = new QHBoxLayout();
    title_ = new QLabel("Initializiation manually");
    title_->setAlignment(Qt::AlignCenter);
    menu->addWidget(title_);
    pawns_ = new QGridLayout();
    pawns_->setAlignment(Qt::AlignCenter);
    populatePawns(pawns_);
    menu->addLayout(pawns_);
    squares_ = new QGridLayout();
    squares_->setAlignment(Qt::AlignCenter);
    squares_->setContentsMargins(0,0,0,0);
    squares_->setSpacing(1);
    populateSquare(squares_);
    menu->addLayout(squares_);
    submit_ = new QPushButton("Submit");
    submit_->setFixedSize(200,50);
    connect(submit_, SIGNAL(clicked()), this, SLOT(addManualBoard()));
    container->addWidget(submit_);
    container->setAlignment(Qt::AlignCenter);
    menu->addLayout(container);
    setLayout(menu);
    adjustSize();
    parent->setWindowTitle("Initializing the game board manually");
}

void QManualWindow::addManualBoard() {
    if(placedPawns_ >= 40) {
        emit submit();
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"Incomplete board","There are still pawns to place");
        messageBox.adjustSize();
    }
}

void QManualWindow::populatePawns(QGridLayout * pawns) {
    game_.initPawns();
    map<Role, int> mapPawn = game_.getRemainingPawns();
    map<Role, int>::iterator index;
    int column = 0;
    for(index = mapPawn.begin(); index != mapPawn.end(); ++index) {
        while(game_.isAvailable(index->first)) {
            game_.decrementPawnCount(index->first);
            QPawn * pawn = new QPawn(player_, index->first, Position(0, column), false, this);
            pawns->addWidget(pawn, 0, column);
            connect(pawn, SIGNAL(clicked(stratego::QPawn*)), this, SLOT(on_pawns(stratego::QPawn*)));
        }
        column++;
    }
    game_.initPawns();
}

void QManualWindow::populateSquare(QGridLayout * squares) {
    int row = player_ == BLUE ? 0 : 6;
    int length = player_ == BLUE ? 4 : 10;
    while(row < length) {
        for(int column = 0; column < 10; column++) {
            QSquare * square = new QSquare("grass", Position(row, column), this);
            squares->addWidget(square, row, column);
            connect(square, SIGNAL(clicked(stratego::Position)), this, SLOT(on_squares(stratego::Position)));
        }
        row++;
    }
}

void QManualWindow::on_pawns(QPawn * pawn) {
    if(pawn->isSelectable()) {
        placedPawns_ += 1;
        selectedPawn_ = pawn;
    }
}

void QManualWindow::on_squares(Position position) {
    if(selectedPawn_ != nullptr) {
        QPawn * qpawn = new QPawn(selectedPawn_->getColor(), selectedPawn_->getRole(),
                                  position, false, this);
        qpawn->setSelectable(false);
        selectedPawn_->close();
        selectedPawn_ = nullptr;
        game_.decrementPawnCount(qpawn->getRole());
        squares_->addWidget(qpawn, position.getX(), position.getY());
        Pawn pawn {qpawn->getRole(), qpawn->getColor(), qpawn->getPosition(), true};
        game_.addPawn(pawn, pawn.getPosition());
    } else {
        QMessageBox messageBox;
        messageBox.critical(0,"No pawn selected","No pawn was selected");
        messageBox.adjustSize();
    }
}
