#include "IceBroadcast.h"
#include "config.h"
#include "stream/audio/controleuraudio.h"

IceBroadcast::IceBroadcast(QWidget *parent)
    : QWidget(parent)
{
    // Load StyleSheet
    QFile file(":/ressources/medias/qss/default.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);


    // Create the menu and add it
    this->mainMenu = new Menu();
    mainLayout->addWidget(mainMenu,0,Qt::AlignLeft);
    connect(mainMenu,&Menu::hideWidgetWindow,this,&IceBroadcast::hideWidgetWindow);
    connect(mainMenu,&Menu::showWidgetWindow,this,&IceBroadcast::showWidgetWindow);

    // Create the windows and add it;
    this->dashboardWindow = new DashboardWindow(this);
    this->audioWindow = new AudioWindow(this);
    this->liveAudioWindow = new LiveAudioWindow(this);
    this->liveTvWindow = new LiveTvWindow(this);
    this->settingsWindow = new SettingsWindow(this);

    mainLayout->addWidget(dashboardWindow);
    mainLayout->addWidget(audioWindow);
    mainLayout->addWidget(liveAudioWindow);
    mainLayout->addWidget(liveTvWindow);
    mainLayout->addWidget(settingsWindow);

    audioWindow->hide();
    liveAudioWindow->hide();
    liveTvWindow->hide();
    settingsWindow->hide();

    //ONly for test
    /*ControleurAudio& audioControler = ControleurAudio::getInstance();
    audioControler.connectToIcecastServer();*/
}

void IceBroadcast::showWidgetWindow(int idButton)
{
    switch(idButton)
    {
    case BUTTON_HOME:
        dashboardWindow->show();
        break;
    case BUTTON_MUSIC:
        audioWindow->show();
        break;
    case BUTTON_LIVE_AUDIO:
        liveAudioWindow->show();
        break;
    case BUTTON_LIVE_TV:
        liveTvWindow->show();
        break;
    case BUTTON_SETTINGS:
        settingsWindow->show();
        break;
    }
}

void IceBroadcast::hideWidgetWindow(int idButton)
{
    switch(idButton)
    {
    case BUTTON_HOME:
        dashboardWindow->hide();
        break;
    case BUTTON_MUSIC:
        audioWindow->hide();
        break;
    case BUTTON_LIVE_AUDIO:
        liveAudioWindow->hide();
        break;
    case BUTTON_LIVE_TV:
        liveTvWindow->hide();
        break;
    case BUTTON_SETTINGS:
        settingsWindow->hide();
        break;
    }
}


IceBroadcast::~IceBroadcast()
{

}
