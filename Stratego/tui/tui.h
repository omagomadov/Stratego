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
    void displayRemainingPawns();
    /**
     * @brief displayCurrentPlayer displays the current player.
     */
    void displayCurrentPlayer();
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
    /**
     * @brief askPawn asks to the current player which pawn he want to place.
     * @return the index of the chosen pawn
     */
    int askPawn();
    /**
     * @brief askLevel asks the level of the game.
     * @return zero for normal, one for easy else negative number
     */
    int askLevel();
    /**
     * @brief askBoardInitialization asks wich type of initialization of the board.
     * @return 1 if it is manual else 2 if is is from file
     */
    int askBoardInitialization();
    /**
     * @brief askFileName asks the name of the file.
     * @return the name of the file
     */
    string askFileName();
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
private:
    /**
     * @brief play plays the game.
     * @param position the position
     * @param direction the direction
     */
    void play(Position& position, Direction& direction);
    /**
     * @brief initPlayers initializes the players. Each player can choose to
     * create manually a board or use a file
     * @param choice the choice
     * @param role the role
     * @param position the position
     * @param roles the roles
     */
    void initPlayers(int choice, Role role, Position position, array<Role, 12> roles);
    /**
     * @brief initRedBoard initializes the board of the red player.
     * @param choice the choice
     * @param role the role
     * @param position the position
     * @param roles the roles
     */
    void initRedBoard(int choice, Role role, Position position, array<Role, 12> roles);
    /**
     * @brief initBlueBoard initializes the board of the blue player.
     * @param choice the choice
     * @param role the role
     * @param position the position
     * @param roles the roles
     */
    void initBlueBoard(int choice, Role role, Position position, array<Role, 12> roles);
    /**
     * @brief analyseFile analyzes the contents of the file.
     * Checks if the file contains valid information
     * @param name the name of the file
     * @return true if the content of file is valid else false
     */
    bool analyseFile(string name);
};

#endif // TUI_H
