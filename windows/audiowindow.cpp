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

    QStringList headers;
    headers << tr("Artist") << tr("Title") << tr("Album") << tr("Year") << tr("Lenght");

    tableMusic = new QTableWidget(0, 5);
    tableMusic->setHorizontalHeaderLabels(headers);
    tableMusic->setSelectionMode(QAbstractItemView::SingleSelection);
    tableMusic->setSelectionBehavior(QAbstractItemView::SelectRows);
    //connect(musicTable, SIGNAL(cellPressed(int,int)),this, SLOT(tableClicked(int,int)));

    //Playlist layout
    QVBoxLayout *playlistLayout = new QVBoxLayout;
    playlistLayout->addWidget(listPlaylist);
    playlistLayout->addWidget(buttonAddPlaylist);
    playlistLayout->addWidget(buttonRemovePlaylist);

    //Player layouts
    QHBoxLayout *topActionsLayout = new QHBoxLayout;
    topActionsLayout->addWidget(buttonPrevious);
    topActionsLayout->addWidget(buttonPlayPause);
    topActionsLayout->addWidget(buttonNext);

    QHBoxLayout *bottomActionsLayout = new QHBoxLayout;
    bottomActionsLayout->addWidget(buttonAddSong);
    bottomActionsLayout->addWidget(buttonRemoveSong);

    QVBoxLayout *playerLayout = new QVBoxLayout;
    playerLayout->addLayout(topActionsLayout);
    playerLayout->addWidget(tableMusic);
    playerLayout->addLayout(bottomActionsLayout);

    //Main Layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(playlistLayout);
    mainLayout->addLayout(playerLayout);

    this->setLayout(mainLayout);

}
