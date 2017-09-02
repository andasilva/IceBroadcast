#include "dashboardwindow.h"
#include <QtWidgets>

DashboardWindow::DashboardWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *layoutLogo = new QHBoxLayout;

    //load Logo
    logo = new QLabel(this);
    logo->setAlignment(Qt::AlignCenter);
    QSettings settings;
    if(settings.value("logoPath").isValid()){
        logo->setPixmap(QPixmap(settings.value("logoPath").toString()));
    }

    layoutLogo->addStretch();
    layoutLogo->addWidget(logo);
    layoutLogo->addStretch();

    mainLayout->addLayout(layoutLogo);
    mainLayout->setMargin(30);
    mainLayout->addStretch();
    setLayout(mainLayout);

}

void DashboardWindow::setLogo()
{
    QSettings settings;

    logo->setPixmap(QPixmap(settings.value("logoPath").toString()));
    qDebug() << "New logo setted: " << settings.value("logoPath").toString();


    logo->repaint();
}
