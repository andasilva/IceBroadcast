#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QtWidgets>

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = 0);
    QLabel *labelServer, *labelAudio, *labelVideo, *labelPreferences;
    QLabel *labelServerAdress, *labelUsername, *labelPassword, *labelMountpoint, *labelPort;
    QLabel *labelAudioInputSource, *labelAudioOutputSource;
    QLabel *labelVideoInputSource;
    QLabel *labelThemes, *labelLogoPath;

    QLineEdit *textServerAdress, *textUsername, *textPassword, *textMountpoint, *textPort;

    QPushButton *buttonSave;

signals:

public slots:
};

#endif // SETTINGSWINDOW_H
