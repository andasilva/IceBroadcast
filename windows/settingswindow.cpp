#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
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
    labelUsername = new QLabel("Username");
    labelPassword = new QLabel("Password");
    labelMountpoint = new QLabel("Mountpoint:");
    labelPort = new QLabel("Port:");

    //inputs
    textServerAdress = new QLineEdit;
    textUsername = new QLineEdit;
    textPassword = new QLineEdit;
    textMountpoint = new QLineEdit;
    textPort = new QLineEdit;

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

    /*****************/
    /* Video Section */
    /*****************/

    //labels
    labelVideoInputSource = new QLabel("Input source:");

    /***********************/
    /* Preferences Section */
    /***********************/
    //labels
    labelThemes = new QLabel("Themes:");
    labelLogoPath = new QLabel("Logo path");


    buttonSave = new QPushButton("Save");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(labelServer);
    mainLayout->addLayout(layoutServer);
    mainLayout->addStretch();
    mainLayout->addWidget(labelAudio);
    mainLayout->addStretch();
    mainLayout->addWidget(labelVideo);
    mainLayout->addStretch();
    mainLayout->addWidget(labelPreferences);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonSave);

    setLayout(mainLayout);
}
