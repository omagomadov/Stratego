#include <Catch.h>
#include <Board.h>
#include <Game.h>
#include <iostream>

TEST_CASE("Test_model")
{
    SECTION("isInside_true")
    {
        Board board {};
        Position position {0,0};
        REQUIRE(board.isInside(position) == true);
    }

    SECTION("isInside_false_row")
    {
        Board board {};
        Position position {-9,10};
        REQUIRE(board.isInside(position) == false);
    }

    SECTION("isInside_false_column")
    {
        Board board {};
        Position position {9,-10};
        REQUIRE(board.isInside(position) == false);
    }


    SECTION("isEmpty_true_BACKWARD")
    {
        Board board {};
        Position position {0,0};
        Direction direction {Direction::BACKWARD};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("isEmpty_true_FORWARD")
    {
        Board board {};
        Position position {1,0};
        Direction direction {Direction::FORWARD};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("isEmpty_true_LEFT")
    {
        Board board {};
        Position position {1,1};
        Direction direction {Direction::LEFT};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("isEmpty_true_RIGHT")
    {
        Board board {};
        Position position {1,1};
        Direction direction {Direction::RIGHT};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("isEmpty_false_BACKWARD")
    {
        Board board {};
        Position position {0,0};
        Direction direction {Direction::BACKWARD};
        Pawn pawn {Role::COLONEL, Color::RED, Position{1,0}, true};
        board.addPawn(pawn, Position{1,0});
        REQUIRE(board.isEmpty(position, direction) == false);
    }

    SECTION("isEmpty_false_FORWARD")
    {
        Board board {};
        Position position {1,0};
        Direction direction {Direction::FORWARD};
        Pawn pawn {Role::COLONEL, Color::RED, Position{0,0}, true};
        board.addPawn(pawn, Position{0,0});
        REQUIRE(board.isEmpty(position, direction) == false);
    }

    SECTION("isEmpty_false_LEFT")
    {
        Board board {};
        Position position {1,1};
        Direction direction {Direction::LEFT};
        Pawn pawn {Role::COLONEL, Color::RED, Position{1,0}, true};
        board.addPawn(pawn, Position{1,0});
        REQUIRE(board.isEmpty(position, direction) == false);
    }

    SECTION("isEmpty_false_RIGHT")
    {
        Board board {};
        Position position {1,0};
        Direction direction {Direction::RIGHT};
        Pawn pawn {Role::COLONEL, Color::RED, Position{1,1}, true};
        board.addPawn(pawn, Position{1,1});
        REQUIRE(board.isEmpty(position, direction) == false);
    }

    SECTION("isWater_01_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,2) == true);
    }

    SECTION("isWater_02_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,2) == true);
    }

    SECTION("isWater_03_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,3) == true);
    }

    SECTION("isWater_04_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,3) == true);
    }

    SECTION("isWater_01_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,6) == true);
    }

    SECTION("isWater_02_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,7) == true);
    }

    SECTION("isWater_03_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,6) == true);
    }

    SECTION("isWater_04_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,7) == true);
    }

    SECTION("isWater_can_not_move_1")
    {
        Board board {};
        REQUIRE(board.isWater(5,7) == true);
    }

    SECTION("isAlone_1_corner_false")
    {
        Board board {};
        Position test {0,0};
        // init position
        Position first_pawn {0,1};
        Position second_pawn {1,0};
        Position third_pawn {1,1};
        // init pawn
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("isAlone_2_corner_false")
    {
        Board board {};
        Position test {9,0};
        // init position
        Position first_pawn {8,0};
        Position second_pawn {8,1};
        Position third_pawn {9,1};
        // init pawn
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("isAlone_3_corner_false")
    {
        Board board {};
        Position test {0,9};
        // init position
        Position first_pawn {0,8};
        Position second_pawn {1,8};
        Position third_pawn {1,9};
        // init pawn
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("isAlone_4_corner_false")
    {
        Board board {};
        Position test {9,9};
        // init position
        Position first_pawn {9,8};
        Position second_pawn {8,8};
        Position third_pawn {8,9};
        // init pawn
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("isAlone_5_true")
    {
        Board board {};
        Position test {3,4};
        // init position
        Position first_pawn {2,3};
        Position second_pawn {2,4};
        Position third_pawn {2,5};
        // init pawn
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == true);
    }

    SECTION("addPawn_isValide_1")
    {
        Board board {};
        Position position {0,0};
        Pawn pawn {Role::MAJOR, Color::BLUE, position, true};
        board.addPawn(pawn, position);
        REQUIRE(board.getPawns()[0][0]->isValide() == true);
    }

    SECTION("isValide_1")
    {
        Board board {};
        Position position {0,0};
        REQUIRE(board.getPawns()[0][0]->isValide() == false);
    }

    SECTION("isEnemy_true_FORWARD")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {0,4};
        Pawn enemy {Role::COMMANDER, Color::BLUE, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::FORWARD, myColor) == true);
    }

    SECTION("isEnemy_true_BACKWARD")
    {
        Game game {};
        Color myColor = Color::BLUE;
        Position myPosition {1,4};
        Position enemyPosition {2,4};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::BACKWARD, myColor) == true);
    }

    SECTION("isEnemy_true_LEFT")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {1,3};
        Pawn enemy {Role::COMMANDER, Color::BLUE, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::LEFT, myColor) == true);
    }

    SECTION("isEnemy_true_RIGHT")
    {
        Game game {};
        Color myColor = Color::BLUE;
        Position myPosition {1,4};
        Position enemyPosition {1,5};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::RIGHT, myColor) == true);
    }

    SECTION("isEnemy_false_FORWARD")
    {
        Game game {};
        Color myColor = Color::BLUE;
        Position myPosition {1,4};
        Position enemyPosition {0,4};
        Pawn enemy {Role::COMMANDER, Color::BLUE, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::FORWARD, myColor) == false);
    }

    SECTION("isEnemy_false_BACKWARD")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {2,4};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::BACKWARD, myColor) == false);
    }

    SECTION("isEnemy_false_LEFT")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {1,3};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::LEFT, myColor) == false);
    }

    SECTION("isEnemy_true_RIGHT")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {1,5};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::RIGHT, myColor) == false);
    }

    SECTION("move_FORWARD")
    {
        Game game {};
        Position position {1,4};
        Pawn pawn {Role::COMMANDER, Color::RED, position, true};
        game.addPawn(pawn, position);
        game.move(position, Direction::FORWARD);
        Position expected {0,4};
        Position result = game.getPawns()[0][4]->getPosition();
        REQUIRE(expected == result);
    }

    SECTION("move_BACKWARD")
    {
        Game game {};
        Position position {1,4};
        Pawn pawn {Role::COMMANDER, Color::RED, position, true};
        game.addPawn(pawn, position);
        game.move(position, Direction::BACKWARD);
        Position expected {2,4};
        Position result = game.getPawns()[2][4]->getPosition();
        REQUIRE(expected == result);
    }

    SECTION("move_LEFT")
    {
        Game game {};
        Position position {1,4};
        Pawn pawn {Role::COMMANDER, Color::RED, position, true};
        game.addPawn(pawn, position);
        game.move(position, Direction::LEFT);
        Position expected {1,3};
        Position result = game.getPawns()[1][3]->getPosition();
        REQUIRE(expected == result);
    }

    SECTION("move_RIGHT")
    {
        Game game {};
        Position position {1,4};
        Pawn pawn {Role::COMMANDER, Color::RED, position, true};
        game.addPawn(pawn, position);
        game.move(position, Direction::RIGHT);
        Position expected {1,5};
        Position result = game.getPawns()[1][5]->getPosition();
        REQUIRE(expected == result);
    }

    SECTION("battle_BothSameRole")
    {
        Game game {};
        Position pawn_position {3,3};
        Position pawn_enemy {2,3};
        Pawn pawn {Role::COMMANDER, Color::RED, pawn_position, true};
        Pawn enemy {Role::COMMANDER, Color::BLUE, pawn_enemy, true};
        game.addPawn(pawn, pawn_position);
        game.addPawn(enemy, pawn_enemy);
        game.battle(pawn_position, Direction::FORWARD);
        REQUIRE(game.getPawns()[3][3]->isValide() == false);
    }

    SECTION("battle_isHigher")
    {
        Game game {};
        Position pawn_position {3,3};
        Position pawn_enemy {2,3};
        Pawn pawn {Role::MARSHAL, Color::RED, pawn_position, true};
        Pawn enemy {Role::GENERAL, Color::BLUE, pawn_enemy, true};
        game.addPawn(pawn, pawn_position);
        game.addPawn(enemy, pawn_enemy);
        game.battle(pawn_position, Direction::FORWARD);
        REQUIRE(game.getPawns()[2][3]->isValide() == true);
    }

    SECTION("battle_isLower")
    {
        Game game {};
        Position pawn_position {3,3};
        Position pawn_enemy {2,3};
        Pawn pawn {Role::COMMANDER, Color::RED, pawn_position, true};
        Pawn enemy {Role::MARSHAL, Color::BLUE, pawn_enemy, true};
        game.addPawn(pawn, pawn_position);
        game.addPawn(enemy, pawn_enemy);
        game.battle(pawn_position, Direction::FORWARD);
        REQUIRE(game.getPawns()[3][3]->isValide() == false);
    }

    SECTION("nextPlayer_Blue")
    {
        Game game {};
        game.setCurrentPlayer(Color::BLUE);
        game.nextPlayer();
        Color expected = Color::RED;
        Color result = game.getCurrentPlayer();
        REQUIRE(expected == result);
    }

    SECTION("nextPlayer_Red")
    {
        Game game {};
        game.setCurrentPlayer(Color::RED);
        game.nextPlayer();
        Color expected = Color::BLUE;
        Color result = game.getCurrentPlayer();
        REQUIRE(expected == result);
    }

    SECTION("isPawnSameColor_true")
    {
        Game game {};
        game.setCurrentPlayer(Color::RED);
        Position pawn_position {3,3};
        Pawn pawn {Role::COMMANDER, Color::RED, pawn_position, true};
        game.addPawn(pawn, pawn_position);
        bool expected = true;
        bool result = game.isPawnSameColor(pawn_position);
        REQUIRE(expected == result);
    }

    SECTION("isPawnSameColor_false")
    {
        Game game {};
        game.setCurrentPlayer(Color::BLUE);
        Position pawn_position {3,3};
        Position pawn_enemy {2,3};
        Pawn pawn {Role::COMMANDER, Color::RED, pawn_position, true};
        game.addPawn(pawn, pawn_position);
        bool expected = false;
        bool result = game.isPawnSameColor(pawn_position);
        REQUIRE(expected == result);
    }
}
