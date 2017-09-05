#ifndef AUDIOWINDOW_H
#define AUDIOWINDOW_H

#include <QtWidgets>
#include <QtMultimedia>
#include "stream/streamengine.h"

class AudioWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AudioWindow(QWidget *parent = 0);

private:
    QPushButton* buttonAddPlaylist;
    QPushButton* buttonRemovePlaylist;
    QPushButton* buttonAddSong;
    QPushButton* buttonRemoveSong;
    QPushButton* buttonPlay;
    QPushButton* buttonStop;
    QPushButton* buttonPrevious;
    QPushButton* buttonNext;

    QListWidget* listPlaylist;
    QLCDNumber* time;
    QLCDNumber* timeTotal;
    QTableWidget* tableMusic;
    QSlider* slider;
    QLabel* labelPlaylist;

    int currentPlaylist;
    int selectedSong;
    int playingSong;
    bool isPlaying;
    QTimer* timer;

    void loadPlaylistAvaible();
    void listContentPlaylist(int playlistNumber);
    void getAndShowInfoMusic(QString path);
    void setupUi();
    void initUi();
signals:
    void playingSongChanged(QString songName);

private slots:
    void addSongPressed();
    void removeSongPressed();
    void addPlaylistPressed();
    void removePlaylistPressed();
    void playPressed();
    void songDoubleClick(int y, int x);
    void stopPressed();
    void previousPressed();
    void nextPressed();

    void tableClicked(int,int);
    void updateCurrentPlaylist(int playlistNumber);
    void updateTime();

};

#endif // AUDIOWINDOW_H
