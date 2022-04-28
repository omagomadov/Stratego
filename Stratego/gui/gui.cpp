#include <iostream>
#include <QHBoxLayout>
#include <fstream>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPixmap>
#include <array>

#include "gui.h"

using namespace stratego;
using namespace std;

QBoard::QBoard(Controller &controller, Game &game, QWidget * parent)
    : QWidget {parent}, game_ {game}, controller_ {controller}, selectedPawn_ {} {
    QVBoxLayout * container = new QVBoxLayout();
    QWidget * board = new QWidget();
    message_ = new QLabel();
    message_->hide();
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
}

void QBoard::clicked_on_pawn(QPawn * pawn) {
    if(message_->isVisible()) {
        message_->hide();
    }

    if(selectedPawn_ != nullptr) {
        if(selectedPawn_->getColor() != pawn->getColor()) {
            if(isNeighbor(selectedPawn_->getPosition(), pawn->getPosition())) {
                Direction direction = deduceDirection(selectedPawn_->getPosition(), pawn->getPosition());
                controller_.move(selectedPawn_->getPosition(), direction);
                selectedPawn_ = nullptr;
            } else {
                displayMessage("Pawn is not your neighbor");
                selectedPawn_ = nullptr;
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
        if(!isNeighbor(selectedPawn_->getPosition(), position) || game_.isWater(position)) {
            selectedPawn_ = nullptr;
        } else {
            Direction direction = deduceDirection(selectedPawn_->getPosition(), position);
            controller_.move(selectedPawn_->getPosition(), direction);
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
            if(containsWater(row, column)) {
                square = new QSquare("water", Position(row,column));
            } else {
                square = new QSquare("grass", Position(row,column));
            }
            connect(square, SIGNAL(clicked(stratego::Position)), this, SLOT(clicked_on_square(stratego::Position)));
            board_->addWidget(square, row, column);
        }
    }
}

bool QBoard::containsWater(unsigned row, unsigned column) {
    return (row == 4 && column == 2) || (row == 4 && column == 3) || (row == 5 && column == 2)
            || (row == 5 && column == 3) || (row == 4 && column == 6) || (row == 4 && column == 7)
            || (row == 5 && column == 6) || (row == 5 && column == 7);
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

bool QBoard::isNeighbor(Position first, Position second) {
    Position up {first.getX() - 1, first.getY()};
    Position right {first.getX(), first.getY() + 1};
    Position left {first.getX(), first.getY() - 1};
    Position down {first.getX() + 1, first.getY()};
    return (second == up) || (second == right)
            || (second == left) || (second == down);
}

void QBoard::clearBoard() {
    QLayoutItem * item;
    while(board_->count() != 0) {
        item = board_->itemAt(0);
        if(item->widget()) {
            delete item->widget();
        }
    }
}

void QBoard::displayMessage(QString message) {
    message_->setText(message);
    message_->show();
}

QSquare::QSquare(QString type, Position position, QWidget * parent)
    : QLabel {parent}, type_ {type}, position_ {position} {
    QString url = "://resource/texture/";
    if(type_ == "grass") {
        url += "grass.png";
        setPixmap(QPixmap(url));
    } else {
        url += "water.png";
        setPixmap(QPixmap(url));
    }
    setScaledContents(true);
    setFixedSize(50,50);
}

void QSquare::mousePressEvent(QMouseEvent * event) {
    event->accept();
    emit clicked(position_);
}

QPawn::QPawn(Color color, Role role, Position position, bool hide, QWidget * parent)
    : QLabel {parent}, color_ {color}, role_ {role}, position_ {position}, hide_ {hide} {
    QString player = (color == BLUE) ? "blue" : "red";
    selectable_ = true;
    if(color == BLUE) {
        if(hide) {
            dressHidden(player);
        } else {
            dressPawn(player, role);
        }
    } else {
        if(hide) {
            dressHidden(player);
        } else {
            dressPawn(player, role);
        }
    }
    if(!hide) {
        setToolTip(to_string(static_cast<Role>(role)).c_str());
    }
    setFixedSize(50,50);
}

void QPawn::dressPawn(QString color, Role role) {
    QString url = "://resource/";
    url += color;
    switch(role) {
    case SPY :
        url += "/spy.png";
        setPixmap(QPixmap(url));
        break;
    case GENERAL :
        url += "/general.png";
        setPixmap(QPixmap(url));
        break;
    case MARSHAL :
        url += "/marshal.png";
        setPixmap(QPixmap(url));
        break;
    case MAJOR :
        url += "/major.png";
        setPixmap(QPixmap(url));
        break;
    case COLONEL :
        url += "/colonel.png";
        setPixmap(QPixmap(url));
        break;
    case LIEUTENANT :
        url += "/lieutenant.png";
        setPixmap(QPixmap(url));
        break;
    case COMMANDER :
        url += "/captain.png";
        setPixmap(QPixmap(url));
        break;
    case SERGEANT :
        url += "/sergeant.png";
        setPixmap(QPixmap(url));
        break;
    case MINESWEEPER :
        url += "/miner.png";
        setPixmap(QPixmap(url));
        break;
    case SCOUT :
        url += "/scout.png";
        setPixmap(QPixmap(url));
        break;
    case FLAG :
        url += "/flag.png";
        setPixmap(QPixmap(url));
        break;
    case BOMB :
        url += "/bomb.png";
        setPixmap(QPixmap(url));
        break;
    }
    setScaledContents(true);
}

void QPawn::dressHidden(QString color) {
    QString url = "://resource/";
    url += color;
    url += "/hide.png";
    setPixmap(QPixmap(url));
    setScaledContents(true);
}

void QPawn::mousePressEvent(QMouseEvent * event) {
    if(selectable_) {
        event->accept();
        emit clicked(this);
    } else {
        event->ignore();
    }
}

Color QPawn::getColor() {
    return color_;
}

Role QPawn::getRole() {
    return role_;
}

Position QPawn::getPosition() {
    return position_;
}

bool QPawn::isSelectable() {
    return selectable_;
}

void QPawn::setSelectable(bool selectable) {
    selectable_ = selectable;
}

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
    for(index = mapPawn.begin(); index != mapPawn.end(); index++) {
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

QFileWindow::QFileWindow(QWidget * parent) : QWidget {parent} {
    QVBoxLayout * menu = new QVBoxLayout();
    QWidget * container = new QWidget();
    QHBoxLayout * middle = new QHBoxLayout();
    title_ = new QLabel("Initializiation from file");
    title_->setAlignment(Qt::AlignCenter);
    menu->addWidget(title_);
    choose_ = new QLabel("The name of the file : ");
    middle->addWidget(choose_);
    file_ = new QLineEdit("default.txt");
    file_->setMinimumSize(100,20);
    middle->addWidget(file_);
    container->setLayout(middle);
    menu->addWidget(container);
    submit_ = new QPushButton("Submit");
    menu->addWidget(submit_);
    setLayout(menu);
    adjustSize();
    connect(submit_, SIGNAL(clicked()), this, SLOT(retrieveChosen()));
}

void QFileWindow::retrieveChosen() {
    emit chosen(file_->text());
}

QChooseWindow::QChooseWindow(QWidget * parent) : QWidget {parent} {
    QVBoxLayout * menu = new QVBoxLayout();
    QWidget * containerChooseMenu = new QWidget();
    QHBoxLayout * chooseMenu = new QHBoxLayout();
    title_ = new QLabel("Initialize your board");
    title_->setAlignment(Qt::AlignCenter);
    menu->addWidget(title_);
    choose_ = new QLabel("Choose : ");
    chooseMenu->addWidget(choose_);
    box_ = new QComboBox();
    box_->addItem("From file");
    box_->addItem("Manual");
    chooseMenu->addWidget(box_);
    containerChooseMenu->setLayout(chooseMenu);
    menu->addWidget(containerChooseMenu);
    submit_ = new QPushButton("Submit");
    menu->addWidget(submit_);
    setLayout(menu);
    adjustSize();
    connect(submit_, SIGNAL(clicked()), this, SLOT(retrieveChosen()));
}

void QChooseWindow::retrieveChosen() {
    emit chosen(box_->currentText());
}

QStartWindow::QStartWindow(QWidget * parent) : QWidget {parent} {
    QVBoxLayout * menu = new QVBoxLayout();
    logo_ = new QLabel("Stratego");
    logo_->setAlignment(Qt::AlignCenter);
    menu->addWidget(logo_);
    level_ = new QComboBox();
    level_->addItem("Easy");
    level_->addItem("Normal");
    menu->addWidget(level_);
    start_ = new QPushButton("Launch");
    menu->addWidget(start_);
    setLayout(menu);
    adjustSize();
    connect(start_, SIGNAL(clicked()), this, SLOT(retrieveLevel()));
}

void QStartWindow::retrieveLevel() {
    emit started(level_->currentText());
}

View::View(Game &game, Controller &controller, QWidget *parent)
    : QWidget{parent}, game_{game}, controller_{controller} {
    game.addObserver(this);
    window_= new QHBoxLayout();
    displayStartWindow();
    show();
}

void View::addLevel(QString level) {
    controller_.addLevel(level);
    displayChooseWindow();
}

void View::option(QString url) {
    string choose = url.toStdString();
    if(choose == "Manual") {
        displayManualWindow();
    } else {
        displayFileWindow();
    }
}

void View::addChosen(QString value) {
    try {
        controller_.addFileBoard(value);
        if(game_.getState() == State::RED_TURN) {
            fileWindow_->close();
            game_.setState(State::STARTED);
            board_ = new QBoard(controller_, game_, this);
            window_->addWidget(board_);
        } else {
            fileWindow_->close();
            try {
                controller_.nextState();
                chooseWindow_ = new QChooseWindow(this);
                window_->addWidget(chooseWindow_);
                connect(chooseWindow_, SIGNAL(chosen(QString)), this, SLOT(option(QString)));
            } catch(invalid_argument& ex) {
            }
        }
    } catch(invalid_argument& ex) {
        QMessageBox messageBox;
        if(string(ex.what()) == "File not found") {
            messageBox.critical(0,"File not found","The filename is not in the 'setup-board' folder");
            messageBox.adjustSize();
        } else {
            messageBox.critical(0,"Invalid file","The file contains invalid data "
                                                 "or data that does not respect the placement rules");
            messageBox.adjustSize();
        }
    }
}

void View::addManualBoard() {
    if(game_.getState() == State::RED_TURN) {
        manualWindow_->close();
        game_.setState(State::STARTED);
        board_ = new QBoard(controller_, game_, this);
        window_->addWidget(board_);
    } else {
        manualWindow_->close();
        controller_.nextState();
        chooseWindow_ = new QChooseWindow(this);
        window_->addWidget(chooseWindow_);
        connect(chooseWindow_, SIGNAL(chosen(QString)), this, SLOT(option(QString)));
    }
}

void View::displayStartWindow() {
    startWindow_ = new QStartWindow(this);
    window_->addWidget(startWindow_);
    window_->setAlignment(Qt::AlignCenter);
    setLayout(window_);
    connect(startWindow_, SIGNAL(started(QString)), this, SLOT(addLevel(QString)));
}

void View::displayChooseWindow() {
    controller_.nextState();
    startWindow_->close();
    chooseWindow_ = new QChooseWindow(this);
    window_->addWidget(chooseWindow_);
    connect(chooseWindow_, SIGNAL(chosen(QString)), this, SLOT(option(QString)));
    game_.nextPlayer();
}

void View::displayFileWindow() {
    chooseWindow_->close();
    fileWindow_ = new QFileWindow(this);
    window_->addWidget(fileWindow_);
    connect(fileWindow_, SIGNAL(chosen(QString)), this, SLOT(addChosen(QString)));
}

void View::displayManualWindow() {
    chooseWindow_->close();
    manualWindow_ = new QManualWindow(game_, game_.getCurrentPlayer(), this);
    window_->addWidget(manualWindow_);
    connect(manualWindow_, SIGNAL(submit()), this, SLOT(addManualBoard()));
}

void View::update() {
    board_->updateBoard();
}

Controller::Controller(Game &game) : game_ {game} {}

void Controller::addLevel(QString level) {
    if(level.toStdString() == "Easy") {
        game_.setLevel(1);
    } else {
        game_.setLevel(2);
    }
}

void Controller::addFileBoard(QString choose) {
    string url = "../../Stratego/setup-board/" + choose.toStdString();
    fstream file;
    file.open(url);
    if(file.is_open()) {
        if(!game_.analyseFile("../../Stratego/setup-board/" + choose.toStdString())) {
            throw invalid_argument("Invalid file");
        } else {
            game_.fillBoard(url, game_.getCurrentPlayer());
            game_.nextPlayer();
        }
    } else {
        throw invalid_argument("File not found");
    }
}

void Controller::nextState() {
    switch(game_.getState()) {
    case NOT_STARTED :
        game_.setState(BLUE_TURN);
        break;
    case BLUE_TURN :
        game_.setState(RED_TURN);
        game_.setCurrentPlayer(RED);
        break;
    case RED_TURN :
        game_.setState(STARTED);
        game_.setCurrentPlayer(BLUE);
        break;
    default:
        throw invalid_argument("Invalid state");
    }
}

void Controller::move(Position position, Direction direction) {
    if(game_.isEnemy(position, direction, game_.getCurrentPlayer())) {
        game_.nextPlayer();
        game_.battle(position, direction);
    } else {
        game_.nextPlayer();
        game_.move(position, direction);
    }
}
