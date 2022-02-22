#ifndef BOARD_H
#define BOARD_H

#include "Pawn.h"
#include <optional>
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
    void addPawn(Pawn pawn, Position position);
};

#endif // BOARD_H
