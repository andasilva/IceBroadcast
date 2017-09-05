#include "dashboardwindow.h"
#include <QtWidgets>
#include "stream/streamengine.h"

DashboardWindow::DashboardWindow(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void DashboardWindow::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *layoutLogo = new QHBoxLayout;

    //load Logo
    logo = new QLabel(this);
    QSettings settings;

    if(settings.value("logoPath").isValid())
    {
        logo->setPixmap(QPixmap(settings.value("logoPath").toString()));
    }

    layoutLogo->addStretch();
    layoutLogo->addWidget(logo);
    layoutLogo->addStretch();

    //Labels
    labelServerStatus = new QLabel(tr("Server Status: Offline"));
    labelMusicBeingPlayed = new QLabel(tr("Currently playing : ------"));

    QVBoxLayout *layoutInfo = new QVBoxLayout;
    layoutInfo->addWidget(labelServerStatus);
    layoutInfo->addWidget(labelMusicBeingPlayed);

    mainLayout->addLayout(layoutLogo);
    mainLayout->setMargin(30);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(layoutInfo);
    mainLayout->addStretch();
    setLayout(mainLayout);
    connect(&(StreamEngine::getInstance()),&StreamEngine::connexionEstablished,this,&DashboardWindow::updateServerStatus);
}

void DashboardWindow::setLogo()
{
    QSettings settings;

    logo->setPixmap(QPixmap(settings.value("logoPath").toString()));
    qDebug() << "New logo setted: " << settings.value("logoPath").toString();

    logo->repaint();
}

void DashboardWindow::updateServerStatus(bool status)
{
    if(status)
    {
        labelServerStatus->setText("Server Status: Online");
    }
    else
    {
        labelServerStatus->setText("Server Status: Offline");
    }
}

void DashboardWindow::updateMusicBeingPlayed(QString nameSong)
{
    labelMusicBeingPlayed->setText("Currently playing : " + nameSong);
}
