#include "liveaudiowindow.h"
#include "stream/streamengine.h"

LiveAudioWindow::LiveAudioWindow(QWidget *parent) : QWidget(parent)
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

    connect(buttonStartStop,&QPushButton::clicked,this,&LiveAudioWindow::playLive);
}

void LiveAudioWindow::playLive()
{
    StreamEngine& streamEngine = StreamEngine::getInstance();
    streamEngine.connexionToServer();
}
