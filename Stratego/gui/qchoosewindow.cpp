#include <QVBoxLayout>
#include <QHBoxLayout>

#include "qchoosewindow.h"

using namespace stratego;

QChooseWindow::QChooseWindow(QWidget * parent) : QWidget {parent} {
    QVBoxLayout * menu = new QVBoxLayout();
    QWidget * containerChooseMenu = new QWidget();
    QHBoxLayout * chooseMenu = new QHBoxLayout();
    title_ = new QLabel("Initialize your board");
    title_->setAlignment(Qt::AlignCenter);
    menu->addWidget(title_);
    choose_ = new QLabel("Choose : ");
    chooseMenu->addWidget(choose_);
    box_ = new QComboBox();
    box_->addItem("From file");
    box_->addItem("Manual");
    chooseMenu->addWidget(box_);
    containerChooseMenu->setLayout(chooseMenu);
    menu->addWidget(containerChooseMenu);
    submit_ = new QPushButton("Submit");
    menu->addWidget(submit_);
    setLayout(menu);
    adjustSize();
    parent->setWindowTitle("Choose initialize option");
    connect(submit_, SIGNAL(clicked()), this, SLOT(retrieveChosen()));
}

void QChooseWindow::retrieveChosen() {
    emit chosen(box_->currentText());
}
