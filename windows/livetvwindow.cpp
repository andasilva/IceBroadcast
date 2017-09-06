#include "livetvwindow.h"
#include <QtWidgets>

LiveTvWindow::LiveTvWindow(QWidget *parent) : QWidget(parent)
{
    new QLabel("test",this);
/*    QVBoxLayout* mainLayout = new QVBoxLayout();

    mainLayout->addWidget(new QLabel("test"));

    setLayout(mainLayout);
    */
}
