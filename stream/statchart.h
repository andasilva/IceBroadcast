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
    void getStats();
    bool static connectToDatabase();
private:
    QLineSeries* series;
    QChart* chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QTimer *timer;

    QChartView *chartView;
signals:

public slots:
    void updateDatabase();
};

#endif // STATCHART_H
