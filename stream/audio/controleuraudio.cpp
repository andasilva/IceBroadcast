#include "controleuraudio.h"
#include <QtWidgets>
#include <QtNetwork>


ControleurAudio::ControleurAudio(QObject *parent)
    :QObject(parent)
{
    this->networkAccessManager = new QNetworkAccessManager();
    connect(networkAccessManager,&QNetworkAccessManager::finished, this, &ControleurAudio::resultOfConnection);
}

void ControleurAudio::connectToIcecastServer()
{
    /*QString login = "souce:hackme";
    QByteArray data = login.toLocal8Bit().toBase64();
    QString headerData = "Basic "+ data;

    QNetworkRequest request(QUrl("http://192.168.1.104:8000/"));
    request.setRawHeader("Authorization",headerData.toLocal8Bit());

    networkAccessManager->get(request);*/


    QSettings settings;

    shout_init();
    connexion = shout_new();
    shout_set_user(connexion,settings.value("username").toString().toStdString().c_str());
    shout_set_password(connexion, settings.value("password").toString().toStdString().c_str());
    shout_set_mount(connexion, settings.value("mountpoint").toString().toStdString().c_str());
    shout_set_host(connexion,settings.value("server").toString().toStdString().c_str());

    int resultConnexion = shout_open(connexion);
    switch(resultConnexion){
    case SHOUTERR_NOLOGIN:
        qDebug() << "login error" ;
        break;
    default:
        qDebug() << resultConnexion;
        break;
    }
}

void ControleurAudio::resultOfConnection(QNetworkReply *reply)
{
    QByteArray content = reply->readAll();

    //read header for debug
    QList<QByteArray> headers = reply->rawHeaderList();
    QListIterator<QByteArray> it(headers);
    while(it.hasNext()){
        QByteArray hName = it.next();
        qDebug() << "En tete : "<< hName << " valeur: " << reply->rawHeader(hName);
    }

    //read the content
    qDebug() << "Contenu: " << QString::fromLocal8Bit(reply->readAll().data());

}
