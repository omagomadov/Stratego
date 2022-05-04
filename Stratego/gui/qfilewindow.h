#ifndef QFILEWINDOW_H
#define QFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace stratego {
/**
 * @brief The QFileWindow class represents the class QFileWindow.
 */
class QFileWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QFileWindow constructor of QFileWindow.
     * @param parent
     */
    explicit QFileWindow(QWidget * parent = nullptr);
    ~QFileWindow() = default;

signals:
    /**
     * @brief chosen gives the path given by the player.
     * @param value the path of the file
     */
    void chosen(QString value);

private slots:
    /**
     * @brief retrieveChosen slots when clicked on the button.
     */
    void retrieveChosen();

private:
    /**
     * @brief title_ the title.
     */
    QLabel * title_;
    /**
     * @brief choose_ the label.
     */
    QLabel * choose_;
    /**
     * @brief file_ the line edit.
     */
    QLineEdit * file_;
    /**
     * @brief submit_ the button.
     */
    QPushButton * submit_;
};
}

#endif // QFILEWINDOW_H
