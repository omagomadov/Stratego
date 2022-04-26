#include <iostream>
#include <QApplication>

#include "Game.h"
#include "gui.h"

using namespace stratego;
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Game game {};
    Controller controller {game};
    View view {game, controller};
    app.exec();
}
