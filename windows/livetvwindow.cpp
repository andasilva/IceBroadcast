#include "livetvwindow.h"
#include <QtWidgets>

LiveTvWindow::LiveTvWindow(QWidget *parent) : QWidget(parent)
{
    new QLabel("Live TV", this);
}
