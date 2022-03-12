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
                    } else {
                        if(game_.getCurrentPlayer() == Color::BLUE) {
                            printf("%3s", "R");
                        } else {
                            printf("%3s", "B");
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
        case Role::SPY :
            cout << "[1]  Spy : " << val << endl;
            break;
        case Role::SCOUT :
            cout << "[2]  Scout : " << val << endl;
            break;
        case Role::MINESWEEPER :
            cout << "[3]  Minesweeper : " << val << endl;
            break;
        case Role::SERGEANT :
            cout << "[4]  Sergeant : " << val << endl;
            break;
        case Role::LIEUTENANT :
            cout << "[5]  Lieutenant : " << val << endl;
            break;
        case Role::COMMANDER :
            cout << "[6]  Commander : " << val << endl;
            break;
        case Role::MAJOR :
            cout << "[7]  Major : " << val << endl;
            break;
        case Role::COLONEL :
            cout << "[8]  Colonel : " << val << endl;
            break;
        case Role::GENERAL :
            cout << "[9]  General : " << val << endl;
            break;
        case Role::MARSHAL :
            cout << "[10] Marshal : " << val << endl;
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

void View::displayCurrentPlayer() {
    switch(game_.getCurrentPlayer()) {
    case Color::BLUE :
        cout << "Current player is blue" << endl;
        break;
    case Color::RED :
        cout << "Current player is red" << endl;
        break;
    }
}

Position View::askPosition() {
    int row, col;
    cout << "Enter the position of your pawn" << endl;
    cout << "Row : ";
    cin >> row;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter a number" << endl;
        cout << "Row : ";
        cin >> row;
    }
    cout << "Column : ";
    cin >> col;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter a number" << endl;
        cout << "Column : ";
        cin >> col;
    }
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
    while(pawn < 1 || pawn > 12 || cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    return pawn;
}

int View::askLevel() {
    int level = 0;
    cout << "Which level do you want :" << endl;
    cout << "[1] Easy\n"
            "[2] Normal" << endl;
    cin >> level;
    while(level <= 0 || level >= 3 || cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter a number between 1 and 2 included" << endl;
        cout << "[1] Easy\n"
                "[2] Normal" << endl;
        cin >> level;
    }
    return level;
}

int View::askBoardInitialization() {
    int choice;
    cout << "Which type of initialization do want to do ?" << endl;
    cout << "[1] Manual" << endl;
    cout << "[2] File" << endl;
    cin >> choice;
    while(choice <= 0 || choice >= 3|| cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please enter a number between 1 and 2 included" << endl;
        cout << "[1] Manual" << endl;
        cout << "[2] File" << endl;
        cin >> choice;
    }
    return choice;
}

Controller::Controller(Game& game, View& view) : game_ {game}, view_ {view} {}

void Controller::start() {
    int choice = 0;
    Direction direction;
    Position position;
    Role role = Role::BOMB;
    array<Role, 12> roles {Role::SPY, Role::SCOUT, Role::MINESWEEPER, Role::SERGEANT, Role::LIEUTENANT, Role::COMMANDER,
                Role::MAJOR, Role::COLONEL, Role::GENERAL, Role::MARSHAL, Role::FLAG, Role::BOMB};
    view_.displayWelcome();
    view_.askBoardInitialization();
    game_.setLevel(view_.askLevel());
    blue_init(choice, role, position, roles);
    red_init(choice, role, position, roles);
    play(position, direction);
}

void Controller::play(Position& position, Direction& direction) {
    while(!game_.isEnd()) {
        view_.displayCurrentPlayer();
        view_.displayBoard();
        // player X chose his pawn
        cout << "Choose your pawn" << endl;
        position = view_.askPosition();
        while(true) {
            if(game_.isInside(position)) {
                if(game_.isPawn(position)) {
                    if(game_.isPawnSameColor(position)) {
                        // is the position is inside the board
                        // is the pawn at this position is really a pawn
                        // is the pawn is your pawn => then break
                        break;
                    } else {
                        cout << "Not your pawn" << endl;
                    }
                } else {
                    cout << "No pawn at this position" << endl;
                }
            } else {
                cout << "Position outside the board" << endl;
            }
            position = view_.askPosition();
        }

        // player X chose where to move his pawn
        cout << "Where do you want to move this pawn" << endl;
        direction = view_.askDirection();
        while(!game_.isEmpty(position, direction)
              || game_.isWater(position.getX(), position.getY())) {
            cout << "Pawn goes outside the board or pawn can't go there!" << endl;
            direction = view_.askDirection();
        }

        // move his pawn
        game_.move(position, direction);
        // switch to next player
        game_.nextPlayer();
    }
}

void Controller::red_init(int choice, Role role, Position position, array<Role, 12> roles) {
    game_.initPawns();
    game_.setCurrentPlayer(Color::RED);
    while(game_.getState() == State::RED_TURN) {
        view_.displayBoard();
        view_.displayRemainingPawns();
        choice = view_.askPawn();
        while(true) {
            if(choice != -1) {
                role = roles.at(choice - 1);
                if(game_.isAvailable(role)) {
                    // if pawn number is correct and the pawn is available
                    break;
                } else {
                    cout << "Maximum number of this pawn is placed" << endl;
                }
            } else {
                cout << "Please enter a number between 1 and 12 both included" << endl;
            }
            choice = view_.askPawn();
        }
        role = roles.at(choice - 1);
        game_.decrementPawnCount(role);
        position = view_.askPosition();
        while(!game_.isInside(position) || !(position.getX() >= 6)
              || game_.isPawn(position)) {
            cout << "Please enter a valid position" << endl;
            position = view_.askPosition();
        }
        Pawn pawn {role, Color::RED, position, true};
        game_.addPawn(pawn, position);
        if(game_.isAllPawnsPlaced()) {
            game_.setState(State::STARTED);
        }
    }
}

void Controller::blue_init(int choice, Role role, Position position, array<Role, 12> roles) {
    game_.initPawns();
    game_.setState(State::BLUE_TURN);
    game_.setCurrentPlayer(Color::BLUE);
    while(game_.getState() == State::BLUE_TURN) {
        view_.displayBoard();
        view_.displayRemainingPawns();
        choice = view_.askPawn();
        while(true) {
            if(choice != -1) {
                role = roles.at(choice - 1);
                if(game_.isAvailable(role)) {
                    // if pawn number is correct and the pawn is available
                    break;
                } else {
                    cout << "Maximum number of this pawn is placed" << endl;
                }
            } else {
                cout << "Please enter a number between 1 and 12 both included" << endl;
            }
            choice = view_.askPawn();
        }
        role = roles.at(choice - 1);
        game_.decrementPawnCount(role);
        position = view_.askPosition();
        while(!game_.isInside(position) || !(position.getX() <= 3)
              || game_.isPawn(position)) {
            cout << "Please enter a valid position" << endl;
            position = view_.askPosition();
        }
        Pawn pawn {role, Color::BLUE, position, true};
        game_.addPawn(pawn, position);
        if(game_.isAllPawnsPlaced()) {
            game_.setState(State::RED_TURN);
        }
    }
}
