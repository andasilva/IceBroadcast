#ifndef SONGINFO_H
#define SONGINFO_H

#include <QtWidgets>

class SongInfo
{
public:
    SongInfo(QString path);

    QString getArtist();
    QString getTitle();
    QString getAlbum();
    QString getLength();
    QString getPath();
    QString getYear();

private:
    QString artist;
    QString title;
    QString album;
    QString lenght;
    QString path;
    QString year;
};

#endif // SONGINFO_H
