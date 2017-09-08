/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#include "controleuraudio.h"
#include <QtWidgets>
#include <QtNetwork>

ControleurAudio::ControleurAudio(QObject *parent) : QObject(parent)
{
    this->networkAccessManager = new QNetworkAccessManager();
    connect(networkAccessManager,&QNetworkAccessManager::finished, this, &ControleurAudio::resultOfConnection);
}

void ControleurAudio::connectToIcecastServer()
{
    QSettings settings;

    connexion = shout_new();
    shout_set_user(connexion,settings.value("username").toString().toStdString().c_str());
    shout_set_password(connexion, settings.value("password").toString().toStdString().c_str());
    shout_set_mount(connexion, settings.value("mountpoint").toString().toStdString().c_str());
    shout_set_host(connexion,settings.value("server").toString().toStdString().c_str());
}

void ControleurAudio::resultOfConnection(QNetworkReply *reply)
{
    QByteArray content = reply->readAll();

    //read header for debug
    QList<QByteArray> headers = reply->rawHeaderList();
    QListIterator<QByteArray> it(headers);

    while(it.hasNext())
    {
        QByteArray hName = it.next();
    }
}
