#ifndef QPAWN_H
#define QPAWN_H

#include <QLabel>

#include "Game.h"

namespace stratego {
/**
 * @brief The QPawn class represents the class QPawn.
 */
class QPawn : public QLabel {
    Q_OBJECT
public:
    /**
     * @brief QPawn constructor of QPawn.
     * @param color the color.
     * @param role the role.
     * @param position the position.
     * @param hide the hide option.
     * @param parent
     */
    explicit QPawn(Color color, Role role, Position position, bool hide, QWidget * parent = nullptr);
    /**
     * @brief dressPawn dresses the pawn corresponding the role and color.
     * @param color the color
     * @param role the role
     */
    void dressPawn(const QString &color, Role role);
    /**
     * @brief dressHidden dresses the pawn hidden corresponding the color.
     * @param color the color
     */
    void dressHidden(const QString &color);
    /**
     * @brief getColor getter of the color.
     * @return the color
     */
    Color getColor();
    /**
     * @brief getRole getter of the role.
     * @return the role
     */
    Role getRole();
    /**
     * @brief getPosition getter of the position
     * @return the position
     */
    Position getPosition();
    /**
     * @brief setSelectable sets the pawn selectable or not.
     * @param selectable true if selectable else false
     */
    void setSelectable(bool selectable);
    /**
     * @brief isSelectable getter of the selectable option.
     * @return true if the pawn is selectable else false
     */
    bool isSelectable();
    ~QPawn() = default;

protected:
    /**
     * @brief mousePressEvent events when clicked on a pawn.
     * @param event the mouse event
     */
    void mousePressEvent(QMouseEvent * event);

signals:
    /**
     * @brief clicked emited when clicked on a pawn.
     * @param pawn the pawn
     */
    void clicked(stratego::QPawn * pawn);

private:
    /**
     * @brief color the color
     */
    Color color_;
    /**
     * @brief role_ the role
     */
    Role role_;
    /**
     * @brief position_ the position
     */
    Position position_;
    /**
     * @brief selectable_ the selectable option.
     */
    bool selectable_;
    /**
     * @brief hide_ the hidden option.
     */
    bool hide_;
};
}

#endif // QPAWN_H
