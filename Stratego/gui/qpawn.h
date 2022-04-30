#ifndef QPAWN_H
#define QPAWN_H

#include <QLabel>

#include "Game.h"

namespace stratego {
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
    explicit QPawn(Color color, Role role, Position position, bool hide, QWidget * parent = nullptr);
    /**
     * @brief dressPawn todo
     * @param color
     * @param role
     */
    void dressPawn(QString color, Role role);
    /**
     * @brief dressHidden
     * @param color
     */
    void dressHidden(QString color);
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
    /**
     * @brief hide_
     */
    bool hide_;
};
}

#endif // QPAWN_H
