#ifndef CHART_DRAW_H
#define CHART_DRAW_H
#include <QChar>
#include <QtCharts>
#include <QObject>

QT_CHARTS_USE_NAMESPACE

class Chart : public QObject
{
    Q_OBJECT

public:
    Chart();
    void drawTemp(QVector<double> data,QVector<QString> time);

    QChartView *chartView;

    QChart *chart;

signals:
    void sendSignal(QChartView *s1);

private:
    QLineSeries series;
};
#endif // CHART_DRAW_H
