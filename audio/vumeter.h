#ifndef VUMETER_H
#define VUMETER_H

#include <QtWidgets>

class VuMeter : public QWidget
{
    Q_OBJECT
public:
    VuMeter(QWidget *parent = 0);

    void setLevel(qreal value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal m_level;
    QPixmap m_pixmap;
};

#endif // VUMETER_H
