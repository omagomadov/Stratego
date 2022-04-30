#ifndef QCHOOSEWINDOW_H
#define QCHOOSEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

namespace stratego {
class QChooseWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QChooseWindow todo
     * @param parent
     */
    explicit QChooseWindow(QWidget * parent = nullptr);
    ~QChooseWindow() = default;

signals:
    /**
     * @brief chosen
     * @param value
     */
    void chosen(QString value);

private slots:
    /**
     * @brief retrieveChoose
     */
    void retrieveChosen();

private:
    /**
     * @brief title_ todo
     */
    QLabel * title_;
    /**
     * @brief choose_ todo
     */
    QLabel * choose_;
    /**
     * @brief box_ todo
     */
    QComboBox * box_;
    /**
     * @brief submit_ todo
     */
    QPushButton * submit_;
};
}

#endif // QCHOOSEWINDOW_H
