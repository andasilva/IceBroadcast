#include "songinfo.h"
#include <QtMultimedia>

SongInfo::SongInfo(QString path)
{
    this->path = path;

    qDebug() << "Path : " << path;
    QMediaPlayer* player = new QMediaPlayer;
    player->setMedia(QMediaContent(QUrl::fromLocalFile(path)));
    player->setVolume(50);
    player->play();


    qDebug() << "metadata : " << player->isMetaDataAvailable();
    qDebug() << "Title : " << player->metaData("Title").toString();
    this->title = player->metaData("Title").toString();
    this->artist = player->metaData("Artist").toString();
    delete player;

}

QString SongInfo::getArtist()
{
    return artist;
}

QString SongInfo::getTitle()
{
    return title;
}

QString SongInfo::getAlbum()
{
    return album;
}

QString SongInfo::getLength()
{
    return lenght;
}

QString SongInfo::getPath()
{
    return path;
}

QString SongInfo::getYear()
{
    return year;
}
