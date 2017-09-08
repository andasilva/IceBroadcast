/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#ifndef LIVEAUDIOWINDOW_H
#define LIVEAUDIOWINDOW_H

#include <QtWidgets>
#include <QtMultimedia>
#include "audio/audioinfo.h"
#include "audio/vumeter.h"

class LiveAudioWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LiveAudioWindow(QWidget *parent = 0);

private:
    QPushButton *buttonStart, *buttonStop;
    QLCDNumber* time;
    QSlider* sliderGain;
    QLabel* labelStatus;
    QCheckBox* checkBoxRecord;
    QLabel* labelMicLogo;
    QLabel* labelLevel;
    QLabel* labelGain;

    QTimer* timer;
    QAudioRecorder *audioRecorder;
    QAudioProbe *audioProbe;
    int elapsedSeconds;

    VuMeter* vuMeter;
    QAudioDeviceInfo device;
    AudioInfo *audioInfo;
    QAudioInput *audioInput;
    QAudioFormat format;

    void setupUi();
    void initializeVuMeter();
    void createVuMeter();
    void stopVuMeter();

signals:

public slots:
    void processBuffer(const QAudioBuffer& buffer);
    void refreshDisplay();

private slots:
    void playLive();
    void stopLive();

    void updateTime();
};

#endif // LIVEAUDIOWINDOW_H
