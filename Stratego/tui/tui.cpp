#include <iostream>
#include "tui.h"

View::View(Game game) : game_ {game} {}

void View::displayWelcome() {
    // todo
}

void View::displayBoard() {
    for(unsigned row = 0; row < game_.getPawns().size(); row++) {
        for(unsigned col = 0; col < game_.getPawns().size(); col++) {
            if(game_.getPawns()[row][col].has_value()) {
                cout << game_.getPawns()[row][col]->getRole() << " ";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void View::displayPlayer() {
    cout << "Current player is "
         << (game_.getCurrentPlayer() ? "blue" : "red") << endl;
}

Position View::askPosition() {
    int row, col;
    cout << "Enter the position of your pawn" << endl;
    cout << "Row : ";
    cin >> row;
    cout << "Column : ";
    cin >> col;
    Position pos {row, col};
    return pos;
}

Direction View::askDirection() {
    string direction;
    cout << "Enter the direction of your pawn :" << endl;
    cout << "F -> Forward | B -> Backward | L -> Left | R -> Right" << endl;
    cin >> direction;
    if(direction == "F") {
        return Direction::FORWARD;
    } else if(direction == "B") {
        return Direction::BACKWARD;
    } else if(direction == "L") {
        return Direction::LEFT;
    } else {
        return Direction::RIGHT;
    }
}

Controller::Controller(Game game, View view) : game_ {game}, view_ {view} {}

void Controller::start() {
    //todo
}

