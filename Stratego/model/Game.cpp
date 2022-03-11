#include "Game.h"

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

int Game::getLevel() {
    return level_;
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
        return true;
    }
    return false;
}

bool Game::isPawn(Position position) {
    return board_.getPawns()[position.getX()][position.getY()]->isValide();
}

bool Game::isPawnSameColor(Position position) {
    if(isInside(position)) {
        if(board_.getPawns()[position.getX()][position.getY()]->getColor() == currentPlayer_) {
            return true;
        }
    }
    return false;
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

bool Game::isAvailable(Role role) {
    return pawns_[role] != 0;
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

void Game::setLevel(int level) {
    level_ = level;
}

void Game::setCurrentPlayer(Color color) {
    currentPlayer_ = color;
}

void Game::addPawn(Pawn& pawn, Position position) {
    board_.addPawn(pawn, position);
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

void Game::decrementPawnCount(Role role) {
    pawns_[role] = pawns_[role] - 1;
}

void Game::nextPlayer() {
    switch(currentPlayer_) {
    case Color::BLUE :
        currentPlayer_ = Color::RED;
        break;
    case Color::RED :
        currentPlayer_ = Color::BLUE;
        break;
    }
}

/*
void Game::fillBoard(string file, Color color) {
    // todo
}
*/

