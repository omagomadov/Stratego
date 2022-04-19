#ifndef GUI_H
#define GUI_H

#include <QWidget>

#include "observer.h"
#include "Game.h"

namespace stratego {
/**
 * @brief The View class todo
 */
class View : public QWidget, public Observer {
    Q_OBJECT
public:
    /**
     * @brief View todo
     * @param parent
     */
    explicit View(QWidget *parent = nullptr);
    /**
     * @brief update todo
     */
    void update() override;

private:
    /**
     * @brief game_ todo
     */
    Game game_;
    /**
     * @brief controller_ todo
     */
    Controller controller_;
};
}

#endif // GUI_H
