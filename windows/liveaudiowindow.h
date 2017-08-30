#ifndef LIVEAUDIOWINDOW_H
#define LIVEAUDIOWINDOW_H

#include <QWidget>
#include <QtWidgets>

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

    void setupUi();

signals:

public slots:
};

#endif // LIVEAUDIOWINDOW_H
