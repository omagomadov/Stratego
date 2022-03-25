#include <Catch.h>
#include <Board.h>
#include <Game.h>
#include <iostream>

TEST_CASE("test_battle")
{
    SECTION("test_battle_BothSameRole")
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

    SECTION("test_battle_isHigher")
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

    SECTION("test_battle_isLower")
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

    SECTION("test_spy_win_against_marshal")
    {
        Game game {};
        Position pos_spy {2,2};
        Position pos_marshal {1,2};
        Pawn spy {Role::SPY, Color::BLUE, pos_spy, true};
        Pawn marshal {Role::MARSHAL, Color::RED, pos_marshal, true};
        game.addPawn(spy, pos_spy);
        game.addPawn(marshal, pos_marshal);
        game.battle(pos_spy, Direction::FORWARD);
        Role expected = Role::SPY;
        Role result = game.getRole(pos_marshal);
        REQUIRE(expected == result);
    }

    SECTION("test_minesweeper_win_against_bomb")
    {
        Game game {};
        Position pos_minesweeper {2,2};
        Position pos_bomb {1,2};
        Pawn minesweeper {Role::MINESWEEPER, Color::BLUE, pos_minesweeper, true};
        Pawn bomb {Role::BOMB, Color::RED, pos_bomb, false};
        game.addPawn(minesweeper, pos_minesweeper);
        game.addPawn(bomb, pos_bomb);
        game.battle(pos_minesweeper, Direction::FORWARD);
        Role expected = Role::MINESWEEPER;
        Role result = game.getRole(pos_bomb);
        REQUIRE(expected == result);
    }
}

TEST_CASE("test_isInside")
{
    SECTION("test_isInside_true")
    {
        Board board {};
        Position position {0,0};
        REQUIRE(board.isInside(position) == true);
    }

    SECTION("test_isInside_false_row")
    {
        Board board {};
        Position position {-9,10};
        REQUIRE(board.isInside(position) == false);
    }

    SECTION("test_isInside_false_column")
    {
        Board board {};
        Position position {9,-10};
        REQUIRE(board.isInside(position) == false);
    }
}

TEST_CASE("test_isEmpty")
{
    SECTION("test_isEmpty_true_BACKWARD")
    {
        Board board {};
        Position position {0,0};
        Direction direction {Direction::BACKWARD};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("test_isEmpty_true_FORWARD")
    {
        Board board {};
        Position position {1,0};
        Direction direction {Direction::FORWARD};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("test_isEmpty_true_LEFT")
    {
        Board board {};
        Position position {1,1};
        Direction direction {Direction::LEFT};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("test_isEmpty_true_RIGHT")
    {
        Board board {};
        Position position {1,1};
        Direction direction {Direction::RIGHT};
        REQUIRE(board.isEmpty(position, direction) == true);
    }

    SECTION("test_isEmpty_false_BACKWARD")
    {
        Board board {};
        Position position {0,0};
        Direction direction {Direction::BACKWARD};
        Pawn pawn {Role::COLONEL, Color::RED, Position{1,0}, true};
        board.addPawn(pawn, Position{1,0});
        REQUIRE(board.isEmpty(position, direction) == false);
    }

    SECTION("test_isEmpty_false_FORWARD")
    {
        Board board {};
        Position position {1,0};
        Direction direction {Direction::FORWARD};
        Pawn pawn {Role::COLONEL, Color::RED, Position{0,0}, true};
        board.addPawn(pawn, Position{0,0});
        REQUIRE(board.isEmpty(position, direction) == false);
    }

    SECTION("test_isEmpty_false_LEFT")
    {
        Board board {};
        Position position {1,1};
        Direction direction {Direction::LEFT};
        Pawn pawn {Role::COLONEL, Color::RED, Position{1,0}, true};
        board.addPawn(pawn, Position{1,0});
        REQUIRE(board.isEmpty(position, direction) == false);
    }

    SECTION("test_isEmpty_false_RIGHT")
    {
        Board board {};
        Position position {1,0};
        Direction direction {Direction::RIGHT};
        Pawn pawn {Role::COLONEL, Color::RED, Position{1,1}, true};
        board.addPawn(pawn, Position{1,1});
        REQUIRE(board.isEmpty(position, direction) == false);
    }
}

TEST_CASE("test_isWater")
{
    SECTION("test_isWater_01_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,2) == true);
    }

    SECTION("test_isWater_02_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,2) == true);
    }

    SECTION("test_isWater_03_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,3) == true);
    }

    SECTION("test_isWater_04_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,3) == true);
    }

    SECTION("test_isWater_05_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,6) == true);
    }

    SECTION("test_isWater_06_true")
    {
        Board board {};
        REQUIRE(board.isWater(4,7) == true);
    }

    SECTION("test_isWater_07_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,6) == true);
    }

    SECTION("test_isWater_08_true")
    {
        Board board {};
        REQUIRE(board.isWater(5,7) == true);
    }

    SECTION("test_isWater_can_not_move_1")
    {
        Board board {};
        REQUIRE(board.isWater(5,7) == true);
    }
}

TEST_CASE("test_isAlone")
{
    SECTION("test_isAlone_1_corner_false")
    {
        Board board {};
        Position test {0,0};
        // init position
        Position first_pawn {0,1};
        Position second_pawn {1,0};
        Position third_pawn {1,1};
        // init pawn
        Pawn pawn {Role::GENERAL, Color::BLUE, test, true};
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn, test);
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("test_isAlone_2_corner_false")
    {
        Board board {};
        Position test {9,0};
        // init position
        Position first_pawn {8,0};
        Position second_pawn {8,1};
        Position third_pawn {9,1};
        // init pawn
        Pawn pawn {Role::LIEUTENANT, Color::BLUE, test, true};
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn, test);
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("test_isAlone_3_corner_false")
    {
        Board board {};
        Position test {0,9};
        // init position
        Position first_pawn {0,8};
        Position second_pawn {1,8};
        Position third_pawn {1,9};
        // init pawn
        Pawn pawn {Role::LIEUTENANT, Color::BLUE, test, true};
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn, test);
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("test_isAlone_4_corner_false")
    {
        Board board {};
        Position test {9,9};
        // init position
        Position first_pawn {9,8};
        Position second_pawn {8,8};
        Position third_pawn {8,9};
        // init pawn
        Pawn pawn {Role::LIEUTENANT, Color::BLUE, test, true};
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn, test);
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == false);
    }

    SECTION("test_isAlone_5_true")
    {
        Board board {};
        Position test {3,4};
        // init position
        Position first_pawn {2,3};
        Position second_pawn {2,4};
        Position third_pawn {2,5};
        // init pawn
        Pawn pawn {Role::MAJOR, Color::BLUE, test, true};
        Pawn pawn_1 {Role::COLONEL, Color::BLUE, first_pawn, true};
        Pawn pawn_2 {Role::COMMANDER, Color::BLUE, second_pawn, true};
        Pawn pawn_3 {Role::GENERAL, Color::BLUE, third_pawn, true};
        // add pawns
        board.addPawn(pawn, test);
        board.addPawn(pawn_1, first_pawn);
        board.addPawn(pawn_2, second_pawn);
        board.addPawn(pawn_3, third_pawn);
        REQUIRE(board.isAlone(test) == true);
    }
}

TEST_CASE("test_isValide")
{
    SECTION("test_addPawn_isValide_1")
    {
        Board board {};
        Position position {0,0};
        Pawn pawn {Role::MAJOR, Color::BLUE, position, true};
        board.addPawn(pawn, position);
        REQUIRE(board.getPawns()[0][0]->isValide() == true);
    }

    SECTION("test_isValide_1")
    {
        Board board {};
        Position position {0,0};
        REQUIRE(board.getPawns()[0][0]->isValide() == false);
    }
}

TEST_CASE("test_isEnemy")
{
    SECTION("test_isEnemy_true_FORWARD")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {0,4};
        Pawn enemy {Role::COMMANDER, Color::BLUE, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::FORWARD, myColor) == true);
    }

    SECTION("test_isEnemy_true_BACKWARD")
    {
        Game game {};
        Color myColor = Color::BLUE;
        Position myPosition {1,4};
        Position enemyPosition {2,4};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::BACKWARD, myColor) == true);
    }

    SECTION("test_isEnemy_true_LEFT")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {1,3};
        Pawn enemy {Role::COMMANDER, Color::BLUE, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::LEFT, myColor) == true);
    }

    SECTION("test_isEnemy_true_RIGHT")
    {
        Game game {};
        Color myColor = Color::BLUE;
        Position myPosition {1,4};
        Position enemyPosition {1,5};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::RIGHT, myColor) == true);
    }

    SECTION("test_isEnemy_false_FORWARD")
    {
        Game game {};
        Color myColor = Color::BLUE;
        Position myPosition {1,4};
        Position enemyPosition {0,4};
        Pawn enemy {Role::COMMANDER, Color::BLUE, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::FORWARD, myColor) == false);
    }

    SECTION("test_isEnemy_false_BACKWARD")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {2,4};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::BACKWARD, myColor) == false);
    }

    SECTION("test_isEnemy_false_LEFT")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {1,3};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::LEFT, myColor) == false);
    }

    SECTION("test_isEnemy_true_RIGHT")
    {
        Game game {};
        Color myColor = Color::RED;
        Position myPosition {1,4};
        Position enemyPosition {1,5};
        Pawn enemy {Role::COMMANDER, Color::RED, enemyPosition, true};
        game.addPawn(enemy, enemyPosition);
        REQUIRE(game.isEnemy(myPosition, Direction::RIGHT, myColor) == false);
    }
}

TEST_CASE("test_move")
{
    SECTION("test_move_FORWARD")
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

    SECTION("test_move_BACKWARD")
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

    SECTION("test_move_LEFT")
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

    SECTION("test_move_RIGHT")
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

    SECTION("test_cant_move_BOMB")
    {
        Game game {};
        Position bomb_pos {1,2};
        Pawn bomb {Role::BOMB, Color::RED, bomb_pos, true};
        game.addPawn(bomb, bomb_pos);
        REQUIRE_THROWS(game.move(bomb_pos, Direction::FORWARD));
    }

    SECTION("test_cant_move_FLAG")
    {
        Game game {};
        Position flag_pos {1,2};
        Pawn bomb {Role::BOMB, Color::RED, flag_pos, true};
        game.addPawn(bomb, flag_pos);
        REQUIRE_THROWS(game.move(flag_pos, Direction::FORWARD));
    }
}

TEST_CASE("test_nextPlayer")
{
    SECTION("test_nextPlayer_Blue")
    {
        Game game {};
        game.setCurrentPlayer(Color::BLUE);
        game.nextPlayer();
        Color expected = Color::RED;
        Color result = game.getCurrentPlayer();
        REQUIRE(expected == result);
    }

    SECTION("test_nextPlayer_Red")
    {
        Game game {};
        game.setCurrentPlayer(Color::RED);
        game.nextPlayer();
        Color expected = Color::BLUE;
        Color result = game.getCurrentPlayer();
        REQUIRE(expected == result);
    }
}

TEST_CASE("test_isPawnSameColor")
{
    SECTION("test_isPawnSameColor_true")
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

    SECTION("test_isPawnSameColor_false")
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
