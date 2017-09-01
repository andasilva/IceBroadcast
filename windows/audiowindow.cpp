#include "audiowindow.h"
#include <QtWidgets>

AudioWindow::AudioWindow(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void AudioWindow::setupUi()
{
    //Instanciation
    buttonAddPlaylist = new QPushButton(tr("Add Playlist"));
    buttonRemovePlaylist = new QPushButton(tr("RemovePlaylist"));
    listPlaylist = new QListWidget();

    buttonPlayPause = new QPushButton(tr("Play/Pause"));
    buttonPrevious = new QPushButton(tr("Previous"));
    buttonNext = new QPushButton(tr("Next"));

    buttonAddSong = new QPushButton(tr("Add Song"));
    buttonRemoveSong = new QPushButton(tr("Remove song"));

    slider = new QSlider(Qt::Horizontal);
    time = new QLCDNumber();
    time->setDigitCount(5);
    time->display(QString("00:00"));

    labelPlaylist = new QLabel(tr("Playlists"));

    QStringList headers;
    headers << tr("Artist") << tr("Title") << tr("Album") << tr("Year") << tr("Lenght");

    tableMusic = new QTableWidget(0, 5);
    tableMusic->setHorizontalHeaderLabels(headers);
    tableMusic->setSelectionMode(QAbstractItemView::SingleSelection);
    tableMusic->setSelectionBehavior(QAbstractItemView::SelectRows);
    //connect(musicTable, SIGNAL(cellPressed(int,int)),this, SLOT(tableClicked(int,int)));

    //Playlist layout
    QVBoxLayout *playlistLayout = new QVBoxLayout;
    playlistLayout->addWidget(labelPlaylist);
    playlistLayout->addWidget(listPlaylist);
    playlistLayout->addWidget(buttonAddPlaylist);
    playlistLayout->addWidget(buttonRemovePlaylist);

    //Player layouts
    QHBoxLayout *topActionsLayout = new QHBoxLayout;
    topActionsLayout->addWidget(buttonPrevious);
    topActionsLayout->addWidget(buttonPlayPause);
    topActionsLayout->addWidget(buttonNext);
    topActionsLayout->addWidget(slider);
    topActionsLayout->addWidget(time);

    QHBoxLayout *bottomActionsLayout = new QHBoxLayout;
    bottomActionsLayout->addStretch(10);
    bottomActionsLayout->addWidget(buttonAddSong);
    bottomActionsLayout->addWidget(buttonRemoveSong);
    bottomActionsLayout->addStretch(10);

    QVBoxLayout *playerLayout = new QVBoxLayout;
    playerLayout->addLayout(topActionsLayout);
    playerLayout->addWidget(tableMusic);
    playerLayout->addLayout(bottomActionsLayout);

    //Main Layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(playlistLayout);
    mainLayout->addLayout(playerLayout);

    this->setLayout(mainLayout);

    //Connections

}
