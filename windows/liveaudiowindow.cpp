#include "liveaudiowindow.h"
#include "stream/streamengine.h"
#include <lame/lame.h>

const int BufferSize = 4096;


LiveAudioWindow::LiveAudioWindow(QWidget *parent) : QWidget(parent)
{
    setupUi();
    audioRecorder = new QAudioRecorder(this);
    audioProbe = new QAudioProbe;
    audioProbe->setSource(audioRecorder);

    connect(audioRecorder, &QAudioRecorder::durationChanged,this,&LiveAudioWindow::updateProgess);
    connect(audioRecorder, &QAudioRecorder::stateChanged, this, &LiveAudioWindow::onStateChanged);
    connect(audioProbe,&QAudioProbe::audioBufferProbed,this,&LiveAudioWindow::processBuffer);

}

void LiveAudioWindow::setupUi()
{
    //Instanciation
    time = new QLCDNumber(this);
    time->setDigitCount(8);
    time->display(QString("00:00:00"));

    vuMeter = new VuMeter(this);
    sliderGain = new QSlider(Qt::Horizontal);
    checkBoxRecord = new QCheckBox(tr("Save live session into a file"));
    labelGain = new QLabel(tr("Gain"));
    labelLevel = new QLabel(tr("Microphone level"));
    labelStatus = new QLabel(tr("Not recording"));
    buttonStartStop = new QPushButton(tr("Start Live Audio"));
    buttonStart = new QPushButton(tr("Start"));
    buttonStop = new QPushButton(tr("Stop"));

    //Sub Layouts
    QHBoxLayout* timeLayout = new QHBoxLayout;
    timeLayout->addStretch(20);
    timeLayout->addWidget(time);
    timeLayout->addStretch(20);

    QHBoxLayout* labelLevelLayout = new QHBoxLayout;
    labelLevelLayout->addWidget(labelLevel);
    labelLevelLayout->addWidget(labelGain);

    QHBoxLayout* levelLayout = new QHBoxLayout;
    levelLayout->addWidget(vuMeter);
    levelLayout->addWidget(sliderGain);

    QHBoxLayout* actionsLayout = new QHBoxLayout;
    actionsLayout->addStretch(20);
    actionsLayout->addWidget(buttonStartStop);
    actionsLayout->addWidget(buttonStart);
    actionsLayout->addWidget(buttonStop);
    actionsLayout->addStretch(20);

    QHBoxLayout* optionsLayout = new QHBoxLayout;
    optionsLayout->addWidget(checkBoxRecord);
    optionsLayout->addStretch(20);
    optionsLayout->addWidget(labelStatus);

    //Main Layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(timeLayout);
    mainLayout->addStretch(20);
    mainLayout->addLayout(labelLevelLayout);
    mainLayout->addLayout(levelLayout);
    mainLayout->addStretch(20);
    mainLayout->addLayout(actionsLayout);
    mainLayout->addStretch(20);
    mainLayout->addLayout(optionsLayout);

    this->setLayout(mainLayout);

    //Connections
    connect(buttonStartStop,&QPushButton::clicked,this,&LiveAudioWindow::playTest);
    connect(buttonStart, &QPushButton::clicked,this,&LiveAudioWindow::playLive);
}


void LiveAudioWindow::playLive()
{
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/mpeg, mpegversion=(int)1, layer=(int)3");
    audioSettings.setSampleRate(0);
    audioSettings.setBitRate(0);
    audioSettings.setChannelCount(1);


    audioRecorder->setEncodingSettings(audioSettings,QVideoEncoderSettings(),"audio/mpeg, mpegversion=(int)1");
    audioRecorder->setOutputLocation(QUrl("/home/angelkiro/Musique/test.mp3"));
    StreamEngine& streamEngine = StreamEngine::getInstance();
    streamEngine.connexionToServer();
    audioRecorder->record();
}

void LiveAudioWindow::processBuffer(const QAudioBuffer& buffer)
{
    /*qDebug() << buffer.format().codec();
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    qDebug() << info.supportedCodecs();*/

    const short int* data = buffer.data<short int>();


    int pcm_size = buffer.byteCount();

    unsigned char mp3Buffer[pcm_size];
    short int pcm_buffer[pcm_size];

    for(int i = 0; i < pcm_size ; i++){
        pcm_buffer[i] = 0;
        qDebug() << data[i];
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


void LiveAudioWindow::pauseLive()
{

}

void LiveAudioWindow::playTest()
{
    StreamEngine& streamEngine = StreamEngine::getInstance();
    streamEngine.connexionToServer();
    streamEngine.sendMusicTest();
}

void LiveAudioWindow::updateStatus(QMediaRecorder::Status status)
{

}

void LiveAudioWindow::onStateChanged(QMediaRecorder::State state)
{

}

void LiveAudioWindow::updateProgess(qint64 pos)
{

}


