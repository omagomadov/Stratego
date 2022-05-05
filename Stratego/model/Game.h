#ifndef GAME_H
#define GAME_H

#include <array>
#include <map>
#include <set>

#include "Board.h"
#include "State.h"
#include "Color.h"
#include "Direction.h"
#include "observable.h"

namespace stratego {
/**
 * @brief The Game class represents the game.
 */
class Game : public Observable {
    /**
     * @brief board_ represents the board of the game.
     */
    stratego::Board board_;
    /**
     * @brief state_ represents the state of the game.
     */
    State state_;
    /**
     * @brief currentPlayer_ represents the current player of the game.
     */
    Color currentPlayer_;
    /**
     * @brief level represents the level of the game.
     */
    int level_;
    /**
     * @brief pawns_ contains the pawns.
     */
    std::map<Role, int> pawns_;
    /**
     * @brief observers_ the observers.
     */
    std::set<Observer *> observers_;

public:
    /**
     * @brief Game constructor of Game.
     */
    Game();
    /**
     * @brief addObserver adds a observer.
     * @param observer the observer
     */
    void addObserver(Observer * observer) override;
    /**
     * @brief removeObserver removes a observer.
     * @param observer the observer
     */
    void removeObserver(Observer * observer) override;
    /**
     * @brief notifyObserver notifies the observers.
     */
    void notifyObserver() override;
    /**
     * @brief getPawns getter of board.
     * @return the board
     */
    std::array<std::array<std::optional<Pawn>, 10>, 10> getPawns();
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
     * @brief getLevel getter of the level.
     * @return the level
     */
    int getLevel();
    /**
     * @brief getRole returns the role of the paw at the position.
     * @param position the position
     * @return the role of the position
     */
    Role getRole(stratego::Position position);
    /**
     * @brief isInside checks if the given position in parameter is inside the board.
     * @param position the position
     * @return true if the position is inside the board else false
     */
    bool isInside(stratego::Position position);
    /**
     * @brief isInside checks if the given position in parameter is inside the board.
     * @param position the position
     * @param direction the direction
     * @return true if the position is inside the board else false
     */
    bool isInside(stratego::Position position, Direction direction);
    /**
     * @brief isPawn checks if there is a pawn at the given position in parameter.
     * @param position the positon
     * @return true if there is a pawn at the given position else false
     */
    bool isPawn(stratego::Position position);
    /**
     * @brief isPawn checks if there is a pawn at the given position in parameter.
     * @param position the position
     * @param direction the direction
     * @return true if there is a pawn at the given position else false
     */
    bool isPawn(stratego::Position position, Direction direction);
    /**
     * @brief isPawnSameColor checks if the pawn at this position is equal to the color of the current player.
     * @param position the position
     * @return true if the pawn at this position is equal to the color of the current player.
     */
    bool isPawnSameColor(stratego::Position position);
    /**
     * @brief isPawnSameColor checks if the pawn at this position is equal to the color of the current player.
     * @param position the position
     * @param direction the direction
     * @return true if the pawn at this position is equal to the color of the current player.
     */
    bool isPawnSameColor(stratego::Position position, Direction direction);
    /**
     * @brief move moves the pawn at the position given in parameter to the direction given in parameter.
     * @param position the position
     * @param direction the direction
     */
    void move(stratego::Position& position, Direction direction);
    /**
     * @brief addPawn adds the given pawn in parameter at the positon given in parameter.
     * @param pawn the pawn
     * @param position the position
     */
    void addPawn(stratego::Pawn& pawn, stratego::Position position);
    /**
     * @brief isEmpty checks if there is a pawn at the given position in parameter.
     * @param position the position
     * @param direction the direction
     * @return true if there isn't a pawn else false
     */
    bool isEmpty(stratego::Position position, Direction direction);
    /**
     * @brief isWater checks if there is a water at the given row and column.
     * @param row the row
     * @param col the column
     * @return true if there is water at this position else false
     */
    bool isWater(stratego::Position position);
    /**
     * @brief isWater checks if there is a water at the given position with the direction.
     * @param position the position
     * @param direction the direction
     * @return true if there is water at this position else false
     */
    bool isWater(stratego::Position position, Direction direction);
    /**
     * @brief isAlone checks if the pawn at the position is surrounded.
     * @param positon the position
     * @return true if the pawn at the position is not surrounded else false
     */
    bool isAlone(stratego::Position position);
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
     * @brief setLevel setter of the level.
     * @param level the level
     */
    void setLevel(int level);
    /**
     * @brief setCurrentPlayer setter of the current player.
     * @param color the color
     */
    void setCurrentPlayer(Color color);
    /**
     * @brief setPosition sets the attribute position of the pawn on the position 'onBoard' with the position
     * given in parameter.
     * @param row the row
     * @param col the column
     */
    void setPosition(stratego::Position onBoard, stratego::Position newPos);
    /**
     * @brief initPawns initializes the pawns possible.
     */
    void initPawns();
    /**
     * @brief getRemainingPawns returns the remaining pawns.
     * @return the pawns
     */
    std::map<Role, int> getRemainingPawns();
    /**
     * @brief fillBoard fills the board with pawns after reading the file.
     * @param file the file
     * @param color the color
     */
    void fillBoard(std::string file, Color color);
    /**
     * @brief analyseFile analyses the file and checks if it is valide.
     * @param file the name of the file
     * @return true if the file is valide else false
     */
    bool analyseFile(std::string file);
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
    bool isEnemy(stratego::Position position, Direction direction, Color color);
    /**
     * @brief isMovablePawn checks if the pawn at the given position is movable.
     * @param position the position
     * @return true if the pawn is movable else false
     */
    bool isMovablePawn(stratego::Position position);
    /**
     * @brief battle makes battle.
     * @param position the position
     * @param direction the direction
     */
    void battle(stratego::Position position, Direction direction);
    /**
     * @brief canScoutMove checks if the scout can move.
     * @param pawn the pawn
     * @param direction the direction
     * @param moves the number of moves
     * @return true if the scout can move else false
     */
    bool canScoutMove(Pawn pawn, Direction direction, int moves);
    /**
     * @brief scoutMove moves the scout.
     * @param position the position
     * @param direction the direction
     * @param player the color
     * @param moves the number of moves.
     */
    void scoutMove(Position& position, Direction& direction, Color player, int moves);
    /**
     * @brief clear clears the board.
     */
    void clear();
private:
    /**
     * @brief addPawn adds a pawn on the board with the given position in parameter.
     * @param role the role
     * @param position the position
     * @param color the color
     */
    void addPawn(std::string role, stratego::Position position, Color color);
    /**
     * @brief retrieveRole retrieves the role enum from a string.
     * @param role the role
     * @return the role
     */
    Role retrieveRole(const std::string &role);
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
}

#endif // GAME_H
