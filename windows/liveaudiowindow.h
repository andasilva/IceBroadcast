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
    QPushButton* buttonStartStop, *buttonStart, *buttonStop;
    QLCDNumber* time;
    QSlider* sliderGain;
    QLabel* labelStatus;
    QCheckBox* checkBoxRecord;
    QLabel* labelLevel;
    QLabel* labelGain;
    VuMeter* vuMeter;

    void setupUi();

    QAudioRecorder *audioRecorder;
    QAudioProbe *audioProbe;


signals:


public slots:
    void processBuffer(const QAudioBuffer& buffer);

private slots:
    void playLive();
    void pauseLive();
    void playTest();

    void updateStatus(QMediaRecorder::Status status);
    void onStateChanged(QMediaRecorder::State state);
    void updateProgess(qint64 pos);
};

#endif // LIVEAUDIOWINDOW_H
