#include "liveaudiowindow.h"
#include "stream/streamengine.h"

const int BufferSize = 4096;


LiveAudioWindow::LiveAudioWindow(QWidget *parent) : QWidget(parent)
  , m_device(QAudioDeviceInfo::defaultInputDevice())
  , m_audioInfo(0)
  , m_audioInput(0)
  , m_input(0)
  , m_pullMode(true)
  , m_buffer(BufferSize, 0)
{
    setupUi();
}

void LiveAudioWindow::setupUi()
{
    //Instanciation
    time = new QLCDNumber();
    time->setDigitCount(8);
    time->display(QString("00:00:00"));

    sliderGain = new QSlider(Qt::Horizontal);
    checkBoxRecord = new QCheckBox(tr("Save live session into a file"));
    labelGain = new QLabel(tr("Gain"));
    labelLevel = new QLabel(tr("Microphone level"));
    labelStatus = new QLabel(tr("Not recording"));
    buttonStartStop = new QPushButton(tr("Start Live Audio"));

    //Sub Layouts
    QHBoxLayout* timeLayout = new QHBoxLayout;
    timeLayout->addStretch(20);
    timeLayout->addWidget(time);
    timeLayout->addStretch(20);

    QHBoxLayout* labelLevelLayout = new QHBoxLayout;
    labelLevelLayout->addWidget(labelLevel);
    labelLevelLayout->addWidget(labelGain);

    QHBoxLayout* levelLayout = new QHBoxLayout;
    levelLayout->addSpacing(200);
    levelLayout->addWidget(sliderGain);

    QHBoxLayout* actionsLayout = new QHBoxLayout;
    actionsLayout->addStretch(20);
    actionsLayout->addWidget(buttonStartStop);
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
    connect(buttonStartStop,&QPushButton::clicked,this,&LiveAudioWindow::playLive);
}

void LiveAudioWindow::playLive()
{
    //StreamEngine& streamEngine = StreamEngine::getInstance();
    //streamEngine.connexionToServer();
    initializeAudio();
}


void LiveAudioWindow::initializeAudio()
{
    m_format.setSampleRate(8000);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setSampleType(QAudioFormat::SignedInt);
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setCodec("audio/pcm");

    QAudioDeviceInfo info(m_device);
    if (!info.isFormatSupported(m_format))
    {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }

    if (m_audioInfo)
    {
        delete m_audioInfo;
    }

    m_audioInfo  = new AudioInfo(m_format, this);
    //connect(m_audioInfo, SIGNAL(update()), SLOT(refreshDisplay()));

    createAudioInput();
}

void LiveAudioWindow::createAudioInput()
{
    m_audioInput = new QAudioInput(m_device, m_format, this);
    qreal initialVolume = QAudio::convertVolume(m_audioInput->volume(), QAudio::LinearVolumeScale, QAudio::LogarithmicVolumeScale);

    m_audioInfo->start();
    m_audioInput->start(m_audioInfo);
}

void LiveAudioWindow::readMore()
{
    if (!m_audioInput)
    {
        return;
    }

    qint64 len = m_audioInput->bytesReady();

    if (len > BufferSize)
    {
        len = BufferSize;
    }

    qint64 l = m_input->read(m_buffer.data(), len);

    if (l > 0)
    {
        m_audioInfo->write(m_buffer.constData(), l);
    }
}

//void LiveAudioWindow::toggleMode()
//{
//    // Change bewteen pull and push modes
//    m_audioInput->stop();

//    if (m_pullMode) {
//        m_modeButton->setText(tr(PULL_MODE_LABEL));
//        m_input = m_audioInput->start();
//        connect(m_input, SIGNAL(readyRead()), SLOT(readMore()));
//        m_pullMode = false;
//    } else {
//        m_modeButton->setText(tr(PUSH_MODE_LABEL));
//        m_pullMode = true;
//        m_audioInput->start(m_audioInfo);
//    }

//    m_suspendResumeButton->setText(tr(SUSPEND_LABEL));
//}
