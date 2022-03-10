#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "State.h"
#include "Color.h"
#include "Direction.h"
#include <array>
#include <map>

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
    /**
     * @brief level //todo
     */
    int level_;
    /**
     * @brief pawns_ contains the pawns.
     */
    map<Role, int> pawns_;

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
     * @brief getLevel //todo
     * @return
     */
    int getLevel();
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
    void move(Position& position, Direction direction);
    /**
     * @brief addPawn adds the given pawn in parameter at the positon given in parameter.
     * @param pawn the pawn
     * @param position the position
     */
    void addPawn(int pawn, Color color, Position position);
    /**
     * @brief isEmpty checks if there is a pawn at the given position in parameter.
     * @param position the position
     * @param direction the direction
     * @return true if there isn't a pawn else false
     */
    bool isEmpty(Position position, Direction direction);
    /**
     * @brief isWater checks if there is a water at the given row and column.
     * @param row the row
     * @param col the column
     * @return true if there is water at this position else false
     */
    bool isWater(int row, int col);
    /**
     * @brief isAvailable checks if there is a pawn avalaible to place.
     * @param pawn the pawn
     * @return true if there is a pawn avalaible else false
     */
    bool isAvailable(int pawn);
    /**
     * @brief isAllPawnsPlaced checks if all pawns are placed on the board.
     * @return true if all pawns are placed on the board else false
     */
    bool isAllPawnsPlaced();
    /**
     * @brief setState setter of State.
     * @param state the state
     */
    void setState(State state);
    /**
     * @brief setLevel //todo
     * @param level
     */
    void setLevel(int level);
    /**
     * @brief setCurrentPlayer //todo
     * @param color
     */
    void setCurrentPlayer(Color color);
    /**
     * @brief initPawns initializes the pawns possible.
     */
    void initPawns();
    /**
     * @brief getRemainingPawns returns the remaining pawns.
     * @return the pawns
     */
    map<Role, int> getRemainingPawns();
    /**
     * @brief fillBoard fills the board with pawns after reading the file.
     * @param file the file
     * @param color the color
     */
    void decrementPawnCount(int index);
    void fillBoard(string file, Color color);
};

#endif // GAME_H
