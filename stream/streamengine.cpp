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

    //To test
    shout_set_format(connexion,SHOUT_FORMAT_MP3);

    mp3File = new QFile(":/ressources/medias/sound.mp3");

    if(mp3File->open(QFile::ReadOnly)){
       qDebug() << "File opened";
    }else{
        qDebug() << "Error";
    }

    /*int fd = mp3File->handle();
    FILE* f = fdopen(fd, "rb");*/

    /*while (!mp3File->atEnd()) {
        QByteArray line = mp3File->readLine();
        shout_send(connexion,(unsigned char*) line.data(),(size_t) line.size());
    }*/


    FILE * pFile;
    unsigned char buff[4096];

    pFile = fopen ("/home/angelkiro/Documents/Dev/Qt/IceBroadcast/medias/sound.mp3" , "r");
    if (pFile == NULL) perror ("Error opening file");

    long read, ret;


    //Read 4096 bytes -> to trash.... only for testing
    for(int i=0; i<4096; i++){
        buff[i] = 0;
    }


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
    qDebug() << shout_get_error(connexion);
    qDebug() << shout_get_connected(connexion);
    //shout_send(connexion,(unsigned char*) mp3File->readAll().data(),(size_t) mp3File->size());
}

void StreamEngine::checkConnexion()
{
    if(shout_get_connected(connexion) != SHOUTERR_CONNECTED){
        qDebug() << "Connexion interrupted";
        timerCheckConnexion->stop();
    }
}




