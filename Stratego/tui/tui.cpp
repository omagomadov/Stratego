#include <iostream>
#include "tui.h"

View::View(Game& game) : game_ {game} {}

void View::displayWelcome() {
    cout << "###################################" << endl;
    cout << "#       Welcome on Stratego       #"<< endl;
    cout << "#          version: v1.0          #" << endl;
    cout << "###################################" << endl;
}

void View::displayBoard() {
    printf("%3s"," ");
    for(unsigned i = 1; i <= game_.getPawns().size(); i++) {
        cout << " " << i << " ";
    }
    cout << endl;
    for(unsigned row = 0; row < game_.getPawns().size(); row++) {
        printf("%3d", row + 1);
        for(unsigned col = 0; col < game_.getPawns().size(); col++) {
            if(game_.getPawns()[row][col].has_value()) {
                cout << " " << game_.getPawns()[row][col]->getRole() << " ";
            } else if(game_.isWater(row, col)) {
                cout << " x ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
}

void View::displayPlayer() {
    cout << "Current player is "
         << (game_.getCurrentPlayer() ? "blue" : "red") << endl;
}

void View::DisplayRemainingPawns() {
    cout << "##############################" << endl;
    cout << "Remaining pawns :" << endl;
    for(auto const& [key, val] : game_.getRemainingPawns()) {
        switch(key) {
        case Role::MARSHAL :
            cout << "Marshal : " << val << endl;
            break;
        case Role::GENERAL :
            cout << "General : " << val << endl;
            break;
        case Role::COLONEL :
            cout << "Colonel : " << val << endl;
            break;
        case Role::MAJOR :
            cout << "Major : " << val << endl;
            break;
        case Role::COMMANDER :
            cout << "Commander : " << val << endl;
            break;
        case Role::LIEUTENANT :
            cout << "Lieutenant : " << val << endl;
            break;
        case Role::SERGEANT :
            cout << "Sergeant : " << val << endl;
            break;
        case Role::MINESWEEPER :
            cout << "Minesweeper : " << val << endl;
            break;
        case Role::SCOUT :
            cout << "Scout : " << val << endl;
            break;
        case Role::SPY :
            cout << "Spy : " << val << endl;
            break;
        case Role::FLAG :
            cout << "Flag : " << val << endl;
            break;
        case Role::BOMB :
            cout << "Bomb : " << val << endl;
            break;
        }
    }
    cout << "##############################" << endl;
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

Controller::Controller(Game& game, View& view) : game_ {game}, view_ {view} {}

void Controller::start() {
    view_.displayWelcome();
    game_.initPawns();
    while(!game_.isEnd()) {
        view_.displayBoard();
        view_.displayPlayer();
        view_.DisplayRemainingPawns();
        Position position = view_.askPosition();
        Direction direction = view_.askDirection();
        while(!game_.isEmpty(position, direction)
              || game_.isWater(position.getX(), position.getY())) {
            cout << "Pawn goes outside the board or pawn can't go there !" << endl;
            position = view_.askPosition();
            direction = view_.askDirection();
        }
    }
    // method in construction. . .
    // method not yet finished. . .
}

