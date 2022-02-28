#ifndef TUI_H
#define TUI_H

#include "Game.h"

class View {

    Game game_;

public:
    View(Game game);
    void displayWelcome();
    void displayBoard();
    void displayPlayer();
    Position askPosition();
    Direction askDirection();
};

class Controller {

    Game game_;
    View view_;

public:
    Controller(Game game, View view);
    void start();
};

#endif // TUI_H
