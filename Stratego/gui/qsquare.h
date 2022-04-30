#ifndef QSQUARE_H
#define QSQUARE_H

#include <QLabel>
#include <QString>

#include "Position.h"

namespace stratego {
/**
 * @brief The QSquare class
 */
class QSquare : public QLabel {
    Q_OBJECT
public:
    /**
     * @brief QSquare
     * @param type
     * @param position
     * @param parent
     */
    explicit QSquare(QString type, Position position, QWidget * parent = nullptr);
    ~QSquare() = default;

protected:
    /**
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent * event);

signals:
    /**
     * @brief clicked
     * @param position
     */
    void clicked(stratego::Position position);

private:
    /**
     * @brief type_
     */
    QString type_;
    /**
     * @brief position_
     */
    Position position_;
};
}

#endif // QSQUARE_H
