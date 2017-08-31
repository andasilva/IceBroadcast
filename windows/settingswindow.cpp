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
//    labelServerAdress->setFixedWidth(100);
    labelUsername = new QLabel("Username:");
    labelPassword = new QLabel("Password:");
    labelMountpoint = new QLabel("Mountpoint:");
    labelPort = new QLabel("Port:");

    //inputs
    textServerAdress = new QLineEdit;
    if(settings->value("server").isValid())
       textServerAdress->setText(settings->value("server").toString());
    textUsername = new QLineEdit;
    if(settings->value("username").isValid())
        textUsername->setText(settings->value("username").toString());
    textPassword = new QLineEdit;
    //textPassword->setEchoMode(QLineEdit::Password);
    if(settings->value("password").isValid())
        textPassword->setText(settings->value("password").toString());
    textMountpoint = new QLineEdit;
    if(settings->value("mountpoint").isValid())
        textMountpoint->setText(settings->value("mountpoint").toString());
    textPort = new QLineEdit;
    if(settings->value("port").isValid())
        textPort->setText(settings->value("port").toString());

    //layouts
    QVBoxLayout *layoutServer = new QVBoxLayout;

    QHBoxLayout *layoutServerFirstLine = new QHBoxLayout;
    layoutServerFirstLine->addWidget(labelServerAdress);
    layoutServerFirstLine->addWidget(textServerAdress);
    layoutServerFirstLine->addWidget(labelPort);
    layoutServerFirstLine->addWidget(textPort);

    QHBoxLayout *layoutServerSecondLine = new QHBoxLayout;
    layoutServerSecondLine->addWidget(labelUsername);
    layoutServerSecondLine->addWidget(textUsername);
    layoutServerSecondLine->addWidget(labelPassword);
    layoutServerSecondLine->addWidget(textPassword);

    QHBoxLayout *layoutServerThirdLine = new QHBoxLayout;
    layoutServerThirdLine->addWidget(labelMountpoint);
    layoutServerThirdLine->addWidget(textMountpoint);

    layoutServer->addLayout(layoutServerFirstLine);
    layoutServer->addLayout(layoutServerSecondLine);
    layoutServer->addLayout(layoutServerThirdLine);


    /*****************/
    /* Audio Section */
    /*****************/

    //labels
    labelAudioInputSource = new QLabel("Input source:");
    labelAudioOutputSource = new QLabel("Output source:");

    QHBoxLayout *layoutAudio = new QHBoxLayout;
    layoutAudio->addWidget(labelAudioInputSource);
    listAudioInput = new QComboBox;

    //Get Input Audio Devices Avaible on computer
    QList<QAudioDeviceInfo> audioDevicesInput = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);

    foreach(QAudioDeviceInfo dev, audioDevicesInput)
    {
       listAudioInput->addItem(dev.deviceName());
    }

    layoutAudio->addWidget(listAudioInput);

    //Get Outpu Audio devices avaible on computer
    listAudioOuput = new QComboBox;
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
    labelLogoPath = new QLabel("Logo path");
    buttonSelectLogoPath = new QPushButton(tr("Select file"));

    QHBoxLayout *layoutPreferences = new QHBoxLayout;
    layoutPreferences->addWidget(labelThemes);
    layoutPreferences->addWidget(listTheme);
    layoutPreferences->addWidget(labelLogoPath);




    //



    buttonSave = new QPushButton("Save");

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
    settings->setValue("audioInput",listAudioInput->itemData(listAudioInput->currentIndex()));

/*
    QMessageBox confirmationMessage;
    confirmationMessage.setText("Settings Saved");
    confirmationMessage.setIcon(QMessageBox::Information);
    confirmationMessage.exec();
    confirmationMessage.button(QMessageBox::Ok)->animateClick(1);
*/
}
