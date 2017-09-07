#include "livetvwindow.h"
#include <QtWidgets>

LiveTvWindow::LiveTvWindow(QWidget *parent) : QWidget(parent)
{
    isCameraPreview = false;
    setupUi();
    connect(buttonPreview,&QPushButton::clicked,this,&LiveTvWindow::enablePreview);
}

void LiveTvWindow::setupUi()
{
    buttonStart = new QPushButton("Start Streaming");
    buttonStop = new QPushButton("Stop Streaming");
    buttonPreview = new QPushButton("Preview");
    labelStatus = new QLabel("Not recording");
    checkBoxRecord = new QCheckBox(tr("Save live session into a file"));

    labelSpace = new QLabel("<b>Video preview</b>");
    labelSpace->setAlignment(Qt::AlignCenter);
    labelSpace->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    labelSpace->setStyleSheet("border: 1px solid; background-color: black; color:white");

    time = new QLCDNumber;
    time->setDigitCount(5);
    time->display(QString("00:00"));
    time->setSegmentStyle(QLCDNumber::Flat);
    time->setFrameStyle(QFrame::NoFrame);
    time->setMinimumSize(300, 100);

    videoWidget = new QVideoWidget;

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(buttonStart);
    buttonLayout->addWidget(buttonStop);
    buttonLayout->addWidget(buttonPreview);
    buttonLayout->addStretch();

    QHBoxLayout *streamLayout = new QHBoxLayout;
    streamLayout->addStretch();
    streamLayout->addWidget(time);
    streamLayout->addStretch();

    QVBoxLayout *previewLayout = new QVBoxLayout;
    previewLayout->addWidget(videoWidget);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(checkBoxRecord);
    bottomLayout->addStretch(20);
    bottomLayout->addWidget(labelStatus);

    mainLayout = new QVBoxLayout;
    mainLayout->addSpacing(30);
    mainLayout->addLayout(streamLayout);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(new QLabel("<b>Video</b>"));
    mainLayout->addLayout(previewLayout);
    mainLayout->addWidget(labelSpace);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}

void LiveTvWindow::enablePreview()
{
    if(!isCameraPreview){
        labelSpace->hide();
        QSettings settings;

        if(settings.value("videoInput").isValid()){
            camera= new QCamera(settings.value("server").toByteArray(),this);
            camera->setCaptureMode(QCamera::CaptureViewfinder) ;
            camera->setViewfinder(videoWidget) ;
            camera->start();
            isCameraPreview = true;
            videoWidget->show();
        }
    }else{
        camera->stop();
        isCameraPreview = false;
        labelSpace->show();
        videoWidget->hide();
    }
}
