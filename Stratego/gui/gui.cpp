#include <iostream>
#include <QHBoxLayout>
#include <fstream>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPixmap>
#include <array>

#include "gui.h"
#include "qboard.h"
#include "qstartwindow.h"
#include "qfilewindow.h"
#include "qchoosewindow.h"
#include "qmanualwindow.h"

using namespace stratego;
using namespace std;

QController::QController(Game &game) : game_ {game} {}

void QController::addLevel(const QString &level) {
    if(level.toStdString() == "Easy") {
        game_.setLevel(1);
    } else {
        game_.setLevel(2);
    }
}

void QController::addFileBoard(const QString &choose) {
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

void QController::nextState() {
    switch(game_.getState()) {
    case NOT_STARTED :
        game_.setState(BLUE_TURN);
        game_.setCurrentPlayer(BLUE);
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

void QController::move(Position position, Direction direction) {
    if(game_.isEnemy(position, direction, game_.getCurrentPlayer())) {
        game_.nextPlayer();
        game_.battle(position, direction);
    } else {
        game_.nextPlayer();
        game_.move(position, direction);
    }
}

QView::QView(Game &game, stratego::QController &controller, QWidget *parent)
    : QWidget{parent}, game_{game}, controller_{controller} {
    game.addObserver(this);
    window_= new QHBoxLayout();
    displayStartWindow();
    show();
}

void QView::addLevel(const QString &level) {
    controller_.addLevel(level);
    displayChooseWindow();
}

void QView::option(const QString &url) {
    string choose = url.toStdString();
    if(choose == "Manual") {
        displayManualWindow();
    } else {
        displayFileWindow();
    }
}

void QView::addChosen(const QString &value) {
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

void QView::addManualBoard() {
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

void QView::displayStartWindow() {
    startWindow_ = new QStartWindow(this);
    window_->addWidget(startWindow_);
    window_->setAlignment(Qt::AlignCenter);
    setLayout(window_);
    connect(startWindow_, SIGNAL(started(QString)), this, SLOT(addLevel(QString)));
}

void QView::displayChooseWindow() {
    controller_.nextState();
    startWindow_->close();
    chooseWindow_ = new QChooseWindow(this);
    window_->addWidget(chooseWindow_);
    connect(chooseWindow_, SIGNAL(chosen(QString)), this, SLOT(option(QString)));
}

void QView::displayFileWindow() {
    chooseWindow_->close();
    fileWindow_ = new QFileWindow(this);
    window_->addWidget(fileWindow_);
    connect(fileWindow_, SIGNAL(chosen(QString)), this, SLOT(addChosen(QString)));
}

void QView::displayManualWindow() {
    chooseWindow_->close();
    manualWindow_ = new QManualWindow(game_, game_.getCurrentPlayer(), this);
    window_->addWidget(manualWindow_);
    connect(manualWindow_, SIGNAL(submit()), this, SLOT(addManualBoard()));
}

void QView::update() {
    board_->updateBoard();
}
