#ifndef AUDIOWINDOW_H
#define AUDIOWINDOW_H

#include <QtWidgets>
#include <QtMultimedia>

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

    void setupUi();
signals:

private slots:
    void addSongPressed();
    void removeSongPressed();
    void addPlaylistPressed();
    void removePlaylistPressed();
    void playPausePressed();
    void stopPressed();
    void previousPressed();
    void nextPressed();

};

#endif // AUDIOWINDOW_H
