#include "Board.h"
#include <iostream>

using namespace std;
using namespace stratego;

Board::Board() : water_ {Position{4,2}, Position{5,2}, Position{4,3}, Position{5,3},
                         Position{4,6}, Position{5,6}, Position{4,7}, Position{5,7}} {
    pawns_[4][2]->setValide(true);
    pawns_[4+1][2]->setValide(true);

    pawns_[4][3]->setValide(true);
    pawns_[4+1][3]->setValide(true);

    pawns_[4][6]->setValide(true);
    pawns_[4+1][6]->setValide(true);

    pawns_[4][7]->setValide(true);
    pawns_[4+1][7]->setValide(true);
}

array<array<optional<Pawn>, 10>, 10> Board::getPawns() {
    return pawns_;
}

bool Board::isInside(Position position) {
    if(position.getX() < 0 || position.getX() > 9) {
        return false;
    } else if(position.getY() < 0 || position.getY() > 9) {
        return false;
    }
    return true;
}

void Board::setValide(int row, int column, bool valide) {
    pawns_[row][column]->setValide(valide);
}

bool Board::isAlone(Position position) {
    int row = position.getX();
    int column = position.getY();
    Position up {row + 1, column};
    Position down {row - 1, column};
    Position left {row, column + 1};
    Position right {row, column - 1};
    Color color = pawns_[row][column]->getColor();
    int count = 0;
    // check if neighbor (incremente), if neighbor is valid decremente
    if(isInside(up)) {
        count++;
        if(pawns_[row + 1][column]->isValide()
                && pawns_[row + 1][column]->getColor() == color) {
            count--;
        }
    }
    if(isInside(down)) {
        count++;
        if(pawns_[row - 1][column]->isValide()
                && pawns_[row - 1][column]->getColor() == color) {
            count--;
        }
    }
    if(isInside(left)) {
        count++;
        if(pawns_[row][column + 1]->isValide()
                && pawns_[row][column + 1]->getColor() == color) {
            count--;
        }
    }
    if(isInside(right)) {
        count++;
        if(pawns_[row][column - 1]->isValide()
                && pawns_[row][column - 1]->getColor() == color) {
            count--;
        }
    }
    // if the counter is equal to 0 that mean => he can't move
    //    if(count == 0) {
    //        return false;
    //    } else {
    //        return true;
    //    }
    return count != 0;
}

void Board::addPawn(Pawn& pawn, Position position) {
    pawns_[position.getX()][position.getY()] = pawn;
}

Role Board::getRole(Position position) {
    return pawns_[position.getX()][position.getY()]->getRole();
}

bool Board::isEmpty(Position position, Direction direction) {
    switch(direction) {
    case Direction::FORWARD :
        position.setX(position.getX() - 1);
        if(isInside(position)) {
            return !pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    case Direction::LEFT :
        position.setY(position.getY() - 1);
        if(isInside(position)) {
            return !pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    case Direction::RIGHT :
        position.setY(position.getY() + 1);
        if(isInside(position)) {
            return !pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    case Direction::BACKWARD :
        position.setX(position.getX() + 1);
        if(isInside(position)) {
            return !pawns_[position.getX()][position.getY()]->isValide();
        }
        break;
    }
    return false;
}

bool Board::isWater(int row, int col) {
    for(Position pos : water_) {
        if(row == pos.getX() && col == pos.getY()) {
            return true;
        }
    }
    return false;
}

bool Board::isWater(Position position, Direction direction) {
    switch(direction) {
    case Direction::FORWARD :
        position.setX(position.getX() - 1);
        break;
    case Direction::LEFT :
        position.setY(position.getY() - 1);
        break;
    case Direction::RIGHT :
        position.setY(position.getY() + 1);
        break;
    case Direction::BACKWARD :
        position.setX(position.getX() + 1);
        break;
    }
    for(Position pos : water_) {
        if(position.getX() == pos.getX() && position.getY() == pos.getY()) {
            return true;
        }
    }
    return false;
}

void Board::setPawn(optional<Pawn> pawn, Position position) {
    pawns_[position.getX()][position.getY()] = pawn;
}

void Board::setVisible(int row, int column, bool visible) {
    pawns_[row][column]->setVisible(visible);
}

void Board::setPosition(Position onBoard, Position newPos) {
    pawns_[onBoard.getX()][onBoard.getY()]->setPosition(newPos.getX(), newPos.getY());
}
