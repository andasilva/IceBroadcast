#-------------------------------------------------
#
# Project created by QtCreator 2017-08-29T17:37:10
#
#-------------------------------------------------

QT       += core gui network multimediawidgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IceBroadcast
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        IceBroadcast.cpp \
    menu/buttonmenu.cpp \
    menu/menu.cpp \
    windows/liveaudiowindow.cpp \
    windows/settingswindow.cpp \
    windows/dashboardwindow.cpp \
    windows/audiowindow.cpp \
    windows/livetvwindow.cpp \
    stream/audio/controleuraudio.cpp \
    audio/waveform.cpp \
    audio/playlistmanager.cpp \
    stream/livemanager.cpp \
    stream/streamengine.cpp \
    audio/audioinfo.cpp \
    stream/workerstream.cpp \
    audio/vumeter.cpp
    
HEADERS += \
        IceBroadcast.h \
    menu/buttonmenu.h \
    menu/menu.h \
    config.h \
    windows/liveaudiowindow.h \
    windows/settingswindow.h \
    windows/dashboardwindow.h \
    windows/audiowindow.h \
    windows/livetvwindow.h \
    stream/audio/controleuraudio.h \
    lib/shout.h \
    audio/waveform.h \
    audio/playlistmanager.h \
    stream/livemanager.h \
    stream/streamengine.h \
    audio/audioinfo.h \
    stream/workerstream.h \
    audio/vumeter.h
    
RESOURCES += \
    ressources.qrc
    
INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/ -lshout

FORMS +=

DISTFILES +=

unix:!macx: LIBS += -lmp3lame
