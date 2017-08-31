#include "streamengine.h"
#include "lib/shout.h"
#include <QSettings>

StreamEngine::StreamEngine(QObject *parent)
:QObject(parent)
{
    shout_init();
    connexion = shout_new();
    isRunning = false;
    timerCheckConnexion = new QTimer(this);
    threadPlayAudio = new QThread;
    //connect(timerCheckConnexion,&QTimer::timeout,this,&StreamEngine::checkConnexion);
}

bool StreamEngine::getIsRunning() const
{
    return isRunning;
}

void StreamEngine::connexionToServer()
{
    qDebug() << "Trying to connect to server...";
    QSettings settings;

    shout_set_user(connexion,settings.value("username").toString().toStdString().c_str());
    shout_set_password(connexion, settings.value("password").toString().toStdString().c_str());
    shout_set_mount(connexion, settings.value("mountpoint").toString().toStdString().c_str());
    shout_set_host(connexion,settings.value("server").toString().toStdString().c_str());
    shout_set_protocol(connexion, SHOUT_PROTOCOL_HTTP);
    shout_set_format(connexion,SHOUT_FORMAT_MP3);
    int resultConnexion = shout_open(connexion);
    switch(resultConnexion){
    case SHOUTERR_SUCCESS:
        qDebug() << "login sucessfull!";
        isRunning = true;
        timerCheckConnexion->start(15000); //TODO: get 15000 from server file?
        break;
    case SHOUTERR_NOLOGIN:
        qDebug() << "login error" ;
        break;
    default:
        qDebug() << resultConnexion;
        break;
    }
}

void StreamEngine::checkConnexion()
{
    if(shout_get_connected(connexion) != SHOUTERR_CONNECTED){
        qDebug() << "Connexion interrupted";
        timerCheckConnexion->stop();
    }
}




