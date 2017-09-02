#include "audiowindow.h"
#include <QtWidgets>

AudioWindow::AudioWindow(QWidget *parent) : QWidget(parent)
{
    setupUi();
    loadPlaylistAvaible();
    connect(listPlaylist,&QListWidget::currentRowChanged,this,&AudioWindow::updateCurrentPlaylist);
}

void AudioWindow::loadPlaylistAvaible()
{
    QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) +".IceBroadcast/playlist/";
    QDir directory(path);

    //If folder exists then list all the playlist
    if(directory.exists()){
        QStringList filter;
        filter << "*.txt";
        QStringList listFiles = directory.entryList(filter);
        if(listFiles.empty())
            buttonRemovePlaylist->setDisabled(true);
        else{
            foreach(QFileInfo file, listFiles){
                listPlaylist->addItem(file.baseName());
                listPlaylist->item(0)->setSelected(true);
                currentPlaylist = 0;
            }
            buttonRemovePlaylist->setDisabled(false);
        }

    }else{
        directory.mkpath(path);
        //Create default playlist
        QFile file(path+"default.txt");
        if(file.open(QIODevice::ReadWrite)){
            file.close();
            listPlaylist->addItem("default");
            listPlaylist->item(0)->setSelected(true);
            currentPlaylist = 0;
        }
    }
}

void AudioWindow::setupUi()
{
    //Instanciation
    buttonAddPlaylist = new QPushButton(tr("Add Playlist"));
    buttonRemovePlaylist = new QPushButton(tr("RemovePlaylist"));
    listPlaylist = new QListWidget();
    listPlaylist->setMaximumWidth(200);


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

    labelPlaylist = new QLabel(tr("<b>Playlists</b>"));

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
    bool ok;
    QString playlistName = QInputDialog::getText(this,tr("Create a playlist"),tr("Playlist name:"),QLineEdit::Normal,"",&ok);
    if(ok && !playlistName.isEmpty()){
        QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) + ".IceBroadcast/playlist/" + playlistName + ".txt";
        if(QFile::exists(path)){
            qDebug() << "This playlist name already exits...";
            QMessageBox::warning(this,tr("Duplicate playlist name"),tr("This playlist name already exists... Write another playlist name."),QMessageBox::Ok);
        }else{
            QFile file(path);
            if(file.open(QIODevice::ReadWrite)){
                file.close();
                qDebug() << "New playlist created: " << playlistName;
                listPlaylist->clear();
                loadPlaylistAvaible();
            }
        }
    }
}

void AudioWindow::removePlaylistPressed()
{
    int response = QMessageBox::question(this,tr("Delete playlist"),tr("Are you sure you want to delete %1 playlist?").arg(listPlaylist->item(currentPlaylist)->text()),QMessageBox::Yes | QMessageBox::No);

    if(response == QMessageBox::Yes){
        QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) + ".IceBroadcast/playlist/" + listPlaylist->item(currentPlaylist)->text() + ".txt";
        QFile file(path);
        file.remove();
        listPlaylist->clear();
        loadPlaylistAvaible();
    }
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

void AudioWindow::updateCurrentPlaylist(int playlistNumber)
{
    currentPlaylist = playlistNumber;
}
