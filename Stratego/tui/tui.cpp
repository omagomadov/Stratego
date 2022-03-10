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
    printf("%3s", " ");
    for(unsigned i = 0; i < game_.getPawns().size(); i++) {
        printf("%3c", ('A' + i));
    }
    cout << endl;
    for(unsigned row = 0; row < game_.getPawns().size(); row++) {
        printf("%3d", row + 1);
        for(unsigned col = 0; col < game_.getPawns().size(); col++) {
            if(game_.getPawns()[row][col].has_value()) {
                if(game_.getLevel() == 1) {
                    switch(game_.getPawns()[row][col]->getRole()) {
                    case FLAG :
                        printf("%3s", "F");
                        break;
                    case BOMB :
                        printf("%3s", "B");
                        break;
                    default:
                        printf("%3d", game_.getPawns()[row][col]->getRole());
                        break;
                    }
                } else {
                    if(game_.getPawns()[row][col]->getColor() == game_.getCurrentPlayer()
                            || game_.getPawns()[row][col]->isVisible()) {
                        switch(game_.getPawns()[row][col]->getRole()) {
                        case FLAG :
                            printf("%3s", "F");
                            break;
                        case BOMB :
                            printf("%3s", "B");
                            break;
                        default:
                            printf("%3d", game_.getPawns()[row][col]->getRole());
                            break;
                        }
                    }
                }
            } else if(game_.isWater(row, col)) {
                printf("%3s", "x");
            } else {
                printf("%3s", ".");
            }
        }
        cout << endl;
    }
}

void View::displayPlayer() {
    cout << "Current player is "
         << (game_.getCurrentPlayer() ? "blue" : "red") << endl;
}

void View::displayRemainingPawns() {
    cout << "#################################" << endl;
    cout << "Remaining pawns :" << endl;
    for(auto const& [key, val] : game_.getRemainingPawns()) {
        switch(key) {
        case Role::MARSHAL :
            cout << "[1]  Marshal : " << val << endl;
            break;
        case Role::GENERAL :
            cout << "[2]  General : " << val << endl;
            break;
        case Role::COLONEL :
            cout << "[3]  Colonel : " << val << endl;
            break;
        case Role::MAJOR :
            cout << "[4]  Major : " << val << endl;
            break;
        case Role::COMMANDER :
            cout << "[5]  Commander : " << val << endl;
            break;
        case Role::LIEUTENANT :
            cout << "[6]  Lieutenant : " << val << endl;
            break;
        case Role::SERGEANT :
            cout << "[7]  Sergeant : " << val << endl;
            break;
        case Role::MINESWEEPER :
            cout << "[8]  Minesweeper : " << val << endl;
            break;
        case Role::SCOUT :
            cout << "[9]  Scout : " << val << endl;
            break;
        case Role::SPY :
            cout << "[10] Spy : " << val << endl;
            break;
        case Role::FLAG :
            cout << "[11] Flag : " << val << endl;
            break;
        case Role::BOMB :
            cout << "[12] Bomb : " << val << endl;
            break;
        }
    }
    cout << "#################################" << endl;
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

int View::askPawn() {
    int pawn;
    cout << "Which pawn do you want to set :" << endl;
    cin >> pawn;
    if(pawn < 1 || pawn > 12) {
        return -1;
    }
    return pawn;
}

int View::askLevel() {
    char level = 0;
    cout << "Which level do you want :" << endl;
    cout << "[1] Easy\n"
            "[2] Normal" << endl;
    cin >> level;
    switch(level) {
    case '1' :
        return 1;
        break;
    case '2' :
        return 2;
        break;
    default :
        return -1;
    }
}

Controller::Controller(Game& game, View& view) : game_ {game}, view_ {view} {}

void Controller::start() {
    Position position;
    Direction direction;
    int choice;
    int level;
    view_.displayWelcome();
    level = view_.askLevel();
    while(level < 0) {
        level = view_.askLevel();
    }
    game_.setLevel(level);
    while(!game_.isEnd()) {
        // controller is not yet finished.. must be decomposed in multiple different method because to long
        while(game_.getState() != State::STARTED) {
            game_.initPawns();
            game_.setState(State::BLUE_TURN);
            game_.setCurrentPlayer(Color::BLUE);
            while(game_.getState() == State::BLUE_TURN) {
                view_.displayBoard();
                view_.displayRemainingPawns();
                choice = view_.askPawn();
                while(choice == -1 || !game_.isAvailable(choice)) {
                    cout << "Please enter a number between 1 and 12 both included"
                            " or this pawn is no longer available" << endl;
                    choice = view_.askPawn();
                }
                game_.decrementPawnCount(choice);
                position = view_.askPosition();
                while(!game_.isInside(position) || !(position.getX() <= 3)
                      || game_.isPawn(position)) {
                    cout << "Please enter a valid position" << endl;
                    position = view_.askPosition();
                }
                game_.addPawn(choice, Color::BLUE, position);
                if(game_.isAllPawnsPlaced()) {
                    game_.setState(State::RED_TURN);
                }
            }
            game_.initPawns();
            game_.setCurrentPlayer(Color::RED);
            while(game_.getState() == State::RED_TURN) {
                view_.displayBoard();
                view_.displayRemainingPawns();
                choice = view_.askPawn();
                while(choice == -1 || !game_.isAvailable(choice)) {
                    cout << "Please enter a number between 1 and 12 both included" << endl;
                    choice = view_.askPawn();
                }
                game_.decrementPawnCount(choice);
                position = view_.askPosition();
                while(!game_.isInside(position) || !(position.getX() >= 6)) {
                    cout << "Please enter a valid position" << endl;
                    position = view_.askPosition();
                }
                game_.addPawn(choice, Color::RED, position);
                if(game_.isAllPawnsPlaced()) {
                    game_.setState(State::STARTED);
                }
            }
        }
        view_.displayBoard();
        view_.displayPlayer();
        position = view_.askPosition();
        direction = view_.askDirection();
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

