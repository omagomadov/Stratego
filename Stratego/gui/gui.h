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
 * @brief The Controller class todo
 */
class QController {
    /**
     * @brief game_ todo
     */
    Game &game_;
public:
    /**
     * @brief Controller todo
     * @param game_
     */
    QController(Game &game_);
    /**
     * @brief initLevel todo
     * @param level
     */
    void addLevel(QString level);
    /**
     * @brief addChoose todo
     * @param file
     */
    void addFileBoard(QString choose);
    /**
     * @brief nextState
     */
    void nextState();
    /**
     * @brief move
     * @param position
     * @param direction
     */
    void move(Position position, Direction direction);
    ~QController() = default;
};

}
/**
 * @brief The View class todo
 */
class QView : public QWidget, public stratego::Observer {
    Q_OBJECT
public:
    /**
     * @brief View todo
     * @param parent
     */
    explicit QView(stratego::Game &game, stratego::QController &controller, QWidget *parent = nullptr);
    /**
     * @brief displayStartWindow
     */
    void displayStartWindow();
    /**
     * @brief displayChooseWindow todo
     */
    void displayChooseWindow();
    /**
     * @brief displayFileWindow todo
     */
    void displayFileWindow();
    /**
     * @brief displayManualWindow todo
     */
    void displayManualWindow();
    /**
     * @brief update todo
     */
    void update() override;

private slots:
    /**
     * @brief setLevel todo
     * @param level
     */
    void addLevel(QString level);
    /**
     * @brief addChosen todo
     * @param value
     */
    void addChosen(QString value);
    /**
     * @brief addManualBoard
     */
    void addManualBoard();
    /**
     * @brief option todo
     * @param file
     */
    void option(QString file);

private:
    /**
     * @brief game_ todo
     */
    stratego::Game &game_;
    /**
     * @brief controller_ todo
     */
    stratego::QController &controller_;
    /**
     * @brief startWindow_ todo
     */
    stratego::QStartWindow * startWindow_;
    /**
     * @brief window_ todo
     */
    QHBoxLayout * window_;
    /**
     * @brief initWindow_ todo
     */
    stratego::QChooseWindow * chooseWindow_;
    /**
     * @brief fileWindow_ todo
     */
    stratego::QFileWindow * fileWindow_;
    /**
     * @brief manualWindow_ todo
     */
    stratego::QManualWindow * manualWindow_;
    /**
     * @brief board_
     */
    stratego::QBoard * board_;
};

#endif // GUI_H
