#ifndef POSITION_H
#define POSITION_H

#include <ostream>

using namespace std;

/**
 * @brief The Position class represents the position.
 */
class Position {

    /**
     * @brief x_ the abscissa
     */
    int x_;
    /**
     * @brief y_ the ordinate
     */
    int y_;

public:
    /**
     * @brief Position constructor of Position.
     * @param x the x
     * @param y the y
     */
    Position(int x, int y);
    /**
     * @brief getX getter of x.
     * @return the abscissa
     */
    int getX();
    /**
     * @brief getY getter of y.
     * @return the ordinate
     */
    int getY();
    /**
     * @brief setX the setter of x.
     */
    void setX(int x);
    /**
     * @brief setY the setter of y.
     */
    void setY(int y);
    /**
     * @brief operator == overloaded operator of comparison.
     * @param lhs the position
     * @return true if the position is the same else false
     */
    bool operator==(Position & lhs);
    /**
     * @brief operator << overloaded operator <<.
     * @param out the ostream
     * @param obj the pawn
     * @return reference of ostream
     */
    friend ostream& operator<<(ostream& out, Position& obj);
};

#endif // POSITION_H
