#include "Pawn.h"

using namespace std;
using namespace stratego;

Pawn::Pawn(Role role, Color color, Position position, bool movable) : role_ {role}, color_ {color},
    position_ {position}, movable_ {movable}, visible_ {false}, valide_ {true} {}

Role Pawn::getRole() {
    return role_;
}

Color Pawn::getColor() {
    return color_;
}

Position Pawn::getPosition() {
    return position_;
}

bool Pawn::isValide() {
    return valide_;
}

bool Pawn::isMovable() {
    return movable_;
}

bool Pawn::isVisible() {
    return visible_;
}

void Pawn::setVisible(bool visible) {
    visible_ = visible;
}

void Pawn::setValide(bool valide) {
    valide_ = valide;
}

void Pawn::setPosition(int row, int col) {
    position_.setX(row);
    position_.setY(col);
}

ostream& operator<<(ostream& out, Pawn obj) {
    return out << "("
               << "role : "
               << obj.getRole()
               << " color : "
               << obj.getColor()
               << " position : ("
               << obj.getPosition().getX()
               << ":"
               << obj.getPosition().getY()
               << ")"
               << " movable : "
               << obj.isMovable()
               << " valide : "
               << obj.isValide()
               << " visible : "
               << obj.isVisible()
               << ")";
}
