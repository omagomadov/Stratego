#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <unistd.h>
#include "tui.h"

View::View(Game& game) : game_ {game} {}

void View::displayWelcome() {
    cout << "###################################" << endl;
    cout << "#       Welcome on Stratego       #"<< endl;
    cout << "#          version: v1.0          #" << endl;
    cout << "###################################" << endl;
}

void View::displayBoard() {
    cout << " " << endl;
    printf("%3s", " ");
    for(unsigned i = 0; i < game_.getPawns().size(); i++) {
        printf("%3c", ('A' + i));
    }
    cout << endl;
    for(unsigned row = 0; row < game_.getPawns().size(); row++) {
        printf("%3u", row + 1);
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
            } else if(game_.isWater(Position {(int)row, (int)col})) {
                printf("%3s", "x");
            } else {
                printf("%3s", ".");
            }
        }
        cout << endl;
    }
    cout << " " << endl;
}

void View::displayBattle() {
    cout << "############ BATTLE ! ############" << endl;
    displayBoard();
    cout << "##################################" << endl;
    sleep(2);
}

void View::displayPlayer() {
    cout << "==============================" << endl;
    cout << "Current player is "
         << (game_.getCurrentPlayer() ? "blue" : "red") << endl;
    cout << "==============================" << endl;
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

void View::displayWinner() {
    cout << "==============================" << endl;
    cout << "The winner is "
         << (game_.getCurrentPlayer() ? "blue" :  "red") << endl;
    cout << "==============================" << endl;
}

Position View::askPosition() {
    int row, col;
    char letter;
    cout << ">> Choose your pawn" << endl;
    cout << "Enter the position of your pawn" << endl;
    cout << "Row : ";
    cin >> row;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "[!] Please enter a number" << endl;
        cout << "Row : ";
        cin >> row;
    }
    cout << "Column : ";
    cin >> letter;
    switch(letter) {
    case 'A':
        col = 1;
        break;
    case 'B':
        col = 2;
        break;
    case 'C':
        col = 3;
        break;
    case 'D':
        col = 4;
        break;
    case 'E':
        col = 5;
        break;
    case 'F':
        col = 6;
        break;
    case 'G':
        col = 7;
        break;
    case 'H':
        col = 8;
        break;
    case 'I':
        col = 9;
        break;
    case 'J':
        col = 10;
        break;

    default:
        col= -1;
        break;
    }
    Position pos {row - 1, col - 1};
    return pos;
}

Direction View::askDirection() {
    string direction;
    cout << ">> Where do you want to move this pawn" << endl;
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
    cout << ">> Which pawn do you want to set :" << endl;
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
    cout << ">> Which level do you want :" << endl;
    cout << "[1] Easy\n"
            "[2] Normal" << endl;
    cin >> level;
    while(level <= 0 || level >= 3 || cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "[!] Please enter a number between 1 and 2 included" << endl;
        cout << "[1] Easy\n"
                "[2] Normal" << endl;
        cin >> level;
    }
    return level;
}

int View::askBoardInitialization() {
    int choice;
    cout << ">> Which type of initialization do you want to do?" << endl;
    cout << "[1] Manual" << endl;
    cout << "[2] File" << endl;
    cin >> choice;
    while(choice <= 0 || choice >= 3 || cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "[!] Please enter a number between 1 and 2 included" << endl;
        cout << "[1] Manual" << endl;
        cout << "[2] File" << endl;
        cin >> choice;
    }
    return choice;
}

int View::askMovement() {
    int moves;
    cout << ">> How much moves do you want to do?" << endl;
    cin >> moves;
    while(cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "[!] Please enter only numbers" << endl;
        cin >> moves;
    }
    return moves;
}

string View::askFileName() {
    string file;
    cout << ">> What is the name of the file?" << endl;
    cin >> file;
    return file;
}

Controller::Controller(Game& game, View& view) : game_ {game}, view_ {view} {}

void Controller::start() {
    int choice = 0;
    Direction direction;
    Position position;
    Role role = Role::BOMB;
    array<Role, 12> roles {Role::SPY, Role::SCOUT, Role::MINESWEEPER, Role::SERGEANT, Role::LIEUTENANT, Role::COMMANDER,
                Role::MAJOR, Role::COLONEL, Role::GENERAL, Role::MARSHAL, Role::FLAG, Role::BOMB};
    // Display welcome message
    view_.displayWelcome();
    // Ask the level (easy or normal)
    game_.setLevel(view_.askLevel());
    // Initialize each players board (each user choose if he want initialize manually or with file)
    initPlayers(choice, role, position, roles);
    // Launch the game
    play(position, direction);
}

void Controller::play(Position& position, Direction& direction) {
    while(game_.getState() == State::STARTED) {
        view_.displayPlayer();
        view_.displayBoard();
        // Ask position
        position = view_.askPosition();
        // Ask while is correct
        while(!checkPosition(position)) {
            position = view_.askPosition();
        }
        // Ask direction
        direction = view_.askDirection();
        // Ask while pawn go nowhere or on water
        while(!checkDirection(position, direction)) {
            cout << "[!] Pawn can't attack his teammate or go on the water" << endl;
            direction = view_.askDirection();
        }
        if(game_.getRole(position) == Role::SCOUT) {
            int movement = view_.askMovement();
            while(movement > 0 && game_.isInside(position, direction)
                  && !game_.isPawn(position, direction)) {
                game_.move(position, direction);
                movement--;
            }
            if(game_.isEnemy(position, direction, game_.getCurrentPlayer())) {
                // display the board with the pawn of the enemy visible
                view_.displayBattle();
                // start battle
                game_.battle(position, direction);
            }
        } else {
            // check if there is a enemy
            if(game_.isEnemy(position, direction, game_.getCurrentPlayer())) {
                // display the board with the pawn of the enemy visible
                view_.displayBattle();
                // start battle
                game_.battle(position, direction);
            } else {
                // move his pawn
                game_.move(position, direction);
            }
        }
        if(game_.getState() != State::ENDED) {
            // switch to next player
            game_.nextPlayer();
        }
    }
    view_.displayWinner();
}

void Controller::initPlayers(int choice, Role role, Position position, array<Role, 12> roles) {
    fstream file;
    string name;
    game_.setCurrentPlayer(Color::BLUE);
    // Player blue choose -> manual or file
    view_.displayPlayer();
    while(true) {
        choice = view_.askBoardInitialization();
        if(choice == 1) {
            initBlueBoard(choice, role, position, roles);
            break;
        } else {
            name = view_.askFileName();
            file.open(name);
            if(file.is_open()) {
                // I guarantee that FillBoard() receives a file that exists
                file.close();
                cout << "File successfully opened" << endl;
                if(!analyseFile(name)) {
                    cout << "An error occurs" << endl;
                    cout << "The file contains invalid data" << endl;
                } else {
                    game_.fillBoard(name, game_.getCurrentPlayer());
                    game_.setState(State::RED_TURN);
                    break;
                }
            } else {
                cout << "File not found" << endl;
            }
        }
    }
    game_.nextPlayer();
    // Player red choose -> manual or file
    view_.displayPlayer();
    while(true) {
        choice = view_.askBoardInitialization();
        if(choice == 1) {
            initRedBoard(choice, role, position, roles);
            break;
        } else {
            name = view_.askFileName();
            file.open(name);
            if(file.is_open()) {
                // I guarantee that FillBoard() receives a file that exists
                file.close();
                cout << "File successfully opened" << endl;
                if(!analyseFile(name)) {
                    cout << "An error occurs" << endl;
                    cout << "The file contains invalid data" << endl;
                } else {
                    game_.fillBoard(name, game_.getCurrentPlayer());
                    game_.setState(State::STARTED);
                    break;
                }
            } else {
                cout << "File not found" << endl;
            }
        }
    }
}

void Controller::initRedBoard(int choice, Role role, Position position, array<Role, 12> roles) {
    game_.initPawns();
    game_.setCurrentPlayer(Color::RED);
    while(game_.getState() == State::RED_TURN) {
        view_.displayPlayer();
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

void Controller::initBlueBoard(int choice, Role role, Position position, array<Role, 12> roles) {
    game_.initPawns();
    game_.setState(State::BLUE_TURN);
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

bool Controller::analyseFile(string name) {
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

bool Controller::checkPosition(Position position) {
    // Check if the position is inside
    if(game_.isInside(position)) {
        // Checks if the there is a pawn at this position
        if(game_.isPawn(position)) {
            // Checks if the selected pawn is your pawn (pawn color == current player color)
            if(game_.isPawnSameColor(position)) {
                if(game_.isMovablePawn(position)) {
                    if(game_.isAlone(position)) {
                        return true;
                    } else {
                        cout << "[!] This pawn can't move because he has no exit" << endl;
                    }
                } else {
                    cout << "[!] This pawn is not movable" << endl;
                }
            } else {
                cout << "[!] Not your pawn" << endl;
            }
        } else {
            cout << "[!] No pawn at this position" << endl;
        }
    } else {
        cout << "[!] Position outside the board" << endl;
    }
    return false;
}

bool Controller::checkDirection(Position position, Direction direction) {
    if(game_.isWater(position, direction) || game_.isPawnSameColor(position, direction)) {
        return false;
    }
    return true;
}
