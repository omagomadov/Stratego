#include "Board.h"

Board::Board() {}

array<array<optional<Pawn>, 10>, 10> Board::getPawns() {
    return pawns_;
}

bool Board::isInside(Position position) {
    if(position.getX() < 0 || position.getX() > 10) {
        return false;
    } else if(position.getY() < 0 || position.getY() > 10) {
        return false;
    }
    return true;
}

void Board::addPawn(Pawn pawn, Position position) {
    if(isInside(position)) {
        if(!pawns_[pawn.getPosition().getX()][pawn.getPosition().getY()]->isValide()) {
            pawns_[position.getX()][position.getY()] = pawn;
        }
    }
}

bool Board::isEmpty(Position position, Direction direction) {
    switch(direction) {
    case Direction::FORWARD :
        position.setX(position.getX() - 1);
        if(isInside(position)) {
            return pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    case Direction::LEFT :
        position.setY(position.getY() - 1);
        if(isInside(position)) {
            return pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    case Direction::RIGHT :
        position.setY(position.getY() + 1);
        if(isInside(position)) {
            return pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    case Direction::BACKWARD :
        position.setX(position.getX() + 1);
        if(isInside(position)) {
            return pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    }
    return false;
}
