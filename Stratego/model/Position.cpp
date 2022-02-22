#include "Position.h"

Position::Position(int x, int y) : x_ {x}, y_ {y} {}

int Position::getX() {
    return x_;
}

int Position::getY() {
    return y_;
}

void Position::setX(int x) {
    x_ = x;
}

void Position::setY(int y) {
    y_ = y;
}

bool Position::operator==(Position &lhs) {
    if(lhs.getX() == x_) {
        if(lhs.getY() == y_) {
            return true;
        }
    }
    return false;
}

ostream& operator<<(ostream& out, Position& obj) {
    return out << "(" << obj.getX() << ":" << obj.getY() << ")";
}
