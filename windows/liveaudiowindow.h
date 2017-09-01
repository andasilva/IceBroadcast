#ifndef LIVEAUDIOWINDOW_H
#define LIVEAUDIOWINDOW_H

#include <QtWidgets>
#include <QtMultimedia>
#include "audio/audioinfo.h"

class LiveAudioWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LiveAudioWindow(QWidget *parent = 0);

    QPushButton* buttonStartStop;
    QLCDNumber* time;
    QSlider* sliderGain;
    QLabel* labelStatus;
    QCheckBox* checkBoxRecord;
    QLabel* labelLevel;
    QLabel* labelGain;

    QAudioDeviceInfo m_device;
    AudioInfo* m_audioInfo;
    QAudioFormat m_format;
    QAudioInput* m_audioInput;
    QIODevice* m_input;
    bool m_pullMode;
    QByteArray m_buffer;

    void setupUi();
    void initializeAudio();
    void createAudioInput();
    void readMore();

signals:

public slots:
    void playLive();
};

#endif // LIVEAUDIOWINDOW_H
