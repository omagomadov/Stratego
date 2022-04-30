#include <iostream>
#include <QApplication>

#include "Game.h"
#include "gui.h"

using namespace stratego;
using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Game game {};
    QController controller {game};
    QView view {game, controller};
    app.exec();
}
