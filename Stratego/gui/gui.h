#ifndef GUI_H
#define GUI_H

#include <QWidget>

namespace stratego {
class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

signals:

};
}

#endif // GUI_H
