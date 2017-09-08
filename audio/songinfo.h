/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#ifndef SONGINFO_H
#define SONGINFO_H

#include <QtWidgets>
#include <taglib/fileref.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/tag.h>

class SongInfo
{
public:
    SongInfo(QString path);

    QString getArtist();
    QString getTitle();
    QString getAlbum();
    QString getPath();
    QString getYear();
    QString getGenre();

    QString getLength();
    QString getBitrate();
    QString getSampleRate();

private:
    QString artist;
    QString title;
    QString album;
    QString path;
    QString year;
    QString genre;

    QString lenght;
    QString bitrate;
    QString sampleRate;

    void readTags();
    void readAudioInfo();
};

#endif // SONGINFO_H
