#include <QMouseEvent>

#include "qsquare.h"

using namespace stratego;

QSquare::QSquare(const QString &type, Position position, QWidget * parent)
    : QLabel {parent}, type_ {type}, position_ {position} {
    QString url = "://resource/texture/";
    if(type_ == "grass") {
        url += "grass.png";
        setPixmap(QPixmap(url));
    } else {
        url += "water.png";
        setPixmap(QPixmap(url));
    }
    setScaledContents(true);
    setFixedSize(50,50);
}

void QSquare::mousePressEvent(QMouseEvent * event) {
    event->accept();
    emit clicked(position_);
}
