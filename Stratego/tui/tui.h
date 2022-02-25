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

#endif // TUI_H
