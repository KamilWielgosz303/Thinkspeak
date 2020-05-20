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
    QString getActualTime();

signals:
    void sendSignal(QChartView *s1);

private:
    QLineSeries series;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    QVector<QString> time;
    QString actualTime;
    QVector<double> data;
    QVector<QString> tempTime;
    QList<QPointF> dataPoints;
    double minY;
    double maxY;
    void setAxisX();
    void setAxisY();
    void findMinMax();
};
#endif // CHART_DRAW_H
