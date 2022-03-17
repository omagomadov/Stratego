#include "Board.h"
#include <iostream>

Board::Board() {
    Position water_pos1 {4,2};
    water_.push_back(water_pos1);
    water_pos1.setX(water_pos1.getX() + 1);
    water_.push_back(water_pos1);

    Position water_pos2 {4,3};
    water_.push_back(water_pos2);
    water_pos2.setX(water_pos2.getX() + 1);
    water_.push_back(water_pos2);

    Position water_pos3 {4,6};
    water_.push_back(water_pos3);
    water_pos3.setX(water_pos3.getX() + 1);
    water_.push_back(water_pos3);

    Position water_pos4 {4,7};
    water_.push_back(water_pos4);
    water_pos4.setX(water_pos4.getX() + 1);
    water_.push_back(water_pos4);
}

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

void Board::addPawn(Pawn& pawn, Position position) {
    pawns_[position.getX()][position.getY()] = pawn;
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

void Board::setPosition(int row, int col) {
    pawns_[row][col]->setPosition(row, col);
}
