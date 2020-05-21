#include "chart.h"

using namespace std;

Chart::Chart()
{
    QPen pen(QRgb(0xfdb157));
    pen.setWidth(5);
    series.setPen(pen);
    chart = new QChart();
    tempTime.append("Start");
    axisY = new QValueAxis();
    axisY->setLabelFormat("%.1f");
    axisY->setTickCount(11);

    axisX = new QDateTimeAxis();
    axisX->setFormat("hh:mm");
    axisX->setTickCount(11);

    axisX->setTitleText("Time");
    axisX->setTitleBrush(QBrush(Qt::white));
    axisY->setTitleBrush(QBrush(Qt::white));

    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0xe21e13));
    plotAreaGradient.setColorAt(1.0, QRgb(0x000000));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    chart->setBackgroundBrush(plotAreaGradient);
    chart->setPlotAreaBackgroundVisible(true);

    font.setPixelSize(12);
    axisX->setLabelsFont(font);
    axisY->setLabelsFont(font);

    pen.setColor(QRgb(0xffffff));
    pen.setWidth(3);
    axisX->setLinePen(pen);
    axisY->setLinePen(pen);

    QBrush axisBrush(Qt::white);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    font.setPixelSize(15);
    axisX->setLabelsFont(font);
    axisY->setLabelsFont(font);

    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::white));
}


Chart::~Chart(){
    delete axisY;
    delete axisX;
    delete chart;
}

void Chart::setData(QVector<QString> time, QVector<double> data, QString name){

    this->time = time;
    this->data = data;
    dataPoints.clear();
    chart->removeSeries(&series);
    for(int i = 0; i<data.size();i++){
        QPointF p(i,data[data.size()-1-i]);
        dataPoints.append(p);
    }
    series.clear();
    series.append(dataPoints);
    chart->addSeries(&series);
        axisY->setTitleText(name);
    chart->legend()->hide();
    chart->setTitle(name);
    if(time != tempTime){
        chart->removeAxis(axisX);
        setAxisX();
    }
    chart->removeAxis(axisY);
    setAxisY();

    chart->update();
    tempTime = time;
}


void Chart::setAxisY(){
    pair<double*, double*> minmax = minmax_element(begin(data),end(data));
    axisY->setMax(*minmax.first);
    axisY->setMin(*minmax.second);
    chart->addAxis(axisY, Qt::AlignLeft);
}

void Chart::setAxisX(){
    for(int j=0;j<time.size();j++){
        QDateTime test(QDateTime::fromString(time[time.size()-1-j],"yyyy-MM-ddThh:mm:ssZ"));
        test = test.addSecs(7200);
        if(j == 0)
            axisX->setMin(test);
            actualTime = test.toString("yyyy-MM-ddThh:mm:ssZ");
        if(j == 99)
            axisX->setMax(test);
    }
    chart->addAxis(axisX,Qt::AlignBottom);
}

QString Chart::getActualTime(){
    return actualTime;
}
