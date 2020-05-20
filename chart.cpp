#include "chart.h"



Chart::Chart()
{
    chart = new QChart();
    tempTime.append("Start");
    axisY = new QValueAxis();
    axisY->setLabelFormat("%.1f");
    axisY->setTickCount(11);

    axisX = new QDateTimeAxis();
    axisX->setFormat("hh:mm");
    axisX->setTickCount(11);
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
    //qDebug()<<data;
    //qDebug()<<time;

    series.clear();
    series.append(dataPoints);
    chart->addSeries(&series);


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
    findMinMax();
    axisY->setMax(maxY);
    axisY->setMin(minY);
    chart->addAxis(axisY, Qt::AlignLeft);

}

void Chart::setAxisX(){
    //QVector<QDateTime> *tempTime = new QVector<QDateTime>;
    //qDebug()<<time;
    for(int j=0;j<time.size();j++){
        QDateTime test(QDateTime::fromString(time[time.size()-1-j],"yyyy-MM-ddThh:mm:ssZ"));
        test = test.addSecs(7200);
        //qDebug()<<test.time();
        //tempTime->append(*test);
        if(j == 0)
            axisX->setMin(test);
            actualTime = test.toString("yyyy-MM-ddThh:mm:ssZ");
        if(j == 99)
            axisX->setMax(test);
    }

//    axisX->setMin(tempTime->at(0));
//    axisX->setMax(tempTime->at(99));
    chart->addAxis(axisX,Qt::AlignBottom);
}

void Chart::findMinMax(){
    maxY = data[0];
    minY = data[0];
    for(int i=1;i<data.size();i++){
        if(data[i] > maxY)
            maxY = data[i];
        if(data[i] < minY)
            minY = data[i];
    }

}

QString Chart::getActualTime(){
    return actualTime;
}

//void Chart::drawTemp(QVector<double> data,QVector<QString> time){ //niepotrzebna metoda na ten moment


    /*//![1]

    //![2]
        // Customize series
        QPen pen(QRgb(0xfdb157));
        pen.setWidth(5);
        series->setPen(pen);

        // Customize chart title
        QFont font;
        font.setPixelSize(18);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::white));
        chart->setTitle("Customchart example");

        // Customize chart background
        QLinearGradient backgroundGradient;
        backgroundGradient.setStart(QPointF(0, 0));
        backgroundGradient.setFinalStop(QPointF(0, 1));
        backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
        backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        chart->setBackgroundBrush(backgroundGradient);

        // Customize plot area background
        QLinearGradient plotAreaGradient;
        plotAreaGradient.setStart(QPointF(0, 1));
        plotAreaGradient.setFinalStop(QPointF(1, 0));
        plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
        plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
        plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        chart->setPlotAreaBackgroundBrush(plotAreaGradient);
        chart->setPlotAreaBackgroundVisible(true);
    //![2]

    //![3]
        QCategoryAxis *axisX = new QCategoryAxis();
        QCategoryAxis *axisY = new QCategoryAxis();

        // Customize axis label font
        QFont labelsFont;
        labelsFont.setPixelSize(12);
        axisX->setLabelsFont(labelsFont);
        axisY->setLabelsFont(labelsFont);

        // Customize axis colors
        QPen axisPen(QRgb(0xd18952));
        axisPen.setWidth(2);
        axisX->setLinePen(axisPen);
        axisY->setLinePen(axisPen);

        // Customize axis label colors
        QBrush axisBrush(Qt::white);
        axisX->setLabelsBrush(axisBrush);
        axisY->setLabelsBrush(axisBrush);

        // Customize grid lines and shades
        axisX->setGridLineVisible(false);
        axisY->setGridLineVisible(false);
        axisY->setShadesPen(Qt::NoPen);
        axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
        axisY->setShadesVisible(true);
    //![3]

    //![4]
        axisX->append("low", 10);
        axisX->append("optimal", 20);
        axisX->append("high", 30);
        axisX->setRange(0, 30);

        axisY->append("slow", 10);
        axisY->append("med", 20);
        axisY->append("fast", 30);
        axisY->setRange(0, 30);

        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
    //![4]

    //![5]*/
     //   qDebug("Wykonalem sie");
        //emit sendSignal(chartView);                          //Tu jest pierwsza wersja wykresu i przesylamy go do mainwindow








//}

