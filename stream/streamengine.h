#ifndef STREAMENGINE_H
#define STREAMENGINE_H

#include "lib/shout.h"
#include <QtNetwork>
#include <QtMultimedia>
#include "workerstream.h"

class StreamEngine:public QObject
{
    Q_OBJECT
public:
    static StreamEngine& getInstance(){
        static StreamEngine streamEngine;
        return streamEngine;

    }

    bool getIsRunning() const;
    void sendDataToPlay(const unsigned char* data, size_t length);

    shout_t *getConnexion() const;

    QString *getCurrentlyPlaying() const;

private:
    QThread *thread;
    StreamEngine(QObject *parent=0);
    shout_t *connexion;
    bool isRunning;
    QTimer* timerCheckConnexion;
    QFile *mp3File;
    WorkerStream* worker;
    QString *currentlyPlaying;

public slots:
    void connexionToServer();
    void checkConnexion();
    void playMusic(QString music);

signals:
    void connexionEstablished(bool response);

};

#endif // STREAMENGINE_H
