#ifndef STREAMENGINE_H
#define STREAMENGINE_H

#include "lib/shout.h"
#include <QtNetwork>
#include <QtMultimedia>

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

private:
    StreamEngine(QObject *parent=0);
    shout_t *connexion;
    bool isRunning;
    QTimer* timerCheckConnexion;
    QFile *mp3File;
    QThread *threadPlayAudio;

public slots:
    void connexionToServer();
    void checkConnexion();
    void sendMusicTest();

};

#endif // STREAMENGINE_H
