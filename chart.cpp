#include "chart.h"

Chart::Chart(QObject *parent) : QObject(parent)
{
    gridNumX=10;
    gridNumY=10;
    minValueX=0;
    maxValueX=100;
    minValueY=0;
    maxValueY=20;
    chartMode=Temperature;
    markerX=1;
    markerY=0;
    dataSize=100;
}

void Chart::drawLinearGrid(QPainter &painter, QRect geometry)
{
    gx=geometry.x()+MX;
    gy=geometry.y()+MY;
    gw=geometry.width()-(2*MX);
    gh=geometry.height()-(2*MY);

    dx=gw/static_cast<double>(gridNumX);
    dy=gh/static_cast<double>(gridNumY);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(backgroundColor);
    painter.setPen(pen);
    painter.setBrush(backgroundColor);
    painter.drawRect(geometry);

    // -----  frame ------------
    pen.setStyle(Qt::SolidLine);
    pen.setColor(gridColor);
    pen.setWidth(2);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.drawRect(gx, gy, gw, gh);
    // ----- grid ------------
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    painter.setPen(pen);
    for(int px=1; px<gridNumX; px++)
        painter.drawLine(QLineF(gx+(px*dx), gy, gx+(px*dx), gy+gh));
    for(int py=1; py<gridNumY; py++)
        painter.drawLine(QLineF(gx, gy+(py*dy), gx+gw, gy+(py*dy)));
    // ------ desc ----------
    QFont font;
    font.setPointSize(8);
    painter.setFont(font);
    pen.setColor(textColor);
    painter.setPen(pen);
    dvx=maxValueX-minValueX;
    dvy=maxValueY-minValueY;
    for(int px=0; px<=gridNumX; px++)
        painter.drawText(QPointF(gx-(font.pointSize()/4)+px*dx, gy+gh+(font.pointSize()*2)), QString().sprintf("%d",static_cast<int>(minValueX+(dvx*px)/gridNumX)));
    for(int py=0; py<=gridNumY; py++)
        painter.drawText(QPointF(gx-(font.pointSize()*4), gy+(font.pointSize()/2)+py*dy), QString().sprintf("%4.1f",(maxValueY-(dvy*py)/gridNumY)));

}
void Chart::drawLinearData(QPainter &painter, QVector<double> &data)
{
    dx=gw/static_cast<double>(dataSize-1);
    dy=gh/(maxValueY-minValueY);
    gmy=gy+(gh/2);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(plotColor);
    pen.setWidth(2);
    painter.setPen(pen);

    for(int i=1; i<dataSize; i++)
        painter.drawLine(QLineF(gx+(i-1)*dx, gy+(data[i-1]*gh), gx+i*dx, gy+(data[i]*gh)));
}
