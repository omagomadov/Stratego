#include "Game.h"

Game::Game() {}

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

void Game::addPawn(Pawn pawn, Position position) {
    board_.addPawn(pawn, position);
}

void Game::initPawns() {
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

void Game::fillBoard(string file, Color color) {
    // todo
}
