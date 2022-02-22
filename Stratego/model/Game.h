#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "State.h"
#include "Color.h"
#include "Direction.h"
#include <array>

using namespace std;

/**
 * @brief The Game class represents the game.
 */
class Game {

    /**
     * @brief board_ represents the board of the game.
     */
    Board board_;
    /**
     * @brief state_ represents the state of the game.
     */
    State state_;
    /**
     * @brief currentPlayer_ represents the current player of the game.
     */
    Color currentPlayer_;

public:
    /**
     * @brief Game constructor of Game.
     */
    Game();
    /**
     * @brief getPawns getter of board.
     * @return the board
     */
    array<array<optional<Pawn>, 10>, 10> getPawns();
    /**
     * @brief getState getter of state.
     * @return the state
     */
    State getState();
    /**
     * @brief getCurrentPlayer getter of the current player.
     * @return the current player
     */
    Color getCurrentPlayer();
    /**
     * @brief isInside checks if the given position in parameter is inside the board.
     * @param position the position
     * @return true if the position is inside the board else false
     */
    bool isInside(Position position);
    /**
     * @brief isEnd checks if the game is ended. Checks if one of the flag is captured
     * @return true if the game is ended else false
     */
    bool isEnd();
    /**
     * @brief isPawn checks if there is a pawn at the given position in parameter.
     * @param position the positon
     * @return true if there is a pawn at the given position else false
     */
    bool isPawn(Position position);
    /**
     * @brief move moves the pawn at the position given in parameter to the direction given in parameter.
     * @param position the position
     * @param direction the direction
     */
    void move(Position position, Direction direction);
    /**
     * @brief addPawn adds the given pawn in parameter at the positon given in parameter.
     * @param pawn the pawn
     * @param position the position
     */
    void addPawn(Pawn pawn, Position position);
    /**
     * @brief fillBoard fills the board with pawns after reading the file.
     * @param file the file
     * @param color the color
     */
    void fillBoard(string file, Color color);
};

#endif // GAME_H
