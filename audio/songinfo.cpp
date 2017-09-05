#include "songinfo.h"
#include <QtMultimedia>

SongInfo::SongInfo(QString path)
{
    this->path = path;

    qDebug() << "Path : " << path;
    QMediaPlayer* player = new QMediaPlayer();
    player->setMedia(QMediaContent(QUrl::fromLocalFile(path)));
    player->setVolume(50);
    //player->play();

    if (player->isMetaDataAvailable())
    {
        qDebug() << player->metaData(QMediaMetaData::AlbumArtist).toString();
        qDebug() << player->metaData(QMediaMetaData::Title).toString();

        /*
        if (coverLabel) {
            QUrl url = player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();

            coverLabel->setPixmap(!url.isEmpty()
                    ? QPixmap(url.toString())
                    : QPixmap());
        }
        */
    }

    /*
    qDebug() << "metadata : " << player->isMetaDataAvailable();
    this->title = player->metaData("Title").toString();
    this->artist = player->metaData("Artist").toString();
    delete player;
    */
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
