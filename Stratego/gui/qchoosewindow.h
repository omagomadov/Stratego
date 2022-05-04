#ifndef QCHOOSEWINDOW_H
#define QCHOOSEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

namespace stratego {
/**
 * @brief The QChooseWindow class represents the class QChooseWindow.
 */
class QChooseWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QChooseWindow the constructor of QChooseWindow.
     * @param parent
     */
    explicit QChooseWindow(QWidget * parent = nullptr);
    ~QChooseWindow() = default;

signals:
    /**
     * @brief chosen gives the value chosen by the player.
     * @param value the value chosen by the player.
     */
    void chosen(QString value);

private slots:
    /**
     * @brief retrieveChoose slots when clicked on the button.
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
     * @brief box_ the different option.
     */
    QComboBox * box_;
    /**
     * @brief submit_ the button.
     */
    QPushButton * submit_;
};
}

#endif // QCHOOSEWINDOW_H
