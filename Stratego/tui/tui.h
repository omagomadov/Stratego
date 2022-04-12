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
    stratego::Game& game_;

public:
    /**
     * @brief View constructor of View.
     * @param game the game
     */
    View(stratego::Game& game);
    /**
     * @brief displayWelcome displays a welcome message on the terminale.
     */
    void displayWelcome();
    /**
     * @brief displayBoard displays the board of the game.
     */
    void displayBoard();
    /**
     * @brief displayBattle displays the board of the game when a battle occure.
     */
    void displayBattle();
    /**
     * @brief displayPlayer displays the current player of the game on the terminale.
     */
    void displayPlayer();
    /**
     * @brief DisplayRemainingPawns displays the remaining pawns.
     */
    void displayRemainingPawns();
    /**
     * @brief displayWinner displays the winner.
     */
    void displayWinner();
    /**
     * @brief displayEnd displays the a end message.
     */
    void displayEnd();
    /**
     * @brief askPosition asks to the current player a position.
     * @return the position that the player has given
     */
    stratego::Position askPosition();
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
     * @return 1 if it is manual else 2 if it is from file
     */
    int askBoardInitialization();
    /**
     * @brief askMovement asks number of movement of the pawn.
     * @return the number of movement
     */
    int askMovement();
    /**
     * @brief askFileName asks the name of the file.
     * @return the name of the file
     */
    std::string askFileName();
};

/**
 * @brief The Controller class represents the class Controller.
 */
class Controller {

    /**
     * @brief game_ represents the game.
     */
    stratego::Game& game_;
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
    Controller(stratego::Game& game, View& view);
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
    void play(stratego::Position& position, Direction& direction);
    /**
     * @brief initPlayers initializes the players. Each player can choose to
     * create manually a board or use a file
     * @param choice the choice
     * @param role the role
     * @param position the position
     * @param roles the roles
     */
    void initPlayers(int choice, Role role, stratego::Position position, std::array<Role, 12> roles);
    /**
     * @brief initRedBoard initializes the board of the red player.
     * @param choice the choice
     * @param role the role
     * @param position the position
     * @param roles the roles
     */
    void initRedBoard(int choice, Role role, stratego::Position position, std::array<Role, 12> roles);
    /**
     * @brief initBlueBoard initializes the board of the blue player.
     * @param choice the choice
     * @param role the role
     * @param position the position
     * @param roles the roles
     */
    void initBlueBoard(int choice, Role role, stratego::Position position, std::array<Role, 12> roles);
    /**
     * @brief checkPosition checks if the position respects the rules.
     * @param position the position
     * @return true if the position is valid else false
     */
    bool checkPosition(stratego::Position position);
    /**
     * @brief checkDirection checks if the direction respects the rules.
     * @param position the position
     * @param direction the direction
     * @return true if the direction is valid else false
     */
    bool checkDirection(stratego::Position position, Direction direction);
};

#endif // TUI_H
