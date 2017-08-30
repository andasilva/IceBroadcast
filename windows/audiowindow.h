#ifndef AUDIOWINDOW_H
#define AUDIOWINDOW_H

#include <QtWidgets>

class QTableWidget;
class QLCDNumber;

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
    QPushButton* buttonPrevious;
    QPushButton* buttonNext;

    QListWidget* listPlaylist;
    QLCDNumber *time;
    QTableWidget *tableMusic;

    void setupUi();
signals:

public slots:
};

#endif // AUDIOWINDOW_H
