#include "Board.h"

Board::Board() {
    Position pos1 {4,2};
    water_.push_back(pos1);
    pos1.setX(pos1.getX() + 1);
    water_.push_back(pos1);

    Position pos2 {4,3};
    water_.push_back(pos2);
    pos2.setX(pos2.getX() + 1);
    water_.push_back(pos2);

    Position pos3 {4,6};
    water_.push_back(pos3);
    pos3.setX(pos3.getX() + 1);
    water_.push_back(pos3);

    Position pos4 {4,7};
    water_.push_back(pos4);
    pos4.setX(pos4.getX() + 1);
    water_.push_back(pos4);
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

void Board::addPawn(int pawn, Color color, Position position) {
    if(isInside(position)) {
        if(!pawns_[position.getX()][position.getY()]->isValide()) {
            switch(pawn) {
            case 1: {
                Pawn chosenPawn {Role::MARSHAL, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 2: {
                Pawn chosenPawn {Role::GENERAL, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 3: {
                Pawn chosenPawn {Role::COLONEL, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 4: {
                Pawn chosenPawn {Role::MAJOR, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 5: {
                Pawn chosenPawn {Role::COMMANDER, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 6: {
                Pawn chosenPawn {Role::LIEUTENANT, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 7: {
                Pawn chosenPawn {Role::SERGEANT, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 8: {
                Pawn chosenPawn {Role::MINESWEEPER, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 9: {
                Pawn chosenPawn {Role::SCOUT, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 10: {
                Pawn chosenPawn {Role::SPY, color, position, true};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 11: {
                Pawn chosenPawn {Role::FLAG, color, position, false};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            case 12: {
                Pawn chosenPawn {Role::BOMB, color, position, false};
                pawns_[position.getX()][position.getY()] = chosenPawn;
                break;
            }
            }
        }
    }
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
        if(pos.getX() == row && pos.getY() == col) {
            return true;
        }
    }
    return false;
}

void Board::setPawn(optional<Pawn> pawn, Position position) {
    pawns_[position.getX()][position.getY()] = pawn;
}
