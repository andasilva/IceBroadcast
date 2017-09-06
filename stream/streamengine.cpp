#include "streamengine.h"
#include "lib/shout.h"
#include "workerstream.h"
#include <QSettings>

StreamEngine::StreamEngine(QObject *parent)
    :QObject(parent)
{
    currentlyPlaying = new QString("");

    shout_init();
    connexion = shout_new();
    isRunning = false;
    timerCheckConnexion = new QTimer(this);

    thread = new QThread(this);
    worker = new WorkerStream;
    worker->moveToThread(thread);
    QMetaObject::invokeMethod(worker,"start");
    connect(timerCheckConnexion,&QTimer::timeout,this,&StreamEngine::checkConnexion);
}

void StreamEngine::setIsRunning(bool value)
{
    isRunning = value;
}

QThread *StreamEngine::getThread() const
{
    return thread;
}

void StreamEngine::setThread(QThread *value)
{
    thread = value;
}

QString *StreamEngine::getCurrentlyPlaying() const
{
    return currentlyPlaying;
}

shout_t *StreamEngine::getConnexion() const
{
    return connexion;
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

void StreamEngine::stopMusic()
{
    worker->setAborted(true);
}

bool StreamEngine::connexionToServer()
{
    if(!isRunning){
        connexion = shout_new();
        qDebug() << "Trying to connect to server...";
        QSettings settings;

        qDebug() << settings.value("username").toString().toStdString().c_str()  << settings.value("username").toString().toStdString().c_str() << settings.value("password").toString().toStdString().c_str() << settings.value("mountpoint").toString().toStdString().c_str() << settings.value("server").toString().toStdString().c_str();
        shout_set_user(connexion,settings.value("username").toString().toStdString().c_str());
        shout_set_password(connexion, settings.value("password").toString().toStdString().c_str());
        shout_set_mount(connexion, settings.value("mountpoint").toString().toStdString().c_str());
        shout_set_host(connexion,settings.value("server").toString().toStdString().c_str());
        shout_set_protocol(connexion, SHOUT_PROTOCOL_HTTP);
        shout_set_format(connexion,SHOUT_FORMAT_MP3);
    }

    int resultConnexion = shout_open(connexion);
    switch(resultConnexion){
    case SHOUTERR_SUCCESS:
        qDebug() << "login sucessfull!";
        isRunning = true;
        //timerCheckConnexion->start(1500); //TODO: get 15000 from server file?
        emit connexionEstablished(true);
        return true;
        break;
    case SHOUTERR_NOLOGIN:
        qDebug() << "login error" ;
        break;
    default:
        qDebug() << "Error connexion:" << resultConnexion;
        break;
    }
    return false;

}



void StreamEngine::checkConnexion()
{
    qDebug() << "Check if connexion active: " << shout_get_connected(connexion);

    if(shout_get_connected(connexion) != SHOUTERR_CONNECTED){
        qDebug() << "Connexion interrupted";
        timerCheckConnexion->stop();
        emit connexionEstablished(false);
    }
}


void StreamEngine::playMusic(QString music)
{
    qDebug() << "Play music: " << music ;
    currentlyPlaying = new QString(music);

    qDebug() << "Thread state:" << thread->isFinished() << thread->isRunning();
    if(!thread->isRunning()){
        qDebug() << "New thread created";
        thread = new QThread;
        worker = new WorkerStream;
        worker->moveToThread(thread);
        QMetaObject::invokeMethod(worker,"start");
        thread->start();
    }else{
        qDebug() << "Play anoter song....";
        worker->playAnotherSong(music);
    }
}




