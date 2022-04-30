#include <QMouseEvent>

#include "qpawn.h"

using namespace stratego;

QPawn::QPawn(Color color, Role role, Position position, bool hide, QWidget * parent)
    : QLabel {parent}, color_ {color}, role_ {role}, position_ {position}, hide_ {hide} {
    QString player = (color == BLUE) ? "blue" : "red";
    selectable_ = true;
    if(color == BLUE) {
        if(hide) {
            dressHidden(player);
        } else {
            dressPawn(player, role);
        }
    } else {
        if(hide) {
            dressHidden(player);
        } else {
            dressPawn(player, role);
        }
    }
    if(!hide) {
        setToolTip(to_string(static_cast<Role>(role)).c_str());
    }
    setFixedSize(50,50);
}

void QPawn::dressPawn(const QString &color, Role role) {
    QString url = "://resource/";
    url += color;
    switch(role) {
    case SPY :
        url += "/spy.png";
        setPixmap(QPixmap(url));
        break;
    case GENERAL :
        url += "/general.png";
        setPixmap(QPixmap(url));
        break;
    case MARSHAL :
        url += "/marshal.png";
        setPixmap(QPixmap(url));
        break;
    case MAJOR :
        url += "/major.png";
        setPixmap(QPixmap(url));
        break;
    case COLONEL :
        url += "/colonel.png";
        setPixmap(QPixmap(url));
        break;
    case LIEUTENANT :
        url += "/lieutenant.png";
        setPixmap(QPixmap(url));
        break;
    case COMMANDER :
        url += "/captain.png";
        setPixmap(QPixmap(url));
        break;
    case SERGEANT :
        url += "/sergeant.png";
        setPixmap(QPixmap(url));
        break;
    case MINESWEEPER :
        url += "/miner.png";
        setPixmap(QPixmap(url));
        break;
    case SCOUT :
        url += "/scout.png";
        setPixmap(QPixmap(url));
        break;
    case FLAG :
        url += "/flag.png";
        setPixmap(QPixmap(url));
        break;
    case BOMB :
        url += "/bomb.png";
        setPixmap(QPixmap(url));
        break;
    }
    setScaledContents(true);
}

void QPawn::dressHidden(const QString &color) {
    QString url = "://resource/";
    url += color;
    url += "/hide.png";
    setPixmap(QPixmap(url));
    setScaledContents(true);
}

void QPawn::mousePressEvent(QMouseEvent * event) {
    if(selectable_) {
        event->accept();
        emit clicked(this);
    } else {
        event->ignore();
    }
}

Color QPawn::getColor() {
    return color_;
}

Role QPawn::getRole() {
    return role_;
}

Position QPawn::getPosition() {
    return position_;
}

bool QPawn::isSelectable() {
    return selectable_;
}

void QPawn::setSelectable(bool selectable) {
    selectable_ = selectable;
}
