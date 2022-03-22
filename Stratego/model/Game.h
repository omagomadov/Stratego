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
     * @brief getRole returns the role of the paw at the position.
     * @param position the position
     * @return the role of the position
     */
    Role getRole(Position position);
    /**
     * @brief isInside checks if the given position in parameter is inside the board.
     * @param position the position
     * @return true if the position is inside the board else false
     */
    bool isInside(Position position);
    /**
     * @brief isInside checks if the given position in parameter is inside the board.
     * @param position the position
     * @param direction the direction
     * @return true if the position is inside the board else false
     */
    bool isInside(Position position, Direction direction);
    /**
     * @brief isPawn checks if there is a pawn at the given position in parameter.
     * @param position the positon
     * @return true if there is a pawn at the given position else false
     */
    bool isPawn(Position position);
    /**
     * @brief isPawn checks if there is a pawn at the given position in parameter.
     * @param position the position
     * @param direction the direction
     * @return true if there is a pawn at the given position else false
     */
    bool isPawn(Position position, Direction direction);
    /**
     * @brief isPawnSameColor checks if the pawn at this position is equal to the color of the current player.
     * @param position the position
     * @return true if the pawn at this position is equal to the color of the current player.
     */
    bool isPawnSameColor(Position position);
    /**
     * @brief isPawnSameColor checks if the pawn at this position is equal to the color of the current player.
     * @param position the position
     * @param direction the direction
     * @return true if the pawn at this position is equal to the color of the current player.
     */
    bool isPawnSameColor(Position position, Direction direction);
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
    void addPawn(Pawn& pawn, Position position);
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
    bool isWater(Position position);
    /**
     * @brief isWater checks if there is a water at the given position with the direction.
     * @param position the position
     * @param direction the direction
     * @return true if there is water at this position else false
     */
    bool isWater(Position position, Direction direction);
    bool isAlone(Position position);
    /**
     * @brief isAvailable checks if there is a pawn avalaible to place.
     * @param pawn the pawn
     * @return true if there is a pawn avalaible else false
     */
    bool isAvailable(Role role);
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
    void setPosition(Position onBoard, Position newPos);
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
    void fillBoard(string file, Color color);
    /**
     * @brief decrementPawnCount decrements counter of the pawn with the role given in paramater
     * @param role the role
     */
    void decrementPawnCount(Role role);
    /**
     * @brief nextPlayer switchs to next player.
     */
    void nextPlayer();
    /**
     * @brief isEnemy checks if there is a enemy.
     * @param position the position
     * @param direction the direction
     * @param color the color
     * @return
     */
    bool isEnemy(Position position, Direction direction, Color color);
    /**
     * @brief isMovablePawn checks if the pawn at the given position is movable.
     * @param position the position
     * @return true if the pawn is movable else false
     */
    bool isMovablePawn(Position position);
    /**
     * @brief battle makes battle.
     * @param position the position
     * @param direction the direction
     */
    void battle(Position position, Direction direction);
private:
    /**
     * @brief addPawn adds a pawn on the board with the given position in parameter.
     * @param role the role
     * @param position the position
     * @param color the color
     */
    void addPawn(string role, Position position, Color color);
    /**
     * @brief retrieveRole retrieves the role enum from a string.
     * @param role the role
     * @return the role
     */
    Role retrieveRole(const string role);
    /**
     * @brief bothSameRole check if the pawn and the enemy pawn given in parameter has equal role.
     * @param pawn the pawn
     * @param enemy the pawn
     * @return true if the pawn and the enemy pawn has equal role else false
     */
    bool bothSameRole(Role pawn, Role enemy);
    /**
     * @brief compare compares 2 roles.
     * @param pawn the role
     * @param enemy the role
     * @return true if the pawn is higher than the enemy else false
     */
    bool compare(Role pawn, Role enemy);
};

#endif // GAME_H
