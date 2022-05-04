#ifndef QSQUARE_H
#define QSQUARE_H

#include <QLabel>
#include <QString>

#include "Position.h"

namespace stratego {
/**
 * @brief The QSquare class represents the class QSquare.
 */
class QSquare : public QLabel {
    Q_OBJECT
public:
    /**
     * @brief QSquare constructor of QSquare.
     * @param type the type
     * @param position the position
     * @param parent
     */
    explicit QSquare(const QString &, Position position, QWidget * parent = nullptr);
    ~QSquare() = default;

protected:
    /**
     * @brief mousePressEvent events when clicked on a square.
     * @param event the mouse event
     */
    void mousePressEvent(QMouseEvent * event);

signals:
    /**
     * @brief clicked emited when clicked on a square.
     * @param position the position
     */
    void clicked(stratego::Position position);

private:
    /**
     * @brief type_ the type of square.
     */
    QString type_;
    /**
     * @brief position_ the position
     */
    Position position_;
};
}

#endif // QSQUARE_H
