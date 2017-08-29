#include "dashboardwindow.h"
#include <QtWidgets>

DashboardWindow::DashboardWindow(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Logo Here"));
}
