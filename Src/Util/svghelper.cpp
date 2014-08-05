#include "svghelper.h"
#include <QtCore/QRegExp>
#include <QStringList>
#include <QPointF>
#include <QRect>
#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QRegion>
#include <QPolygon>
QPointF strToPoint(QStringList &coord){

	QPointF p = QPointF(coord[0].toDouble(), coord[1].toDouble());

	coord.pop_front();
	coord.pop_front();
	return p;

}

QPointF strToPointH(QStringList &coord, int y){
	QPointF p = QPointF(coord[0].toDouble(), y);

	coord.pop_front();
	return p;
}
QPointF strToPointV(QStringList &coord, int x){
	QPointF p = QPointF(x, coord[0].toDouble());

	coord.pop_front();
	return p;
}


QList<QPointF> strToPoints(QStringList &coord, int count){

	QList<QPointF> res;
	for (int i = 0; i < count; i++)
	{
		res.append(QPointF(coord[0].toDouble(), coord[1].toDouble()));
		coord.pop_front();
		coord.pop_front();
	}

	return res;
}

#define PI 3.1415926

void ellipseTransform(QPointF p1, QPointF p2, qreal rx, qreal ry, int largeFlag, int sweepFlag, int angel,
						qreal* startAngle, qreal *sweepLength, QRectF *rect){
	qreal r1 = (p1.x() - p2.x()) / (2.f * rx);
	qreal r2 = (p2.y() - p1.y()) / (2.f * ry);

	qreal tmp = atan(r1 / r2);
	qreal a1s[2] = { tmp, -tmp };
	
	tmp = asin(sqrt(r1*r1 + r2*r2));
	qreal a2s[2] = { tmp, -tmp };
	qreal x, y, t1, t2;

	qreal rrmin = rx*rx;
	qreal rrmax = ry*ry;
	if (rrmin > rrmax){
		tmp = rrmin;
		rrmin = rrmax;
		rrmax = tmp;
	}
	for (int i = 0; i < 2;i++)
	{
		qreal a1 = a1s[i];
		bool isBreak = false;
		for (int j = 0; j < 2; j++)
		{
			qreal a2 = a2s[j];
			t1 = a1 + a2;
			t2 = a1 - a2;
			x = p1.x() - rx*cos(t1);
			y = p1.y() - ry*sin(t1);

			qreal check1 = (p1.x() - x)*(p1.x() - x) / (rx*rx) + (p1.y() - y)*(p1.y() - y) / (ry*ry);
			qreal check2 = (p2.x() - x)*(p2.x() - x) / (rx*rx) + (p2.y() - y)*(p2.y() - y) / (ry*ry);
			
			if ( fabs(check1-1) < 1.e-6 && fabs(check2-1) < 1.e-6)
			{
				isBreak = true;
				break;
			}
		
		}
		if (isBreak)	break;
	}

	QVector3D edge1(x - p1.x(), y - p1.y(),0);
	QVector3D edge2(p2.x() - x, p2.y() - y,0);

	QVector3D cross = QVector3D::crossProduct(edge1,edge2);
	

	bool isCw = cross.z() > 0;
	if (isCw != (largeFlag == sweepFlag))
	{
		QPointF centerOfp1p2 = (p1 + p2) / 2.f;
		x = centerOfp1p2.x() * 2 - x;
		y = centerOfp1p2.y() * 2 - y;

		/*x = x0 + a * cos(t)
		y = y0 + b * sin(t)*/

		
	}


	*rect = QRect(x - rx, y - ry, rx * 2, ry * 2);

	t1 = atan2((p1.y() - y) / ry, (p1.x() - x) / rx);
	t2 = atan2((p2.y() - y) / ry, (p2.x() - x) / rx);

	*startAngle = t1 * 180 / PI;
	*startAngle = -*startAngle;
	*sweepLength = t2 * 180 / PI;
	*sweepLength = -*sweepLength;
	*sweepLength -= *startAngle;

	if ((largeFlag && fabs(*sweepLength) < 180) || (!largeFlag && fabs(*sweepLength) > 180))
	{
		if (*sweepLength < 0)
			*sweepLength = -360 - *sweepLength;
		else
			*sweepLength = 360 - *sweepLength;
	}

	if ((!sweepFlag && *sweepLength <0) || (sweepFlag && *sweepLength >0))
	{
		*sweepLength = -*sweepLength;
	}

	/*if (!isCw)
	{
		*sweepLength = fabs(*sweepLength);
	}*/
	
}

void ellipseTransform(qreal startAngle, qreal sweepLength, const QRectF &rect,
			QPointF *p2, qreal *rx, qreal *ry, int *largeFlag, int *sweepFlag, int *angel ){
	
	*rx = rect.width()  / 2.;
	*ry = rect.height() / 2.;
	*largeFlag = fabs(sweepLength) > 180 ;
	*sweepFlag = sweepLength < 0;
	*angel = 0;
	
	qreal endArc   = -(startAngle+sweepLength) / 180.*PI;

	QPointF center = rect.center();
	*p2 = QPointF(center.x() + *rx*cos(endArc), center.y() + *ry*sin(endArc));

}

QVector<QPointF> vectorFrom2Points(QPointF p1, QPointF p2, int pad, int penWidth){

	QPointF v = p2 - p1;
	//unit
	QVector2D unit(v);
	v = unit.normalized().toPointF();
	v += v*(penWidth / 2. + pad);

	qreal angle = 3.1415926 / 2;
	qreal x1 = cos(angle)*v.x() - sin(angle)*v.y();
	qreal y1 = cos(angle)*v.y() + sin(angle)*v.x();
	QPointF vccw90 = QPointF(x1, y1);


	QVector<QPointF> vector;
	vector.append(p1 - v + vccw90);
	vector.append(p2 + v + vccw90);
	vector.append(p2 + v - vccw90);
	vector.append(p1 - v - vccw90);
	return vector;
}

QRegion regionFrom2Points(QPointF p1, QPointF p2,int pad, int penWidth){
	QVector<QPointF> v = vectorFrom2Points(p1, p2, pad, penWidth);

	QVector<QPoint> vector;
	for each (const QPointF p in v)
	{
		vector.append(p.toPoint());
	}

	return QRegion(QPolygon(vector));
}
