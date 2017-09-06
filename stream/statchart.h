#ifndef STATCHART_H
#define STATCHART_H

#include <QWidget>
#include <QtWidgets>
#include <QtCharts>

class StatChart : public QWidget
{
    Q_OBJECT
public:
    explicit StatChart(QWidget *parent = nullptr);
private:
    QLineSeries* series;
    QChart* chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;

    QChartView *chartView;
signals:

public slots:
};

#endif // STATCHART_H
