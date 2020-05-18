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
    ~Chart();
    void drawTemp(QVector<double> data,QVector<QString> time);
    void setData(QVector<QString>, QVector<double>, QString);
    QChart *chart;

signals:
    void sendSignal(QChartView *s1);

private:
    QLineSeries series;
    QVector<QString> time;
    QVector<double> data;
    QList<QPointF> dataPoints;
    void setLabelX();
};
#endif // CHART_DRAW_H
