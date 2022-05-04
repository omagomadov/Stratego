#ifndef QSTARTWINDOW_H
#define QSTARTWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

namespace stratego {
/**
 * @brief The QStartWindow class represents the class QStartWindow.
 */
class QStartWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QStartWindow constructor of QStartWindow.
     * @param parent
     */
    explicit QStartWindow(QWidget * parent = nullptr);
    /**
     * @brief getLevel getter of the level.
     * @return the level of the game
     */
    QString getLevel();
    ~QStartWindow() = default;

signals:
    /**
     * @brief started gives the level chosen by the player.
     * @param value the level
     */
    void started(QString value);

private slots:
    /**
     * @brief retrieveLevel slots when clicked on the button.
     */
    void retrieveLevel();

private:
    /**
     * @brief logo_ the logo.
     */
    QLabel * logo_;
    /**
     * @brief level_ the level.
     */
    QComboBox * level_;
    /**
     * @brief start_ the button.
     */
    QPushButton * start_;
};
}

#endif // QSTARTWINDOW_H
