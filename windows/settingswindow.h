/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QtWidgets>

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = 0);

private:
    QLabel *labelServer, *labelAudio, *labelVideo, *labelPreferences;
    QLabel *labelServerAdress, *labelUsername, *labelPassword, *labelMountpoint, *labelPort;
    QLabel *labelAudioInputSource, *labelAudioOutputSource;
    QLabel *labelVideoInputSource;
    QLabel *labelThemes, *labelLogoPathTitle, *labelLogoPath;

    QLineEdit *textServerAdress, *textUsername, *textPassword, *textMountpoint, *textPort;

    QComboBox *listAudioInput, *listVideoInput, *listTheme, *listAudioOuput;

    QPushButton *buttonSave, *buttonSelectLogoPath;

    QSettings *settings;

signals:
    void logoUpdated();
public slots:
    void saveSettings();
    void loadLogoFile();
};

#endif // SETTINGSWINDOW_H
