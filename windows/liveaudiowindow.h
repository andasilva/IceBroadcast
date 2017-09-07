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
    VuMeter* vuMeter;

    QTimer* timer;
    QAudioRecorder *audioRecorder;
    QAudioProbe *audioProbe;
    int elapsedSeconds;

    QAudioDeviceInfo device;
    AudioInfo *audioInfo;
    QAudioFormat format;

    void setupUi();

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
