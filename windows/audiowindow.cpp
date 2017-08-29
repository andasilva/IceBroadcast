#include "audiowindow.h"
#include <QtWidgets>

AudioWindow::AudioWindow(QWidget *parent) : QWidget(parent)
{
    new QLabel("Audio Window", this);
}
