#include "livetvwindow.h"
#include <QtWidgets>

LiveTvWindow::LiveTvWindow(QWidget *parent) : QWidget(parent)
{
    isCameraPreview = false;
    buttonStart = new QPushButton("Start Streaming");
    buttonStop = new QPushButton("Stop streaming");
    buttonPreview = new QPushButton("Preview");
    labelStatus = new QLabel("Status: Not streaming");
    labelTime = new QLabel("Duration of stream:");
    checkBoxRecord = new QCheckBox(tr("Save live session into a file"));
    labelSpace = new QLabel("<b>Video preview</b>");
    labelSpace->setAlignment(Qt::AlignCenter);
    labelSpace->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    labelSpace->setStyleSheet("border: 1px solid; background-color: black; color:white");
    time = new QLCDNumber;
    time->setDigitCount(8);
    time->display(QString("00:00:00"));

    videoWidget = new QVideoWidget;


    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonStart);
    buttonLayout->addWidget(buttonStop);

    QHBoxLayout *streamLayout = new QHBoxLayout;
    streamLayout->addWidget(labelTime);
    streamLayout->addWidget(time);
    streamLayout->addStretch();


    QVBoxLayout *previewLayout = new QVBoxLayout;
    previewLayout->addWidget(buttonPreview);
    previewLayout->addWidget(videoWidget);

    mainLayout = new QVBoxLayout;

    mainLayout->addSpacing(30);
    mainLayout->addWidget(labelStatus);
    mainLayout->addLayout(streamLayout);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(new QLabel("<b>Video</b>"));
    mainLayout->addLayout(previewLayout);
    mainLayout->addWidget(labelSpace);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(checkBoxRecord);

    setLayout(mainLayout);

    connect(buttonPreview,&QPushButton::clicked,this,&LiveTvWindow::enablePreview);
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
