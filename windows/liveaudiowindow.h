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
    void updateStatus(QMediaRecorder::Status status);
    void onStateChanged(QMediaRecorder::State state);
    void updateProgess(qint64 pos);
};

#endif // LIVEAUDIOWINDOW_H
