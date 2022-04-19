#include "gui.h"

using namespace stratego;

View::View(Game game, Controller controller, QWidget *parent)
    : QWidget{parent}, game_{game}, controller_{controller} {
}

void View::update() {
    //todo
}

Controller::Controller(Game game) : game_ {game} {}
