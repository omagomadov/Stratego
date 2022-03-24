#ifndef BOARD_H
#define BOARD_H

#include "Pawn.h"
#include "Direction.h"
#include <optional>
#include <vector>
#include <array>

using namespace std;

/**
 * @brief The Board class represents the board of the game.
 */
class Board {

    /**
     * @brief pawns_ represents the board.
     */
    array<array<optional<Pawn>, 10>, 10> pawns_;
    /**
     * @brief water represents the position of the waters.
     */
    vector<Position> water_;

public:
    /**
     * @brief Board constructor of Board.
     */
    Board();
    /**
     * @brief getPawns getter of board.
     * @return the board
     */
    array<array<optional<Pawn>, 10>, 10> getPawns();
    /**
     * @brief isInside checks if the given position in parameter is inside the board.
     * @param position the position
     * @return true if the position is inside the board else false
     */
    bool isInside(Position position);
    /**
     * @brief addPawn adds the given pawn in parameter at the position given in parameter.
     * @param pawn the pawn
     * @param position the position
     */
    void addPawn(Pawn& pawn, Position position);
    /**
     * @brief getRole Gives the role of the pawn  at the given position in parameter.
     * @param position the position
     * @return the role of the pawn at the position
     */
    Role getRole(Position position);
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
     * @brief isAlone checks if the pawn at the position is surrounded.
     * @param positon the position
     * @return true if the pawn at the position is not surrounded else false
     */
    bool isAlone(Position position);
    /**
     * @brief isWater checks if there is a water at the position.
     * @param position the position
     * @param direction the direction
     * @return true if there is water at this position else false
     */
    bool isWater(Position position, Direction direction);
    /**
     * @brief setPawn sets a pawn at the given position on the board.
     * @param pawn the pawn
     * @param position the position
     */
    void setPawn(optional<Pawn> pawn, Position position);
    /**
     * @brief setVisible sets the attribute visible with the boolean given in parameter.
     * @param row the row
     * @param column the column
     * @param visible the visibility
     */
    void setVisible(int row, int column, bool visible);
    /**
     * @brief setValide sets the attribute valide with the boolean given in parameter.
     * @param row the row
     * @param column the column
     * @param valide the validity
     */
    void setValide(int row, int column, bool valide);
    /**
     * @brief setPosition sets the attribute position of the pawn on the position 'onBoard' with the position
     * given in parameter.
     * @param row the row
     * @param col the column
     */
    void setPosition(Position onBoard, Position newPos);
};

#endif // BOARD_H
