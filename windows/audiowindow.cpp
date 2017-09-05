#include "audiowindow.h"
#include <QtWidgets>
#include "audio/songinfo.h"
#include "dashboardwindow.h"

AudioWindow::AudioWindow(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    setupUi();
    loadPlaylistAvaible();
    initUi();
}

void AudioWindow::setupUi()
{
    //Instanciation
    buttonAddPlaylist = new QPushButton(tr("Add Playlist"));
    buttonRemovePlaylist = new QPushButton(tr("Remove Playlist"));
    listPlaylist = new QListWidget();
    listPlaylist->setMaximumWidth(200);

    buttonPlay = new QPushButton(tr("Play"));
    buttonStop = new QPushButton(tr("Stop"));
    buttonStop->setEnabled(false);
    buttonPrevious = new QPushButton(tr("Previous"));
    buttonNext = new QPushButton(tr("Next"));

    buttonAddSong = new QPushButton(tr("Add Song"));
    buttonRemoveSong = new QPushButton(tr("Remove Song"));

    slider = new QSlider(Qt::Horizontal);
    time = new QLCDNumber();
    time->setDigitCount(5);
    time->display(QString("00:00"));
    timeTotal = new QLCDNumber();
    timeTotal->setDigitCount(5);
    timeTotal->display(QString("00:00"));

    labelPlaylist = new QLabel(tr("<b>Playlists</b>"));

    QStringList headers;
    headers << tr("Artist") << tr("Title") << tr("Album") << tr("Year") << tr("genre") << tr("Lenght") << tr("Bitrate") << tr("Sample Rate") << tr("Path");

    tableMusic = new QTableWidget(0, 9);
    tableMusic->setHorizontalHeaderLabels(headers);
    tableMusic->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    tableMusic->setSelectionMode(QAbstractItemView::SingleSelection);
    tableMusic->setSelectionBehavior(QAbstractItemView::SelectRows);

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
    topActionsLayout->addWidget(buttonPlay);
    topActionsLayout->addWidget(buttonNext);
    topActionsLayout->addWidget(time);
    topActionsLayout->addWidget(slider);
    topActionsLayout->addWidget(timeTotal);

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
    connect(buttonPlay, &QPushButton::clicked, this, &AudioWindow::playPressed);
    connect(buttonPrevious, &QPushButton::clicked, this, &AudioWindow::previousPressed);
    connect(buttonNext, &QPushButton::clicked, this, &AudioWindow::nextPressed);
    connect(buttonStop, &QPushButton::clicked, this, &AudioWindow::stopPressed);
    connect(buttonAddPlaylist, &QPushButton::clicked, this, &AudioWindow::addPlaylistPressed);
    connect(buttonRemovePlaylist, &QPushButton::clicked, this, &AudioWindow::removePlaylistPressed);
    connect(buttonAddSong, &QPushButton::clicked, this, &AudioWindow::addSongPressed);
    connect(buttonRemoveSong, &QPushButton::clicked, this, &AudioWindow::removeSongPressed);
    connect(tableMusic, SIGNAL(cellPressed(int,int)),this, SLOT(tableClicked(int,int)));
    connect(listPlaylist,&QListWidget::currentRowChanged,this,&AudioWindow::updateCurrentPlaylist);
    connect(tableMusic,&QTableWidget::cellDoubleClicked,this,&AudioWindow::songDoubleClick);
}

void AudioWindow::initUi()
{
    isPlaying = false;
    playingSong = -1;

    if(tableMusic->rowCount() == 0)
    {
        buttonPlay->setEnabled(false);
        selectedSong = -1;
    }
    else
    {
        selectedSong = 0;
        tableMusic->selectRow(selectedSong);
    }
}

void AudioWindow::loadPlaylistAvaible()
{
    QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) +".IceBroadcast/playlist/";
    QDir directory(path);

    //If folder exists then list all the playlist
    if(directory.exists())
    {
        QStringList filter;
        filter << "*.txt";
        QStringList listFiles = directory.entryList(filter);

        //If there is no playlist
        if(listFiles.empty())
        {
            buttonRemovePlaylist->setDisabled(true);
        }
        else
        {
            //Load title playlist
            foreach(QFileInfo file, listFiles)
            {
                listPlaylist->addItem(file.baseName());
            }

            listPlaylist->item(0)->setSelected(true);
            currentPlaylist = 0;
            listContentPlaylist(0);
            buttonRemovePlaylist->setDisabled(false);
        }
    }
    else
    {
        //create directory
        directory.mkpath(path);
        //Create default playlist
        QFile file(path+"default.txt");

        if(file.open(QIODevice::ReadWrite))
        {
            file.close();
            listPlaylist->addItem("default");
            listPlaylist->item(0)->setSelected(true);
            currentPlaylist = 0;
            listContentPlaylist(0);
        }
    }
}

void AudioWindow::listContentPlaylist(int playlistNumber)
{
    QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) + ".IceBroadcast/playlist/" + listPlaylist->item(playlistNumber)->text() + ".txt";
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    //Read playlist file
    QTextStream textStream(&file);
    while(!textStream.atEnd())
    {
        QString line = file.readLine();
        line.truncate(line.length() - 1);
        getAndShowInfoMusic(line);
        qDebug() << "Line : " << line;
    }

    initUi();
}

void AudioWindow::getAndShowInfoMusic(QString path)
{
    int numberOflines = tableMusic->rowCount()+1;
    tableMusic->setRowCount(numberOflines);

    //Get metadata from the song and put them in the table
    //"Artist" "Title" "Album" "Year" "genre" "Lenght" "Bitrate" "Sample Rate" "Path"
    SongInfo* song = new SongInfo(path);

    QTableWidgetItem* artistItem = new QTableWidgetItem(song->getArtist());
    artistItem->setFlags(artistItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 0, artistItem);

    QTableWidgetItem* titleItem = new QTableWidgetItem(song->getTitle());
    titleItem->setFlags(titleItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 1, titleItem);

    QTableWidgetItem* albumItem = new QTableWidgetItem(song->getAlbum());
    albumItem->setFlags(albumItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 2, albumItem);

    QTableWidgetItem* yearItem = new QTableWidgetItem(song->getYear());
    yearItem->setFlags(yearItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 3, yearItem);

    QTableWidgetItem* genreItem = new QTableWidgetItem(song->getGenre());
    genreItem->setFlags(genreItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 4, genreItem);

    QTableWidgetItem* lenghtItem = new QTableWidgetItem(song->getLength());
    lenghtItem->setFlags(lenghtItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 5, lenghtItem);

    QTableWidgetItem* bitrateItem = new QTableWidgetItem(song->getBitrate());
    bitrateItem->setFlags(bitrateItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 6, bitrateItem);

    QTableWidgetItem* sampleRateItem = new QTableWidgetItem(song->getSampleRate());
    sampleRateItem->setFlags(sampleRateItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 7, sampleRateItem);

    QTableWidgetItem* pathItem = new QTableWidgetItem(song->getPath());
    pathItem->setFlags(pathItem->flags() ^ Qt::ItemIsEditable);
    tableMusic->setItem(numberOflines-1, 8, pathItem);
}

void AudioWindow::addSongPressed()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Load song"),QStandardPaths::locate(QStandardPaths::MusicLocation, QString(),QStandardPaths::LocateDirectory),tr("Song Files (*.mp3)"));

    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        //Open file chooser
        QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) + ".IceBroadcast/playlist/" + listPlaylist->item(currentPlaylist)->text() + ".txt";
        QFile file(path);

        if(!file.open(QFile::Append | QFile::Text))
        {
            qDebug() << "Error while add Song on playlist";
            return;
        }

        QTextStream out(&file);
        out << fileName.toUtf8() << endl;
        file.close();
        getAndShowInfoMusic(fileName);
    }
}

void AudioWindow::removeSongPressed()
{
    int response = QMessageBox::question(this,tr("Remove song"),tr("Are you sure you want to delete this song from the playlist?"), QMessageBox::Yes | QMessageBox::No);

    if(response == QMessageBox::Yes)
    {
        QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) + ".IceBroadcast/playlist/" + listPlaylist->item(currentPlaylist)->text() + ".txt";
        QFile file(path);

        if(file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            //Erase and rewrite the file without the removed line
            QString s;
            QTextStream textStream(&file);
            int i = 0;

            while(!textStream.atEnd())
            {
                QString line = textStream.readLine();
                if(i != selectedSong)
                {
                    s.append(line + "\n");
                }
                i++;
            }

            file.resize(0);
            textStream << s;
            file.close();

            //Update the table
            tableMusic->removeRow(selectedSong);
        }
    }
}

void AudioWindow::addPlaylistPressed()
{
    bool ok;
    QString playlistName = QInputDialog::getText(this,tr("Create a playlist"),tr("Playlist name:"),QLineEdit::Normal,"",&ok);

    if(ok && !playlistName.isEmpty())
    {
        QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) + ".IceBroadcast/playlist/" + playlistName + ".txt";

        if(QFile::exists(path))
        {
            qDebug() << "This playlist name already exits...";
            QMessageBox::warning(this,tr("Duplicate playlist name"),tr("This playlist name already exists... Write another playlist name."),QMessageBox::Ok);
        }
        else
        {
            //Create the new playlist
            QFile file(path);

            if(file.open(QIODevice::ReadWrite))
            {
                file.close();
                qDebug() << "New playlist created: " << playlistName;
                listPlaylist->clear();
                loadPlaylistAvaible();

                //Set the new playlist as selected
                QList<QListWidgetItem*> items = listPlaylist->findItems(playlistName,Qt::MatchExactly);
                listPlaylist->setCurrentItem(items.at(0));
            }
        }
    }
}

void AudioWindow::removePlaylistPressed()
{
    int response = QMessageBox::question(this,tr("Delete playlist"),tr("Are you sure you want to delete %1 playlist?").arg(listPlaylist->item(currentPlaylist)->text()),QMessageBox::Yes | QMessageBox::No);

    if(response == QMessageBox::Yes)
    {
        //Delete the playlist file
        QString path = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(),QStandardPaths::LocateDirectory) + ".IceBroadcast/playlist/" + listPlaylist->item(currentPlaylist)->text() + ".txt";
        QFile file(path);
        file.remove();

        listPlaylist->clear();
        loadPlaylistAvaible();
    }
}

void AudioWindow::playPressed()
{
    if(isPlaying == false)
    {
        songDoubleClick(selectedSong, 0);
    }
}

void AudioWindow::songDoubleClick(int y, int x)
{
    qDebug() << "start playing : " << y;
    //Stream the audio
    StreamEngine &streamEngine = StreamEngine::getInstance();
    streamEngine.connexionToServer();
    streamEngine.playMusic(tableMusic->item(y,8)->text());

    //Update UI
    isPlaying = true;
    playingSong = selectedSong = y;
    buttonPlay->setEnabled(false);
    buttonStop->setEnabled(true);

    QDateTime dateTime = QDateTime::fromTime_t(tableMusic->item(playingSong, 5)->text().toInt());
    timeTotal->display(dateTime.toString("mm:ss"));
    emit playingSongChanged(tableMusic->item(playingSong, 0)->text() + " - " + tableMusic->item(playingSong, 1)->text());
}

void AudioWindow::stopPressed()
{
    if(isPlaying == true)
    {
        isPlaying = false;
        buttonStop->setEnabled(false);
        buttonPlay->setEnabled(true);
        StreamEngine &streamEngine = StreamEngine::getInstance();
        streamEngine.connexionToServer();
        streamEngine.stopMusic();
    }
}

void AudioWindow::previousPressed()
{
    if(playingSong > 0)
    {
        stopPressed();
        selectedSong--;
        tableMusic->selectRow(selectedSong);
        playPressed();
    }
}

void AudioWindow::nextPressed()
{
    if(playingSong < tableMusic->rowCount()-1 && playingSong != -1)
    {
        stopPressed();
        selectedSong++;
        tableMusic->selectRow(selectedSong);
        playPressed();
    }
}

void AudioWindow::tableClicked(int y, int x)
{
    selectedSong = y;
}

void AudioWindow::updateCurrentPlaylist(int playlistNumber)
{
    qDebug() << "Current playlist number: " << playlistNumber;
    currentPlaylist = playlistNumber;

    if(playlistNumber >= 0)
    {
        //Clear table music
        tableMusic->setRowCount(0);
        listContentPlaylist(playlistNumber);
    }
}

void AudioWindow::updateTime()
{

}
