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
    buttonStop = new QPushButton(tr("Stop"));
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
    //connect(tableMusic, SIGNAL(cellPressed(int,int)),this, SLOT(tableClicked(int,int)));

    //Playlist layout
    QVBoxLayout *playlistLayout = new QVBoxLayout;
    playlistLayout->addWidget(labelPlaylist);
    playlistLayout->addWidget(listPlaylist);
    playlistLayout->addWidget(buttonAddPlaylist);
    playlistLayout->addWidget(buttonRemovePlaylist);

    //Player layouts
    QHBoxLayout *topActionsLayout = new QHBoxLayout;
    topActionsLayout->addWidget(buttonPrevious);
    topActionsLayout->addWidget(buttonStop);
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
    connect(buttonPlayPause, &QPushButton::clicked, this, &AudioWindow::playPausePressed);
    connect(buttonPrevious, &QPushButton::clicked, this, &AudioWindow::previousPressed);
    connect(buttonNext, &QPushButton::clicked, this, &AudioWindow::nextPressed);
    connect(buttonStop, &QPushButton::clicked, this, &AudioWindow::stopPressed);
    connect(buttonAddPlaylist, &QPushButton::clicked, this, &AudioWindow::addPlaylistPressed);
    connect(buttonRemovePlaylist, &QPushButton::clicked, this, &AudioWindow::removePlaylistPressed);
    connect(buttonAddSong, &QPushButton::clicked, this, &AudioWindow::addSongPressed);
    connect(buttonRemoveSong, &QPushButton::clicked, this, &AudioWindow::removeSongPressed);
}

void AudioWindow::addSongPressed()
{

}

void AudioWindow::removeSongPressed()
{

}

void AudioWindow::addPlaylistPressed()
{

}

void AudioWindow::removePlaylistPressed()
{

}

void AudioWindow::playPausePressed()
{

}

void AudioWindow::stopPressed()
{

}

void AudioWindow::previousPressed()
{

}

void AudioWindow::nextPressed()
{

}
