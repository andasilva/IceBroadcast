#include "vumeter.h"

VuMeter::VuMeter(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(false);

    m_level = 0;
    setMinimumHeight(30);
    setMinimumWidth(200);
}

void VuMeter::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.drawRect(QRect(painter.viewport().left()+10, painter.viewport().top()+10, painter.viewport().right()-20, painter.viewport().bottom()-20));

    if (m_level == 0.0)
    {
        return;
    }

    int pos = ((painter.viewport().right()-20)-(painter.viewport().left()+11))*m_level;
    painter.fillRect(painter.viewport().left()+11, painter.viewport().top()+10, pos, painter.viewport().height()-21, Qt::cyan);
}

void VuMeter::setLevel(qreal value)
{
    m_level = value;
    update();
}
