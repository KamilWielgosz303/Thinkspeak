#ifndef CHART_DRAW_H
#define CHART_DRAW_H
#include <QChar>
#include <QtCharts>
#include <QObject>

QT_CHARTS_USE_NAMESPACE

class Chart_draw : public QObject
{
    Q_OBJECT

public:
    Chart_draw();
    void drawTemp(QVector<double> data,QVector<QString> time);

    QChartView *chartView;

signals:
    void sendSignal(QChartView *s1);

private:
    QLineSeries series;
    QChart chart;
};
#endif // CHART_DRAW_H
