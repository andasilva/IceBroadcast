#ifndef LIVETVWINDOW_H
#define LIVETVWINDOW_H

#include <QWidget>
#include <QtMultimediaWidgets>

class LiveTvWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LiveTvWindow(QWidget *parent = 0);

private:
    QVBoxLayout* mainLayout;
    bool isCameraPreview;
    QLabel *labelStatus, *labelTime, *labelSpace;
    QLCDNumber* time;
    QCamera *camera;
    QVideoWidget *videoWidget;
    QPushButton *buttonStart, *buttonStop, *buttonPreview;
    QCheckBox* checkBoxRecord;

    void setupUi();
    
signals:

public slots:
    void enablePreview();
};

#endif // LIVETVWINDOW_H
