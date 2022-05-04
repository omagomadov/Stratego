#ifndef QBOARD_H
#define QBOARD_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include "Game.h"
#include "gui.h"
#include "qpawn.h"

namespace stratego {
/**
 * @brief The QBoard class
 */
class QBoard : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QBoard
     * @param game
     * @param parent
     */
    explicit QBoard(QController &controller, Game &game, QWidget * parent = nullptr);
    /**
     * @brief updateBoard
     */
    void updateBoard();
    /**
     * @brief initialize
     */
    void initialize();
    /**
     * @brief containsWater
     * @param row
     * @param column
     * @return
     */
    bool containsWater(unsigned row, unsigned column);
    /**
     * @brief isNeighbor
     * @param first
     * @param second
     * @return
     */
    bool isNeighbor(Position first, Position second);
    /**
     * @brief deduceDirection
     * @param first
     * @param second
     * @return
     */
    Direction deduceDirection(Position initial, Position next);
    /**
     * @brief moveScout
     * @param pawn
     * @param enemy
     */
    void moveScout(Position position);
    /**
     * @brief clearBoard
     */
    void clearBoard();
    /**
     * @brief displayError
     * @param message
     */
    void displayMessage(QString message);
    ~QBoard() = default;

private slots:
    /**
     * @brief clicked_on_pawn
     */
    void clicked_on_pawn(stratego::QPawn *);
    /**
     * @brief clicked_on_square
     */
    void clicked_on_square(stratego::Position);

private:
    /**
     * @brief game_
     */
    Game &game_;
    /**
     * @brief controller_
     */
    QController &controller_;
    /**
     * @brief board_
     */
    QGridLayout * board_;
    /**
     * @brief selectedPawn_
     */
    QPawn * selectedPawn_;
    /**
     * @brief message_
     */
    QLabel * message_;
};
}

#endif // QBOARD_H
