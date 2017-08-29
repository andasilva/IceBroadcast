#include "dashboardwindow.h"
#include <QtWidgets>

DashboardWindow::DashboardWindow(QWidget *parent) : QWidget(parent)
{
    new QLabel("DashBoard Window", this);
}
