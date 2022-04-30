#ifndef QFILEWINDOW_H
#define QFILEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace stratego {
/**
 * @brief The QFileWindow class todo
 */
class QFileWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QFileWindow todo
     * @param parent
     */
    explicit QFileWindow(QWidget * parent = nullptr);
    ~QFileWindow() = default;

signals:
    void chosen(QString value);

private slots:
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
     * @brief file_ todo
     */
    QLineEdit * file_;
    /**
     * @brief submit_ todo
     */
    QPushButton * submit_;
};
}

#endif // QFILEWINDOW_H
