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
        board_.getPawns()[position.getX()][position.getY()] = empty;
        position.setX(position.getX() - 1);
        board_.getPawns()[position.getX()][position.getY()] = pawn;
        break;
    case Direction::LEFT :
        board_.getPawns()[position.getX()][position.getY()] = empty;
        position.setY(position.getY() - 1);
        board_.getPawns()[position.getX()][position.getY()] = pawn;
        break;
    case Direction::RIGHT :
        board_.getPawns()[position.getX()][position.getY()] = empty;
        position.setY(position.getY() + 1);
        board_.getPawns()[position.getX()][position.getY()] = pawn;
        break;
    case Direction::BACKWARD :
        board_.getPawns()[position.getX()][position.getY()] = empty;
        position.setX(position.getX() + 1);
        board_.getPawns()[position.getX()][position.getY()] = pawn;
        break;
    }
}

bool Game::isEmpty(Position position, Direction direction) {
    return board_.isEmpty(position, direction);
}

void Game::addPawn(Pawn pawn, Position position) {
    board_.addPawn(pawn, position);
}

void Game::fillBoard(string file, Color color) {
    // todo
}
