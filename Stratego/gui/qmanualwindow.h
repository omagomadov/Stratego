#ifndef QMANUALWINDOW_H
#define QMANUALWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

#include "qpawn.h"
#include "Game.h"
#include "Color.h"

namespace stratego {
/**
 * @brief The QManualWindow class represents the class QManualWindow.
 */
class QManualWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QManualWindow constructor of QManualWindow.
     * @param parent
     */
    explicit QManualWindow(Game &game, Color player, QWidget * parent = nullptr);
    /**
     * @brief populatePawns adds pawns on the horizontale.
     */
    void populatePawns(QGridLayout * pawns);
    /**
     * @brief populateSquare adds grass squares on the board.
     * @param squares the board containing squares
     */
    void populateSquare(QGridLayout * squares);
    ~QManualWindow() = default;

signals:
    /**
     * @brief submit emited when clicked on the button.
     */
    void submit();

private slots:
    /**
     * @brief on_pawns slots when clicked on a pawn.
     * @param pawn the pawn
     */
    void on_pawns(stratego::QPawn * pawn);
    /**
     * @brief on_squares slots when clicked on a square.
     * @param position the position
     */
    void on_squares(stratego::Position position);
    /**
     * @brief addManualBoard adds the board.
     */
    void addManualBoard();

private:
    /**
     * @brief title_ the title.
     */
    QLabel * title_;
    /**
     * @brief squares_ the squares.
     */
    QGridLayout * squares_;
    /**
     * @brief pawns_ the pawns.
     */
    QGridLayout * pawns_;
    /**
     * @brief button_ the button.
     */
    QPushButton * submit_;
    /**
     * @brief player_ the current player color.
     */
    Color player_;
    /**
     * @brief game_ the game.
     */
    Game &game_;
    /**
     * @brief selectedPawn_ the selected pawn.
     */
    QPawn * selectedPawn_;
    /**
     * @brief placedPawns the number of placed pawns.
     */
    int placedPawns_;
};
}

#endif // QMANUALWINDOW_H
