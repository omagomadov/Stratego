#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>

#include "observer.h"
#include "Game.h"

namespace stratego {
class QSquare : public QLabel {
    Q_OBJECT
public:
    explicit QSquare(QString type, Position position, QWidget * parent = nullptr);
    ~QSquare() = default;

protected:
    void mousePressEvent(QMouseEvent * event);

signals:
    void clicked(stratego::Position position);

private:
    QString type_;
    Position position_;
};

/**
 * @brief The QPawn class todo
 */
class QPawn : public QLabel {
    Q_OBJECT
public:
    /**
     * @brief QPawn todo
     * @param color
     * @param role
     * @param parent
     */
    explicit QPawn(Color color, Role role, Position position, QWidget * parent = nullptr);
    /**
     * @brief dressPawn todo
     * @param color
     * @param role
     */
    void dressPawn(QString color, Role role);
    /**
     * @brief getColor
     * @return
     */
    Color getColor();
    /**
     * @brief getRole todo
     * @return
     */
    Role getRole();
    /**
     * @brief getPosition
     * @return
     */
    Position getPosition();
    /**
     * @brief setSelectable
     * @param selectable
     */
    void setSelectable(bool selectable);
    /**
     * @brief isSelectable
     * @return
     */
    bool isSelectable();
    ~QPawn() = default;

protected:
    /**
     * @brief mousePressEvent todo
     * @param event
     */
    void mousePressEvent(QMouseEvent * event);

signals:
    /**
     * @brief clicked todo
     * @param pawn
     */
    void clicked(stratego::QPawn * pawn);

private:
    /**
     * @brief color todo
     */
    Color color_;
    /**
     * @brief role_ todo
     */
    Role role_;
    /**
     * @brief position_ todo
     */
    Position position_;
    /**
     * @brief selectable_
     */
    bool selectable_;
};

/**
 * @brief The QManualWindow class todo
 */
class QManualWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QManualWindow todo
     * @param parent
     */
    explicit QManualWindow(Game &game, Color player, QWidget * parent = nullptr);
    /**
     * @brief populatePawns
     */
    void populatePawns(QGridLayout * pawns);
    /**
     * @brief populateSquare
     * @param squares
     */
    void populateSquare(QGridLayout * squares);
    ~QManualWindow() = default;

signals:
    void submit();

private slots:
    /**
     * @brief on_pawns
     * @param pawn
     */
    void on_pawns(stratego::QPawn * pawn);
    /**
     * @brief on_squares
     * @param position
     */
    void on_squares(stratego::Position position);
    /**
     * @brief addManualBoard
     */
    void addManualBoard();

private:
    /**
     * @brief title_ todo
     */
    QLabel * title_;
    /**
     * @brief board_ todo
     */
    QGridLayout * squares_;
    /**
     * @brief pawns_ todo
     */
    QGridLayout * pawns_;
    /**
     * @brief button_ todo
     */
    QPushButton * submit_;
    /**
     * @brief player_ todo
     */
    Color player_;
    /**
     * @brief game_
     */
    Game game_;
    /**
     * @brief selectedPawn_
     */
    QPawn * selectedPawn_;
    /**
     * @brief placedPawns
     */
    int placedPawns_;
};

/**
 * @brief The QFileWindow class todo
 */
class QFileWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QFileWindow todo
     * @param parent
     */
    explicit QFileWindow(QWidget * parent = nullptr);
    ~QFileWindow() = default;

signals:
    void chosen(QString value);

private slots:
    void retrieveChosen();

private:
    /**
     * @brief title_ todo
     */
    QLabel * title_;
    /**
     * @brief choose_ todo
     */
    QLabel * choose_;
    /**
     * @brief file_ todo
     */
    QLineEdit * file_;
    /**
     * @brief submit_ todo
     */
    QPushButton * submit_;
};

class QChooseWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QChooseWindow todo
     * @param parent
     */
    explicit QChooseWindow(QWidget * parent = nullptr);
    ~QChooseWindow() = default;

signals:
    /**
     * @brief chosen
     * @param value
     */
    void chosen(QString value);

private slots:
    /**
     * @brief retrieveChoose
     */
    void retrieveChosen();

private:
    /**
     * @brief title_ todo
     */
    QLabel * title_;
    /**
     * @brief choose_ todo
     */
    QLabel * choose_;
    /**
     * @brief box_ todo
     */
    QComboBox * box_;
    /**
     * @brief submit_ todo
     */
    QPushButton * submit_;
};

/**
 * @brief The QStartWindow class todo
 */
class QStartWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QStartWindow todo
     * @param parent
     */
    explicit QStartWindow(QWidget * parent = nullptr);
    /**
     * @brief  todo
     * @return
     */
    QString getLevel();
    ~QStartWindow() = default;

signals:
    /**
     * @brief started todo
     * @param value
     */
    void started(QString value);

private slots:
    /**
     * @brief retrieveLevel todo
     */
    void retrieveLevel();

private:
    /**
     * @brief logo_ todo
     */
    QLabel * logo_;
    /**
     * @brief level_ todo
     */
    QComboBox * level_;
    /**
     * @brief start_ todo
     */
    QPushButton * start_;
};

/**
 * @brief The Controller class todo
 */
class Controller {
    /**
     * @brief game_ todo
     */
    Game &game_;
public:
    /**
     * @brief Controller todo
     * @param game_
     */
    Controller(Game &game_);
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
    ~Controller() = default;
};

/**
 * @brief The View class todo
 */
class View : public QWidget, public Observer {
    Q_OBJECT
public:
    /**
     * @brief View todo
     * @param parent
     */
    explicit View(Game &game, Controller &controller, QWidget *parent = nullptr);
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
    Game &game_;
    /**
     * @brief controller_ todo
     */
    Controller &controller_;
    /**
     * @brief startWindow_ todo
     */
    QStartWindow * startWindow_;
    /**
     * @brief window_ todo
     */
    QHBoxLayout * window_;
    /**
     * @brief initWindow_ todo
     */
    QChooseWindow * chooseWindow_;
    /**
     * @brief fileWindow_ todo
     */
    QFileWindow * fileWindow_;
    /**
     * @brief manualWindow_ todo
     */
    QManualWindow * manualWindow_;
};
}

#endif // GUI_H
