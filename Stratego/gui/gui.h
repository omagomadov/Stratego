#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QHBoxLayout>

#include "observer.h"
#include "Game.h"

namespace stratego {

class QChooseWindow;
class QFileWindow;
class QManualWindow;
class QStartWindow;
class QBoard;

/**
 * @brief The Controller class represents the class Controller.
 */
class QController {
    /**
     * @brief game_ the game.
     */
    Game &game_;
public:
    /**
     * @brief Controller constructor of Controller.
     * @param game_
     */
    QController(Game &game_);
    /**
     * @brief addLevel adds the level for the game.
     * @param level the level
     */
    void addLevel(const QString &level);
    /**
     * @brief addFileBoard adds the path of the file for the game.
     * @param choose the path of the file
     */
    void addFileBoard(const QString &choose);
    /**
     * @brief nextState change the game state.
     */
    void nextState();
    /**
     * @brief move moves the pawn.
     * @param position the position of the pawn
     * @param direction the direction of the pawn
     * @param moves the number of moves
     */
    void move(Position& position, Direction& direction, int moves = 0);
    ~QController() = default;
};

}
/**
 * @brief The View class represents the class View.
 */
class QView : public QWidget, public stratego::Observer {
    Q_OBJECT
public:
    /**
     * @brief View constructor of View.
     * @param parent
     */
    explicit QView(stratego::Game &game, stratego::QController &controller, QWidget *parent = nullptr);
    /**
     * @brief displayStartWindow displays the start window.
     */
    void displayStartWindow();
    /**
     * @brief displayChooseWindow displays the choose window.
     */
    void displayChooseWindow();
    /**
     * @brief displayFileWindow displays the file window.
     */
    void displayFileWindow();
    /**
     * @brief displayManualWindow displays the manual window.
     */
    void displayManualWindow();
    /**
     * @brief displayWinner displays the winner.
     */
    void displayWinner();
    /**
     * @brief update updates the board.
     */
    void update() override;

private slots:
    /**
     * @brief setLevel slots when the player finished to set the level of the game.
     * @param level the level
     */
    void addLevel(const QString &level);
    /**
     * @brief addChosen slots when the player finished to set the type of initialization.
     * @param value the choose option
     */
    void addChosen(const QString &value);
    /**
     * @brief addManualBoard slots when the player finished to place pawns.
     */
    void addManualBoard();
    /**
     * @brief option slots when the player finished to set the path of the file.
     * @param file
     */
    void option(const QString &file);
    /**
     * @brief reset resets the game.
     */
    void reset();
    /**
     * @brief quit quits the game.
     */
    void quit();

private:
    /**
     * @brief game_ the game.
     */
    stratego::Game &game_;
    /**
     * @brief controller_ the controller.
     */
    stratego::QController &controller_;
    /**
     * @brief startWindow_ the start window.
     */
    stratego::QStartWindow * startWindow_;
    /**
     * @brief window_ the main window.
     */
    QHBoxLayout * window_;
    /**
     * @brief initWindow_ the choose window.
     */
    stratego::QChooseWindow * chooseWindow_;
    /**
     * @brief fileWindow_ the file window.
     */
    stratego::QFileWindow * fileWindow_;
    /**
     * @brief manualWindow_ the manual window.
     */
    stratego::QManualWindow * manualWindow_;
    /**
     * @brief board_ the board.
     */
    stratego::QBoard * board_;
    /**
     * @brief winnerWindow_ the winner window.
     */
    QVBoxLayout * winnerWindow_;
};

#endif // GUI_H
