#include <QVBoxLayout>

#include "qstartwindow.h"

using namespace stratego;

QStartWindow::QStartWindow(QWidget * parent) : QWidget {parent} {
    QVBoxLayout * menu = new QVBoxLayout();
    logo_ = new QLabel("Stratego");
    logo_->setStyleSheet("font-size: 25px");
    logo_->setAlignment(Qt::AlignCenter);
    menu->addWidget(logo_);
    level_ = new QComboBox();
    level_->addItem("Easy");
    level_->addItem("Normal");
    menu->addWidget(level_);
    start_ = new QPushButton("Launch");
    menu->addWidget(start_);
    setLayout(menu);
    adjustSize();
    connect(start_, SIGNAL(clicked()), this, SLOT(retrieveLevel()));
}

void QStartWindow::retrieveLevel() {
    emit started(level_->currentText());
}
