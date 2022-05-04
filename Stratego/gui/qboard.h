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
 * @brief The QBoard class represents the class Board.
 */
class QBoard : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QBoard constructor of QBoard.
     * @param game the game
     * @param parent
     */
    explicit QBoard(QController &controller, Game &game, QWidget * parent = nullptr);
    /**
     * @brief updateBoard updates the board.
     */
    void updateBoard();
    /**
     * @brief initialize initializes the board. Adds grass & water.
     */
    void initialize();
    /**
     * @brief containsWater checks if at the row and column there is a square water.
     * @param row the row
     * @param column the column
     * @return true if there is a square water
     */
    bool containsWater(unsigned row, unsigned column);
    /**
     * @brief isNeighbor checks if the position first and second are 'neighbor'.
     * @param first the position
     * @param second the position
     * @return true if the position first is neighbor with the position second
     */
    bool isNeighbor(Position first, Position second);
    /**
     * @brief deduceDirection deduces the direction with the given position 'initial' and 'next'.
     * @param first the position
     * @param second the position
     * @return the direction
     */
    Direction deduceDirection(Position initial, Position next);
    /**
     * @brief moveScout moves the scout.
     * @param position the position
     */
    void moveScout(Position position);
    /**
     * @brief clearBoard clears the board.
     */
    void clearBoard();
    /**
     * @brief displayError displays a 'error' message
     * @param message the message
     */
    void displayMessage(QString message);
    ~QBoard() = default;

private slots:
    /**
     * @brief clicked_on_pawn slots when clicked on a pawn.
     */
    void clicked_on_pawn(stratego::QPawn *);
    /**
     * @brief clicked_on_square slots when clicked on a square.
     */
    void clicked_on_square(stratego::Position);

private:
    /**
     * @brief game_ the game.
     */
    Game &game_;
    /**
     * @brief controller_ the controller.
     */
    QController &controller_;
    /**
     * @brief board_ the board.
     */
    QGridLayout * board_;
    /**
     * @brief selectedPawn_ the selected pawn.
     */
    QPawn * selectedPawn_;
    /**
     * @brief message_ the message.
     */
    QLabel * message_;
};
}

#endif // QBOARD_H
