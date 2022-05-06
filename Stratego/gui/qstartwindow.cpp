#include <QVBoxLayout>
#include <QFontDatabase>

#include "qstartwindow.h"
#include "gui.h"

using namespace stratego;

QStartWindow::QStartWindow(QWidget * parent) : QWidget {parent} {
    QVBoxLayout * menu = new QVBoxLayout();
    logo_ = new QLabel("Stratego");
    QFontDatabase::addApplicationFont(("://resource/fonts/Quisand.otf"));
    QFont font ("Quicksand", 50, QFont::Bold);
    logo_->setFont(font);
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
    static_cast<QView *>(parent)->addBackgroundColor();
    connect(start_, SIGNAL(clicked()), this, SLOT(retrieveLevel()));
}

void QStartWindow::retrieveLevel() {
    emit started(level_->currentText());
}
