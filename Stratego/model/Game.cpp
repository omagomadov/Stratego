#include "Game.h"
#include <iostream>

Game::Game() {
    state_ = State::NOT_STARTED;
}

array<array<optional<Pawn>, 10>, 10> Game::getPawns() {
    return board_.getPawns();
}

State Game::getState() {
    return state_;
}

Color Game::getCurrentPlayer() {
    return currentPlayer_;
}

bool Game::isInside(Position position) {
    return board_.isInside(position);
}

bool Game::isEnd() {
    int flags = 0;
    for(unsigned row = 0; row < board_.getPawns().size(); row++) {
        for(unsigned col = 0; col < board_.getPawns()[row].size(); col++) {
            if(board_.getPawns()[row][col]->getRole() == Role::FLAG) {
                flags++;
            }
        }
    }
    if(flags < 2) {
        return false;
    }
    return true;
}

bool Game::isPawn(Position position) {
    return board_.getPawns()[position.getX()][position.getY()]->isValide();
}

void Game::move(Position& position, Direction direction) {
    optional<Pawn> empty;
    optional<Pawn> pawn = board_.getPawns()[position.getX()][position.getY()];
    switch(direction) {
    case Direction::FORWARD :
        board_.setPawn(empty, position);
        position.setX(position.getX() - 1);
        board_.setPawn(pawn, position);
        break;
    case Direction::LEFT :
        board_.setPawn(empty, position);
        position.setY(position.getY() - 1);
        board_.setPawn(pawn, position);
        break;
    case Direction::RIGHT :
        board_.setPawn(empty, position);
        position.setY(position.getY() + 1);
        board_.setPawn(pawn, position);
        break;
    case Direction::BACKWARD :
        board_.setPawn(empty, position);
        position.setX(position.getX() + 1);
        board_.setPawn(pawn, position);
        break;
    }
}

bool Game::isEmpty(Position position, Direction direction) {
    return board_.isEmpty(position, direction);
}

bool Game::isWater(int row, int col) {
    return board_.isWater(row, col);
}

bool Game::isAvailable(int pawn) {
    switch(pawn) {
    case 1:
        if(pawns_[Role::MARSHAL] == 0) {
            return false;
        }
        break;
    case 2:
        if(pawns_[Role::GENERAL] == 0) {
            return false;
        }
        break;
    case 3:
        if(pawns_[Role::COLONEL] == 0) {
            return false;
        }
        break;
    case 4:
        if(pawns_[Role::MAJOR] == 0) {
            return false;
        }
        break;
    case 5:
        if(pawns_[Role::COMMANDER] == 0) {
            return false;
        }
        break;
    case 6:
        if(pawns_[Role::LIEUTENANT] == 0) {
            return false;
        }
        break;
    case 7:
        if(pawns_[Role::SERGEANT] == 0) {
            return false;
        }
        break;
    case 8:
        if(pawns_[Role::MINESWEEPER] == 0) {
            return false;
        }
        break;
    case 9:
        if(pawns_[Role::SCOUT] == 0) {
            return false;
        }
        break;
    case 10:
        if(pawns_[Role::SPY] == 0) {
            return false;
        }
        break;
    case 11:
        if(pawns_[Role::FLAG] == 0) {
            return false;
        }
        break;
    case 12:
        if(pawns_[Role::BOMB] == 0) {
            return false;
        }
        break;
    }
    return true;
}

bool Game::isAllPawnsPlaced() {
    auto it = pawns_.begin();
    while(it != pawns_.end()) {
        if(it->second > 0) {
            return false;
        }
        it++;
    }
    return true;
}

void Game::setState(State state) {
    state_ = state;
}

void Game::addPawn(int pawn, Color color, Position position) {
    board_.addPawn(pawn, color, position);
}

void Game::initPawns() {
    if(!pawns_.empty()) {
        pawns_.clear();
    }
    pawns_.insert({Role::MARSHAL, 1});
    pawns_.insert({Role::GENERAL, 1});
    pawns_.insert({Role::COLONEL, 2});
    pawns_.insert({Role::MAJOR, 3});
    pawns_.insert({Role::COMMANDER, 4});
    pawns_.insert({Role::LIEUTENANT, 4});
    pawns_.insert({Role::SERGEANT, 4});
    pawns_.insert({Role::MINESWEEPER, 5});
    pawns_.insert({Role::SCOUT, 8});
    pawns_.insert({Role::SPY, 1});
    pawns_.insert({Role::FLAG, 1});
    pawns_.insert({Role::BOMB, 6});
}

map<Role, int> Game::getRemainingPawns() {
    return pawns_;
}

void Game::decrementPawnCount(int index) {
    switch(index) {
    case 1: {
        pawns_.at(Role::MARSHAL) = pawns_.at(Role::MARSHAL) - 1;
        break;
    }
    case 2: {
        pawns_.at(Role::GENERAL) = pawns_.at(Role::GENERAL) - 1;
        break;
    }
    case 3: {
        pawns_.at(Role::COLONEL) = pawns_.at(Role::COLONEL) - 1;
        break;
    }
    case 4: {
        pawns_.at(Role::MAJOR) = pawns_.at(Role::MAJOR) - 1;
        break;
    }
    case 5: {
        pawns_.at(Role::COMMANDER) = pawns_.at(Role::COMMANDER) - 1;
        break;
    }
    case 6: {
        pawns_.at(Role::LIEUTENANT) = pawns_.at(Role::LIEUTENANT) - 1;
        break;
    }
    case 7: {
        pawns_.at(Role::SERGEANT) = pawns_.at(Role::SERGEANT) - 1;
        break;
    }
    case 8: {
        pawns_.at(Role::MINESWEEPER) = pawns_.at(Role::MINESWEEPER) - 1;
        break;
    }
    case 9: {
        pawns_.at(Role::SCOUT) = pawns_.at(Role::SCOUT) - 1;
        break;
    }
    case 10: {
        pawns_.at(Role::SPY) = pawns_.at(Role::SPY) - 1;
        break;
    }
    case 11: {
        pawns_.at(Role::FLAG) = pawns_.at(Role::FLAG) - 1;
        break;
    }
    case 12: {
        pawns_.at(Role::BOMB) = pawns_.at(Role::BOMB) - 1;
        break;
    }
    }
}

/*
void Game::fillBoard(string file, Color color) {
    // todo
}
*/

