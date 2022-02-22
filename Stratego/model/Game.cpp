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
    Position pos {position.getX(), position.getY()};
    switch(direction) {
    case Direction::FORWARD :
        pos.setX(pos.getX() - 1);
        if(board_.isInside(pos)) {
            position.setX(pos.getX());
        }
        break;
    case Direction::LEFT :
        pos.setY(pos.getY() - 1);
        if(board_.isInside(pos)) {
            position.setY(pos.getY());
        }
        break;
    case Direction::RIGHT :
        pos.setY(pos.getY() + 1);
        if(board_.isInside(pos)) {
            position.setY(pos.getY());
        }
        break;
    case Direction::BACKWARD :
        pos.setX(pos.getX() + 1);
        if(board_.isInside(pos)) {
            position.setX(pos.getX());
        }
        break;
    }
}

void Game::addPawn(Pawn pawn, Position position) {
    board_.addPawn(pawn, position);
}

void Game::fillBoard(string file, Color color) {
    // todo
}
