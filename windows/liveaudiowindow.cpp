/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#include "liveaudiowindow.h"
#include "stream/streamengine.h"
#include <lame/lame.h>

const int BufferSize = 4096;

LiveAudioWindow::LiveAudioWindow(QWidget *parent) : QWidget(parent), device(QAudioDeviceInfo::defaultInputDevice()), audioInfo(0), audioInput(0)
{
    setupUi();
    audioRecorder = new QAudioRecorder(this);
    audioProbe = new QAudioProbe;
    audioProbe->setSource(audioRecorder);

    timer = new QTimer(this);
    timer->setInterval(1000);
    elapsedSeconds = 0;

    connect(timer, &QTimer::timeout, this, &LiveAudioWindow::updateTime);
}

void LiveAudioWindow::setupUi()
{
    //Instanciation
    time = new QLCDNumber(this);
    time->setDigitCount(5);
    time->display(QString("00:00"));
    time->setSegmentStyle(QLCDNumber::Flat);
    time->setFrameStyle(QFrame::NoFrame);
    time->setMinimumSize(300, 100);

    vuMeter = new VuMeter(this);
    sliderGain = new QSlider(Qt::Horizontal);
    sliderGain->setMaximum(100);
    sliderGain->setMinimum(0);
    sliderGain->setValue(50);
    sliderGain->setMinimumWidth(200);

    checkBoxRecord = new QCheckBox(tr("Save live session into a file"));
    labelGain = new QLabel(tr("Gain : "));
    labelLevel = new QLabel(tr("Microphone level : "));
    labelStatus = new QLabel(tr("Not recording"));

    labelMicLogo = new QLabel();
    labelMicLogo->setPixmap(QPixmap(":/ressources/medias/images/big_mic.png"));

    buttonStart = new QPushButton(tr("Start"));
    buttonStop = new QPushButton(tr("Stop"));
    buttonStop->setEnabled(false);

    //Sub Layouts
    QHBoxLayout* timeLayout = new QHBoxLayout;
    timeLayout->addStretch();
    timeLayout->addWidget(time);
    timeLayout->addStretch();

    QHBoxLayout* logoLayout = new QHBoxLayout;
    logoLayout->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(labelMicLogo);

    QHBoxLayout* levelLayout = new QHBoxLayout;
    levelLayout->addWidget(labelLevel);
    levelLayout->addWidget(vuMeter);
    levelLayout->addStretch(20);
    levelLayout->addWidget(labelGain);
    levelLayout->addWidget(sliderGain);

    QHBoxLayout* actionsLayout = new QHBoxLayout;
    actionsLayout->addStretch();
    actionsLayout->addWidget(buttonStart);
    actionsLayout->addWidget(buttonStop);
    actionsLayout->addStretch();

    QHBoxLayout* optionsLayout = new QHBoxLayout;
    optionsLayout->addWidget(checkBoxRecord);
    optionsLayout->addStretch(20);
    optionsLayout->addWidget(labelStatus);

    //Main Layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(levelLayout);
    mainLayout->addStretch(20);
    mainLayout->addLayout(timeLayout);
    mainLayout->addStrut(20);
    mainLayout->addLayout(logoLayout);
    mainLayout->addLayout(actionsLayout);
    mainLayout->addStretch(20);
    mainLayout->addLayout(optionsLayout);

    this->setLayout(mainLayout);

    //Connections
    connect(buttonStart, &QPushButton::clicked, this, &LiveAudioWindow::playLive);
    connect(buttonStop, &QPushButton::clicked, this, &LiveAudioWindow::stopLive);
}

void LiveAudioWindow::initializeVuMeter()
{
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/wav");

    QAudioDeviceInfo info(device);
    if (!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }

    if (audioInfo)
    {
        delete audioInfo;
    }

    audioInfo  = new AudioInfo(format, this);
    connect(audioInfo, SIGNAL(update()), SLOT(refreshDisplay()));

    createVuMeter();
}

void LiveAudioWindow::createVuMeter()
{
    audioInput = new QAudioInput(device, format, this);
    audioInfo->start();
    audioInput->start(audioInfo);
}

void LiveAudioWindow::stopVuMeter()
{
    audioInfo->stop();
    audioInput->stop();
    vuMeter->setLevel(0);
}

void LiveAudioWindow::playLive()
{
    if(checkBoxRecord->isChecked())
    {
        QAudioEncoderSettings audioSettings;
        audioSettings.setCodec("audio/mpeg, mpegversion=(int)1, layer=(int)3");
        audioSettings.setSampleRate(0);
        audioSettings.setBitRate(0);
        audioSettings.setChannelCount(1);

        audioRecorder->setEncodingSettings(audioSettings, QVideoEncoderSettings(),"audio/mpeg, mpegversion=(int)1");
        audioRecorder->setOutputLocation(QUrl(QStandardPaths::locate(QStandardPaths::MusicLocation, QString(),QStandardPaths::LocateDirectory) + "Record_" + QDateTime::currentDateTime().toString() + ".mp3"));
        audioRecorder->record();

        labelStatus->setText(tr("Recoding"));
    }

    initializeVuMeter();

    //Update UI
    buttonStart->setEnabled(false);
    buttonStop->setEnabled(true);
    checkBoxRecord->setEnabled(false);
    timer->start();
}

void LiveAudioWindow::stopLive()
{
    //Update UI
    buttonStart->setEnabled(true);
    buttonStop->setEnabled(false);
    checkBoxRecord->setEnabled(true);
    labelStatus->setText(tr("Not Recording"));
    timer->stop();
    elapsedSeconds = 0;
    time->display("00:00");

    stopVuMeter();

    if(checkBoxRecord->isChecked())
    {
        audioRecorder->stop();
        QMessageBox::information(this, tr("Recording"), tr("The session has been record in %1").arg(QStandardPaths::locate(QStandardPaths::MusicLocation, QString(),QStandardPaths::LocateDirectory)), QMessageBox::Ok);
    }
}

void LiveAudioWindow::updateTime()
{
    elapsedSeconds++;
    QDateTime dateTime = QDateTime::fromTime_t(elapsedSeconds);
    time->display(dateTime.toString("mm:ss"));
}

//Unused function that try to convert PCM to MP3 on the fly
void LiveAudioWindow::processBuffer(const QAudioBuffer& buffer)
{
    const short int* data = buffer.data<short int>();

    int pcm_size = buffer.byteCount();

    unsigned char mp3Buffer[pcm_size];
    short int pcm_buffer[pcm_size];

    for(int i = 0; i < pcm_size ; i++){
        pcm_buffer[i] = data[i];
    }

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame,44100);
    lame_set_VBR(lame,vbr_default);
    lame_init_params(lame);

    lame_encode_buffer_interleaved(lame,pcm_buffer,pcm_size, mp3Buffer,pcm_size);
    lame_encode_flush(lame,mp3Buffer,pcm_size);
    lame_close(lame);

    StreamEngine& streamEngine = StreamEngine::getInstance();
    streamEngine.sendDataToPlay(mp3Buffer,pcm_size);

}

void LiveAudioWindow::refreshDisplay()
{
    vuMeter->setLevel(audioInfo->level());
}
