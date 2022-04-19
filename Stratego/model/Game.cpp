#include <fstream>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "Game.h"

using namespace std;
using namespace stratego;

Game::Game() {
    state_ = State::NOT_STARTED;
}

void Game::addObserver(Observer * observer) {
    observers_.insert(observer);
}

void Game::removeObserver(Observer * observer) {
    observers_.erase(observer);
}

void Game::notifyObserver() {
    for(Observer * observer : observers_) {
        observer->update();
    }
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

Role Game::getRole(Position position) {
    return board_.getRole(position);
}

bool Game::isInside(Position position) {
    return board_.isInside(position);
}

bool Game::isInside(Position position, Direction direction) {
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
    return board_.isInside(position);
}

bool Game::isPawn(Position position) {
    if(isInside(position)) {
        return board_.getPawns()[position.getX()][position.getY()]->isValide();
    }
    return false;
}

bool Game::isPawn(Position position, Direction direction) {
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
        return board_.getPawns()[position.getX()][position.getY()]->isValide();
    }
    return false;
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
    // store bool who indicate that the box is empty at position + direction
    bool emptyBox = isEmpty(position, direction);
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
        if(!emptyBox) {
            if(board_.getPawns()[position.getX()][position.getY()]->getColor() == currentPlayer_) {
                return true;
            }
        }
    }
    return false;
}

bool Game::isAlone(Position position) {
    return board_.isAlone(position);
}

void Game::move(Position& position, Direction direction) {
    optional<Pawn> empty;
    optional<Pawn> pawn = board_.getPawns()[position.getX()][position.getY()];
    if(getRole(position) == Role::BOMB || getRole(position) == Role::FLAG) {
        throw invalid_argument("Pawn can't move");
    }
    switch(direction) {
    case Direction::FORWARD :
        board_.setPawn(empty, position);
        position.setX(position.getX() - 1);
        board_.setPawn(pawn, position);
        board_.setPosition(position, position);
        break;
    case Direction::LEFT :
        board_.setPawn(empty, position);
        position.setY(position.getY() - 1);
        board_.setPawn(pawn, position);
        board_.setPosition(position, position);
        break;
    case Direction::RIGHT :
        board_.setPawn(empty, position);
        position.setY(position.getY() + 1);
        board_.setPawn(pawn, position);
        board_.setPosition(position, position);
        break;
    case Direction::BACKWARD :
        board_.setPawn(empty, position);
        position.setX(position.getX() + 1);
        board_.setPawn(pawn, position);
        board_.setPosition(position, position);
        break;
    }
}

bool Game::isEmpty(Position position, Direction direction) {
    return board_.isEmpty(position, direction);
}

bool Game::isWater(Position position, Direction direction) {
    return board_.isWater(position, direction);
}

bool Game::isWater(Position position) {
    return board_.isWater(position.getX(), position.getY());
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

void Game::setPosition(Position onBoard, Position newPos) {
    board_.setPosition(onBoard, newPos);
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

bool Game::analyseFile(string name) {
    fstream file;
    int count = 0;
    map<string, int> pawns;
    pawns.insert({"1", 1});
    pawns.insert({"2", 8});
    pawns.insert({"3", 5});
    pawns.insert({"4", 4});
    pawns.insert({"5", 4});
    pawns.insert({"6", 4});
    pawns.insert({"7", 3});
    pawns.insert({"8", 2});
    pawns.insert({"9", 1});
    pawns.insert({"10", 1});
    pawns.insert({"B", 6});
    pawns.insert({"F", 1});
    file.open(name);
    string acceptedPawns {"1 2 3 4 5 6 7 8 9 10 B F"};
    while(!file.eof()) {
        // for each line delimited with ' '
        for (string line; getline(file, line, ' '); ) {
            // if value size is 2 and first char is not in accepted => have \r\n
            if(line.size() == 3) {
                if((acceptedPawns.find(line.at(0)) != string::npos) &&
                        (acceptedPawns.find(line.at(2)) != string::npos)) {
                    pawns[string(1, line.at(0))] = pawns[string(1, line.at(0))] - 1;
                    pawns[string(1, line.at(2))] = pawns[string(1, line.at(2))] - 1;
                } else {
                    file.close();
                    return false;
                }
            } else {
                pawns[line] = pawns[line] - 1;
                // return false immediately if a value is not a accepted pawn (avoid useless loop !)
                // (or) maximum number of pawns exceeded
                // (or) maximum (max. 40 pawns) number of pawns on the board exceeded
                if(acceptedPawns.find(line) == string::npos || count > 40 || pawns[line] < 0) {
                    file.close();
                    return false;
                }
            }
            count++;
        }
    }
    // if count => 0. That mean that there is no pawn
    if(count == 0) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

void Game::addPawn(const string role, Position position, Color color) {
    if(retrieveRole(role) == Role::FLAG || retrieveRole(role) == Role::BOMB) {
        Pawn pawn {retrieveRole(role), color, position, false};
        addPawn(pawn, position);
    } else {
        Pawn pawn {retrieveRole(role), color, position, true};
        addPawn(pawn, position);
    }
}

Role Game::retrieveRole(const string role) {
    switch(atoi(role.c_str())) {
    case 1 :
        return Role::SPY;
        break;
    case 2 :
        return Role::SCOUT;
        break;
    case 3 :
        return Role::MINESWEEPER;
        break;
    case 4 :
        return Role::SERGEANT;
        break;
    case 5 :
        return Role::LIEUTENANT;
        break;
    case 6 :
        return Role::COMMANDER;
        break;
    case 7 :
        return Role::MAJOR;
        break;
    case 8 :
        return Role::COLONEL;
        break;
    case 9 :
        return Role::GENERAL;
        break;
    case 10 :
        return Role::MARSHAL;
        break;
    default:
        if(role == "F") {
            return Role::FLAG;
        } else {
            return Role::BOMB;
        }
        break;
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

bool Game::compare(Role pawn, Role enemy) {
    if(enemy == Role::FLAG) {
        setState(State::ENDED);
        return true;
    } else if(pawn == Role::MINESWEEPER && enemy == Role::BOMB) {
        return true;
    } else if(pawn == Role::SPY && enemy == Role::MARSHAL) {
        return true;
    } else if(enemy == Role::BOMB) {
        return false;
    }
    return pawn > enemy;
}

bool Game::bothSameRole(Role pawn,Role enemy) {
    return pawn == enemy;
}

void Game::battle(Position position, Direction direction) {
    optional<Pawn> empty;
    optional<Pawn> pawn = board_.getPawns()[position.getX()][position.getY()];
    optional<Pawn> enemy;
    switch(direction) {
    case Direction::FORWARD :
        enemy = board_.getPawns()[position.getX() - 1][position.getY()];
        if(bothSameRole(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, pawn->getPosition());
            board_.setPawn(empty, enemy->getPosition());
        } else if(compare(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, enemy->getPosition());
            move(position, direction);
        } else {
            board_.setPawn(empty, pawn->getPosition());
            board_.setVisible(position.getX() - 1, position.getY(), false);
        }
        break;
    case Direction::BACKWARD :
        enemy = board_.getPawns()[position.getX() + 1][position.getY()];
        if(bothSameRole(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, pawn->getPosition());
            board_.setPawn(empty, enemy->getPosition());
        } else if(compare(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, enemy->getPosition());
            move(position, direction);
        } else {
            board_.setPawn(empty, pawn->getPosition());
            board_.setVisible(position.getX() + 1, position.getY(), false);
        }
        break;
    case Direction::LEFT :
        enemy = board_.getPawns()[position.getX()][position.getY() - 1];
        if(bothSameRole(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, pawn->getPosition());
            board_.setPawn(empty, enemy->getPosition());
        } else if(compare(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, enemy->getPosition());
            move(position, direction);
        } else {
            board_.setPawn(empty, pawn->getPosition());
            board_.setVisible(position.getX(), position.getY() - 1, false);
        }
        break;
    case Direction::RIGHT :
        enemy = board_.getPawns()[position.getX()][position.getY() + 1];
        if(bothSameRole(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, pawn->getPosition());
            board_.setPawn(empty, enemy->getPosition());
        } else if(compare(pawn->getRole(), enemy->getRole())) {
            board_.setPawn(empty, enemy->getPosition());
            move(position, direction);
        } else {
            board_.setPawn(empty, pawn->getPosition());
            board_.setVisible(position.getX(), position.getY() + 1, false);
        }
        break;
    }
}

