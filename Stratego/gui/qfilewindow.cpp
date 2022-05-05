#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

#include "qfilewindow.h"

using namespace stratego;

QFileWindow::QFileWindow(QWidget * parent) : QWidget {parent} {
    QVBoxLayout * menu = new QVBoxLayout();
    QWidget * container = new QWidget();
    QHBoxLayout * middle = new QHBoxLayout();
    title_ = new QLabel("Initializiation from file");
    title_->setAlignment(Qt::AlignCenter);
    menu->addWidget(title_);
    choose_ = new QLabel("The name of the file : ");
    middle->addWidget(choose_);
    file_ = new QLineEdit("default.txt");
    file_->setMinimumSize(100,20);
    file_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    middle->addWidget(file_);
    container->setLayout(middle);
    menu->addWidget(container);
    submit_ = new QPushButton("Submit");
    menu->addWidget(submit_);
    setLayout(menu);
    adjustSize();
    parent->setWindowTitle("Initializing the game board with a file");
    connect(submit_, SIGNAL(clicked()), this, SLOT(retrieveChosen()));
}

void QFileWindow::retrieveChosen() {
    emit chosen(file_->text());
}
