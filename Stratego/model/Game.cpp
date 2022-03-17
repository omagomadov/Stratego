#include "Game.h"
#include <fstream>
#include <iostream>
#include <vector>

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

bool Game::isPawnSameColor(Position position, Direction direction) {
    // move -> direction
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

    if(isInside(position)) {
        if(isEmpty(position, direction)) {
            if(board_.getPawns()[position.getX()][position.getY()]->getColor() == currentPlayer_) {
                return true;
            }
        }
    }
    return false;
}

void Game::move(Position& position, Direction direction) {
    optional<Pawn> empty;
    optional<Pawn> pawn = board_.getPawns()[position.getX()][position.getY()];
    optional<Pawn> enemy;
    switch(direction) {
    case Direction::FORWARD :
        if(isEnemy(position, direction, currentPlayer_)) {
            enemy = board_.getPawns()[position.getX() - 1][position.getY()];
            if(bothSameRole(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, pawn->getPosition());
                board_.setPawn(empty, enemy->getPosition());
            } else if(battle(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, position);
                position.setX(position.getX() - 1);
                board_.setPawn(pawn, position);
            } else {
                board_.setVisible(position.getX() - 1, position.getY(), false);
                board_.setPawn(empty, position);
            }
        } else {
            board_.setPawn(empty, position);
            position.setX(position.getX() - 1);
            board_.setPawn(pawn, position);
            board_.setPosition(position.getX(), position.getY());
        }
        break;
    case Direction::LEFT :
        if(isEnemy(position, direction, currentPlayer_)) {
            enemy = board_.getPawns()[position.getX()][position.getY() - 1];
            if(bothSameRole(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, pawn->getPosition());
                board_.setPawn(empty, enemy->getPosition());
            } else if(battle(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, position);
                position.setY(position.getY() - 1);
                board_.setPawn(pawn, position);
            } else {
                board_.setVisible(position.getX(), position.getY() - 1, false);
                board_.setPawn(empty, position);
            }
        } else {
            board_.setPawn(empty, position);
            position.setY(position.getY() - 1);
            board_.setPawn(pawn, position);
            board_.setPosition(position.getX(), position.getY());
        }
        break;
    case Direction::RIGHT :
        if(isEnemy(position, direction, currentPlayer_)) {
            enemy = board_.getPawns()[position.getX()][position.getY() + 1];
            if(bothSameRole(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, pawn->getPosition());
                board_.setPawn(empty, enemy->getPosition());
            } else if(battle(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, position);
                position.setY(position.getY() + 1);
                board_.setPawn(pawn, position);
            } else {
                board_.setVisible(position.getX(), position.getY() + 1, false);
                board_.setPawn(empty, position);
            }
        } else {
            board_.setPawn(empty, position);
            position.setY(position.getY() + 1);
            board_.setPawn(pawn, position);
            board_.setPosition(position.getX(), position.getY());
        }
        break;
    case Direction::BACKWARD :
        if(isEnemy(position, direction, currentPlayer_)) {
            enemy = board_.getPawns()[position.getX() + 1][position.getY()];
            if(bothSameRole(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, pawn->getPosition());
                board_.setPawn(empty, enemy->getPosition());
            } else if(battle(pawn->getRole(), enemy->getRole())) {
                board_.setPawn(empty, position);
                position.setX(position.getX() + 1);
                board_.setPawn(pawn, position);
            } else {
                board_.setVisible(position.getX() + 1, position.getY(), false);
                board_.setPawn(empty, position);
            }
        } else {
            board_.setPawn(empty, position);
            position.setX(position.getX() + 1);
            board_.setPawn(pawn, position);
            board_.setPosition(position.getX(), position.getY());
        }
        break;
    }
}

bool Game::isEmpty(Position position, Direction direction) {
    return board_.isEmpty(position, direction);
}

bool Game::isWater(int row, int col) {
    return board_.isWater(row, col);
}

bool Game::isWater(Position position, Direction direction) {
    return board_.isWater(position, direction);
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

void Game::fillBoard(string file, Color color) {
    fstream stream;
    stream.open(file);
    // read file while not eof
    while(!stream.eof()) {
        // check color of pawn
        if(color == Color::BLUE) {
            int row = 0, col = 0;
            // read each line delimited with ' '
            for (string line; getline(stream, line, ' '); ) {
                // check if the col is lower than 10
                if(col > 9) {
                    col = 0;
                    row++;
                }
                // if letter is size 3 ==> which mean that it have taken the '/r/n'
                if(line.size() == 3) {
                    // take the first letter at position 0 and create a pawn
                    addPawn(string(1, line.at(0)), Position{row,col}, color);
                    col++;
                    if(col > 9) {
                        col = 0;
                        row++;
                    }
                    // take the second letter at position 2 and create pawn
                    addPawn(string(1, line.at(2)), Position{row,col}, color);
                } else {
                    // if not letter with size 3.. it's ok just take his letter and create pawn
                    addPawn(line, Position{row, col}, color);
                }
                col++;
            }
        } else {
            int row = 9, col = 0;
            // read each line delimited with ' '
            for (string line; getline(stream, line, ' '); ) {
                // check if the col is lower than 10
                if(col > 9) {
                    col = 0;
                    row--;
                }
                // if letter is size 3 ==> which mean that it have taken the '/r/n'
                if(line.size() == 3) {
                    // take the first letter at position 0 and create a pawn
                    addPawn(string(1, line.at(0)), Position{row,col}, color);
                    col++;
                    if(col > 9) {
                        col = 0;
                        row--;
                    }
                    // take the second letter at position 2 and create pawn
                    addPawn(string(1, line.at(2)), Position{row,col}, color);
                } else {
                    // if not letter with size 3.. it's ok just take his letter and create pawn
                    addPawn(line, Position{row, col}, color);
                }
                col++;
            }
        }
    }
}

void Game::addPawn(string role, Position position, Color color) {
    if(retrieveRole(role) == Role::FLAG || retrieveRole(role) == Role::BOMB) {
        Pawn pawn {retrieveRole(role), color, position, false};
        addPawn(pawn, position);
    } else {
        Pawn pawn {retrieveRole(role), color, position, true};
        addPawn(pawn, position);
    }
}

Role Game::retrieveRole(string role) {
    if(role == "10") {
        return Role::MARSHAL;
    } else if(role == "9") {
        return Role::GENERAL;
    } else if(role == "8") {
        return Role::COLONEL;
    } else if(role == "7") {
        return Role::MAJOR;
    } else if(role == "6") {
        return Role::COMMANDER;
    } else if(role == "5") {
        return Role::LIEUTENANT;
    } else if(role == "4") {
        return Role::SERGEANT;
    } else if(role == "3") {
        return Role::MINESWEEPER;
    } else if(role == "2") {
        return Role::SCOUT;
    } else if(role == "1") {
        return Role::SPY;
    } else if(role == "F") {
        return Role::FLAG;
    } else {
        return Role::BOMB;
    }
}

bool Game::isEnemy(Position position, Direction direction, Color color) {
    // move -> direction
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

    // check if new position is inside
    if(isInside(position)) {
        // check if at the new position there is a pawn valide
        if(board_.getPawns()[position.getX()][position.getY()]->isValide()) {
            // check if at the new position the pawn has different color as the color given in paramater
            // different color mean -> enemy
            if(board_.getPawns()[position.getX()][position.getY()]->getColor() != color) {
                // set this pawn (enemy) visible
                board_.setVisible(position.getX(), position.getY(), true);
                return true;
            }
        }
    }
    return false;
}

bool Game::isMovablePawn(Position position) {
    return board_.getPawns()[position.getX()][position.getY()]->isMovable();
}

bool Game::battle(Role pawn, Role enemy) {
    if(pawn == Role::SPY && enemy == Role::MARSHAL) {
        return true;
    } else if(enemy == Role::FLAG) {
        return true;
    }else if(pawn == Role::MINESWEEPER && enemy == Role::BOMB) {
        return true;
    } else if(pawn > enemy) {
        return true;
    } else {
        return false;
    }
}

bool Game::bothSameRole(Role pawn,Role enemy) {
    return pawn == enemy;
}

