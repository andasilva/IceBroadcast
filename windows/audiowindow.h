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
    QPushButton* buttonPlayPause;
    QPushButton* buttonStop;
    QPushButton* buttonPrevious;
    QPushButton* buttonNext;

    QListWidget* listPlaylist;
    QLCDNumber* time;
    QTableWidget* tableMusic;
    QSlider* slider;
    QLabel* labelPlaylist;

    int currentPlaylist;
    int selectedSong;
    int playingSong;
    bool isPlaying;

    void loadPlaylistAvaible();
    void listContentPlaylist(int playlistNumber);
    void getAndShowInfoMusic(QString path);
    void setupUi();
signals:

private slots:
    void addSongPressed();
    void removeSongPressed();
    void addPlaylistPressed();
    void removePlaylistPressed();
    void playPausePressed();
    void songDoubleClick(int y, int x);
    void stopPressed();
    void previousPressed();
    void nextPressed();

    void tableClicked(int,int);
    void updateCurrentPlaylist(int playlistNumber);

};

#endif // AUDIOWINDOW_H
