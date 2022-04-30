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
    Game &game_;
    /**
     * @brief selectedPawn_
     */
    QPawn * selectedPawn_;
    /**
     * @brief placedPawns
     */
    int placedPawns_;
};
}

#endif // QMANUALWINDOW_H
