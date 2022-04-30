#ifndef QSTARTWINDOW_H
#define QSTARTWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

namespace stratego {
/**
 * @brief The QStartWindow class todo
 */
class QStartWindow : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief QStartWindow todo
     * @param parent
     */
    explicit QStartWindow(QWidget * parent = nullptr);
    /**
     * @brief  todo
     * @return
     */
    QString getLevel();
    ~QStartWindow() = default;

signals:
    /**
     * @brief started todo
     * @param value
     */
    void started(QString value);

private slots:
    /**
     * @brief retrieveLevel todo
     */
    void retrieveLevel();

private:
    /**
     * @brief logo_ todo
     */
    QLabel * logo_;
    /**
     * @brief level_ todo
     */
    QComboBox * level_;
    /**
     * @brief start_ todo
     */
    QPushButton * start_;
};
}

#endif // QSTARTWINDOW_H
