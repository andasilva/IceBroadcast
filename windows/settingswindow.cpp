/*
 * IceBroadcast
 * P2 Project He-Arc
 * André Neto Da Silva & Axel Rieben
 * 8 september 2017
 */

#include "settingswindow.h"
#include <QtMultimedia>

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    settings = new QSettings;

    //groups labels
    labelServer = new QLabel("<b>Server</b>");
    labelAudio = new QLabel("<b>Audio</b>");
    labelVideo = new QLabel("<b>Video</b>");
    labelPreferences = new QLabel("<b>Preferences</b>");

    /******************/
    /* Server Section */
    /******************/

    //labels
    labelServerAdress = new QLabel("Server adress:");
    labelUsername = new QLabel("Username:");
    labelPassword = new QLabel("Password:");
    labelMountpoint = new QLabel("Mountpoint:");
    labelPort = new QLabel("Port:");

    //inputs
    textServerAdress = new QLineEdit;
    if(settings->value("server").isValid())
    {
        textServerAdress->setText(settings->value("server").toString());
    }

    textUsername = new QLineEdit;
    if(settings->value("username").isValid())
    {
        textUsername->setText(settings->value("username").toString());
    }

    textPassword = new QLineEdit;
    if(settings->value("password").isValid())
    {
        textPassword->setText(settings->value("password").toString());
    }

    textMountpoint = new QLineEdit;
    if(settings->value("mountpoint").isValid())
    {
        textMountpoint->setText(settings->value("mountpoint").toString());
    }

    textPort = new QLineEdit;
    if(settings->value("port").isValid())
    {
        textPort->setText(settings->value("port").toString());
    }

    //layouts
    QVBoxLayout *layoutServer = new QVBoxLayout;

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(labelServerAdress,0,0);
    gridLayout->addWidget(textServerAdress,0,1);
    gridLayout->addWidget(labelPort,0,2);
    gridLayout->addWidget(textPort,0,3);
    gridLayout->addWidget(labelUsername,1,0);
    gridLayout->addWidget(textUsername,1,1);
    gridLayout->addWidget(labelPassword,1,2);
    gridLayout->addWidget(textPassword,1,3);
    gridLayout->addWidget(labelMountpoint,2,0);
    gridLayout->addWidget(textMountpoint,2,1);

    layoutServer->addLayout(gridLayout);

    /*****************/
    /* Audio Section */
    /*****************/

    //labels
    labelAudioInputSource = new QLabel("Input source:");
    labelAudioOutputSource = new QLabel("Output source:");

    QHBoxLayout *layoutAudio = new QHBoxLayout;
    layoutAudio->addWidget(labelAudioInputSource);

    //Get Input Audio Devices Avaible on computer
    listAudioInput = new QComboBox;
    listAudioInput->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QList<QAudioDeviceInfo> audioDevicesInput = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);

    //display all devices and set one as default if saved in settings
    if(settings->value("audioInput").isValid())
    {
        int valueInSettings = 0;

        for(int i = 0; i < audioDevicesInput.length(); i++)
        {
            QString dev = audioDevicesInput.at(i).deviceName();
            listAudioInput->addItem(dev);
            if(!dev.compare(settings->value("audioInput").toString()))
            {
                valueInSettings = i;
            }
        }

        listAudioInput->setCurrentIndex(valueInSettings);
    }
    else
    {
        foreach(QAudioDeviceInfo dev, audioDevicesInput)
        {
            listAudioInput->addItem(dev.deviceName());
        }
    }

    layoutAudio->addWidget(listAudioInput);

    //Get Output Audio devices avaible on computer
    listAudioOuput = new QComboBox;
    listAudioOuput->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    QList<QAudioDeviceInfo> audioDevicesOutput = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

    foreach(QAudioDeviceInfo dev, audioDevicesOutput)
    {
        listAudioOuput->addItem(dev.deviceName());
    }

    layoutAudio->addWidget(labelAudioOutputSource);
    layoutAudio->addWidget(listAudioOuput);

    /*****************/
    /* Video Section */
    /*****************/

    //labels
    labelVideoInputSource = new QLabel("Input source:");
    QHBoxLayout *layoutVideo = new QHBoxLayout;
    layoutVideo->addWidget(labelVideoInputSource);

    listVideoInput = new QComboBox;
    listVideoInput->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    //Get Camera input on computer
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras() ;

    foreach(const QCameraInfo &cameraInfo, cameras)
    {
        listVideoInput->addItem(cameraInfo.deviceName()) ;
    }

    layoutVideo->addWidget(listVideoInput);

    /***********************/
    /* Preferences Section */
    /***********************/

    //labels
    labelThemes = new QLabel("Themes:");
    listTheme = new QComboBox;
    listTheme->addItem("Dark Theme");
    labelLogoPathTitle = new QLabel("Logo path:");
    labelLogoPath = new QLabel("No logo selected");

    if(settings->value("logoPath").isValid())
    {
        labelLogoPath->setText(settings->value("logoPath").toString());
    }

    labelLogoPath->setStyleSheet("border: 1px solid");
    buttonSelectLogoPath = new QPushButton(tr("Select file"));
    listTheme->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    labelLogoPath->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    buttonSave = new QPushButton("Save");

    connect(buttonSelectLogoPath,&QPushButton::clicked,this,&SettingsWindow::loadLogoFile);

    QHBoxLayout *layoutPreferences = new QHBoxLayout;
    layoutPreferences->addWidget(labelThemes);
    layoutPreferences->addWidget(listTheme);
    layoutPreferences->addWidget(labelLogoPathTitle);
    layoutPreferences->addWidget(labelLogoPath);
    layoutPreferences->addWidget(buttonSelectLogoPath);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(labelServer);
    mainLayout->addLayout(layoutServer);
    mainLayout->addStretch();
    mainLayout->addWidget(labelAudio);
    mainLayout->addLayout(layoutAudio);
    mainLayout->addStretch();
    mainLayout->addWidget(labelVideo);
    mainLayout->addLayout(layoutVideo);
    mainLayout->addStretch();
    mainLayout->addWidget(labelPreferences);
    mainLayout->addLayout(layoutPreferences);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonSave);

    mainLayout->setMargin(30);
    setLayout(mainLayout);

    //Save the settings
    connect(buttonSave,&QPushButton::clicked,this,&SettingsWindow::saveSettings);
}

void SettingsWindow::saveSettings()
{
    settings->setValue("server",textServerAdress->displayText());
    settings->setValue("port",textPort->displayText());
    settings->setValue("username",textUsername->displayText());
    settings->setValue("password",textPassword->displayText());
    settings->setValue("mountpoint",textMountpoint->displayText());
    settings->setValue("audioInput",listAudioInput->currentText());
    settings->setValue("audioOutput",listAudioOuput->currentText());
    settings->setValue("videoInput",listVideoInput->currentText());
    settings->setValue("theme",listTheme->currentText());

    //Update Logo if necessary
    if(labelLogoPath->text().compare(settings->value("logoPath").toString()))
    {
        settings->setValue("logoPath",labelLogoPath->text());
        emit logoUpdated();
    }
}

void SettingsWindow::loadLogoFile()
{
    //Open dialog box to choose logo file with default location in Pictures Folder
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),QStandardPaths::locate(QStandardPaths::PicturesLocation, QString(),QStandardPaths::LocateDirectory),tr("Image Files (*.png *.jpg)"));

    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        labelLogoPath->setText(fileName);
    }
}
