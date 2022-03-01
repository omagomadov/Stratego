#ifndef TUI_H
#define TUI_H

#include "Game.h"

/**
 * @brief The View class represents the class View.
 */
class View {

    /**
     * @brief game_ represents the game.
     */
    Game& game_;

public:
    /**
     * @brief View constructor of View.
     * @param game the game
     */
    View(Game& game);
    /**
     * @brief displayWelcome displays a welcome message on the terminale.
     */
    void displayWelcome();
    /**
     * @brief displayBoard displays the board of the game on the terminale.
     */
    void displayBoard();
    /**
     * @brief displayPlayer displays the current player of the game on the terminale.
     */
    void displayPlayer();
    /**
     * @brief DisplayRemainingPawns displays the remaining pawns.
     */
    void DisplayRemainingPawns();
    /**
     * @brief askPosition asks to the current player a position.
     * @return the position that the player has given
     */
    Position askPosition();
    /**
     * @brief askDirection asks to the current player a direction.
     * @return the direction that the player has given
     */
    Direction askDirection();
};

/**
 * @brief The Controller class represents the class Controller.
 */
class Controller {

    /**
     * @brief game_ represents the game.
     */
    Game& game_;
    /**
     * @brief view_ represents the view.
     */
    View& view_;

public:
    /**
     * @brief Controller constructor of Controller.
     * @param game the game
     * @param view the view
     */
    Controller(Game& game, View& view);
    /**
     * @brief start starts the game.
     */
    void start();
};

#endif // TUI_H
