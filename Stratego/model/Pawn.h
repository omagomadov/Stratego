#ifndef PAWN_H
#define PAWN_H

#include "Role.h"
#include "Color.h"
#include "Position.h"
#include <ostream>

namespace stratego {
/**
 * @brief The Pawn class represents the pawn of the game.
 */
class Pawn {

    /**
     * @brief role_ represents the role of the pawn.
     */
    Role role_;
    /**
     * @brief color_ represents the color of the pawn.
     */
    Color color_;
    /**
     * @brief position_ represents the position of the pawn.
     */
    stratego::Position position_;
    /**
     * @brief movable_ represents if the pawn is movable or not.
     */
    bool movable_;
    /**
     * @brief visible_ represents if the role of the pawn is visible.
     */
    bool visible_;
    /**
     * @brief valide_ represents if the pawn is valide or not.
     * Not valid represent that there is not a 'real' pawn.
     */
    bool valide_;

public:
    /**
     * @brief Pawn constructor of Pawn.
     * @param role the role
     * @param color the color
     * @param position the position
     * @param movable the movability
     */
    Pawn(Role role, Color color, stratego::Position position, bool movable);
    /**
     * @brief getRole getter of the role.
     * @return the role
     */
    Role getRole();
    /**
     * @brief getColor getter of the color.
     * @return the color
     */
    Color getColor();
    /**
     * @brief getPosition getter of the position.
     * @return the position
     */
    stratego::Position getPosition();
    /**
     * @brief isValide getter of valide.
     * @return the validity
     */
    bool isValide();
    /**
     * @brief isMovable getter of movable.
     * @return the movability
     */
    bool isMovable();
    /**
     * @brief isVisible getter of visible.
     * @return the visibility
     */
    bool isVisible();
    /**
     * @brief setVisible setter of visible.
     * @param visible the visibility
     */
    void setVisible(bool visible);
    /**
     * @brief setValide setter of valide.
     * @param valide the validity
     */
    void setValide(bool valide);
    /**
     * @brief setPosition setter of position.
     * @param row the row
     * @param col the column
     */
    void setPosition(int row, int col);
    /**
     * @brief operator << overloaded operator <<.
     * @param out the ostream
     * @param obj the pawn
     * @return reference of ostream
     */
    friend std::ostream& operator<<(std::ostream& out, stratego::Pawn obj);
};
}

#endif // PAWN_H
