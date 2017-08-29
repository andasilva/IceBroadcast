#ifndef CONTROLEURAUDIO_H
#define CONTROLEURAUDIO_H

#include <QtNetwork>
#include "lib/shout.h"

class ControleurAudio:public QObject
{
    Q_OBJECT
public:
    static ControleurAudio& getInstance(){
        static ControleurAudio controleurAudio;
        return controleurAudio;

    }
    void connectToIcecastServer();

private:
    ControleurAudio(QObject *parent=0);
    QNetworkAccessManager *networkAccessManager;

public slots:
    void resultOfConnection(QNetworkReply *reply);
};

#endif // CONTROLEURAUDIO_H
