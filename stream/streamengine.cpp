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
    connect(timerCheckConnexion,&QTimer::timeout,this,&StreamEngine::checkConnexion);
}

bool StreamEngine::getIsRunning() const
{
    return isRunning;
}

void StreamEngine::sendDataToPlay(const unsigned char *data, size_t length)
{
    long ret = shout_send(connexion, data, length);
    if (ret != SHOUTERR_SUCCESS) {
        printf("DEBUG: Send error: %s\n", shout_get_error(connexion));
    }

    shout_sync(connexion);
}

void StreamEngine::connexionToServer()
{

    if(!isRunning){
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
}



void StreamEngine::checkConnexion()
{
    if(shout_get_connected(connexion) != SHOUTERR_CONNECTED){
        qDebug() << "Connexion interrupted";
        timerCheckConnexion->stop();
    }
}

void StreamEngine::sendMusicTest()
{
    FILE * pFile;
    unsigned char buff[4096];

    pFile = fopen ("/home/angelkiro/Musique/test.mp3" , "r");
    if (pFile == NULL) perror ("Error opening file");

    long read, ret;

    while (true) {
        read = fread(buff, 1, sizeof(buff), pFile);
        qDebug() << read;
        if (read > 0) {
            ret = shout_send(connexion, buff, read);
            if (ret != SHOUTERR_SUCCESS) {
                printf("DEBUG: Send error: %s\n", shout_get_error(connexion));
                break;
            }
        } else {
            break;
        }
        shout_sync(connexion);
    }
}




