#include "songinfo.h"
#include <QtMultimedia>

SongInfo::SongInfo(QString path)
{
    this->path = path;
    readTags();
    readAudioInfo();
}

void SongInfo::readTags()
{
    TagLib::MPEG::File file(TagLib::FileName(path.toLocal8Bit()));

    if (file.isValid() && file.tag())
    {
        TagLib::ID3v2::Tag *fileTag = file.ID3v2Tag(true);

        this->artist = QString::fromUtf8(fileTag->artist().toCString(true));
        this->title = QString::fromUtf8(fileTag->title().toCString(true));
        this->album = QString::fromUtf8(fileTag->album().toCString(true));
        this->year = QString::number(fileTag->year());
        this->genre = QString::fromUtf8(fileTag->genre().toCString(true));
    }
}

void SongInfo::readAudioInfo()
{
    TagLib::FileRef ref(TagLib::FileName(path.toLocal8Bit()));

    if (ref.isNull() == false && ref.audioProperties())
    {
        TagLib::AudioProperties *properties = ref.audioProperties();
        this->lenght = QString::number(properties->length());
        this->sampleRate = QString::number(properties->sampleRate());
        this->bitrate = QString::number(properties->bitrate());
    }
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

QString SongInfo::getGenre()
{
    return genre;
}

QString SongInfo::getBitrate()
{
    return bitrate;
}

QString SongInfo::getSampleRate()
{
    return sampleRate;
}

QString SongInfo::getPath()
{
    return path;
}

QString SongInfo::getYear()
{
    return year;
}
