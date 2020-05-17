#ifndef CHART_DRAW_H
#define CHART_DRAW_H
#include <QChar>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QObject>

QT_CHARTS_USE_NAMESPACE

class chart_draw : public QObject
{
    Q_OBJECT

public:
    chart_draw();
    void drawTemp(QVector<double> data,QVector<QString> time);

signals:
    void sendSignal(QChartView *s1);
};
#endif // CHART_DRAW_H
