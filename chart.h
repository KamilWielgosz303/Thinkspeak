#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QPainter>
#include <math.h>
#include <vector>

enum ChartMode {
    Temperature,
    Humidity,
    Pressure
};

class Chart : public QObject
{
    Q_OBJECT
public:
    explicit Chart(QObject *parent = nullptr);
    void drawLinearGrid(QPainter &painter, QRect geometry);
    void drawLinearData(QPainter &painter, QVector<double> &data);
    int gridNumX=10, gridNumY=10;
    int minValueX=0, maxValueX=100;
    int minValueY=-100, maxValueY=100;
    int chartMode=0;
    double markerX=1, markerY=0;
    int dataSize;

    QColor backgroundColor=Qt::black;
    QColor gridColor=Qt::gray;
    QColor textColor=Qt::white;
    QColor plotColor=Qt::cyan;
    QColor markersColorA=Qt::red;
    QColor markersColorB=Qt::yellow;

private:
    double dx, dy, dvx, dvy, dmkx, dmky;
    int gx, gy, gw, gh, gmy;
};

#endif // CHART_H
