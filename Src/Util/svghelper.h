#ifndef SVGHELPER_H
#define SVGHELPER_H

#include "util_global.h"
#include <QObject>

UTILSHARED_EXPORT QPointF strToPoint(QStringList &coord);
UTILSHARED_EXPORT QPointF strToPointH(QStringList &coord, int y);
UTILSHARED_EXPORT QPointF strToPointV(QStringList &coord, int x);
UTILSHARED_EXPORT QList<QPointF> strToPoints(QStringList &coord, int count);

UTILSHARED_EXPORT void ellipseTransform(QPointF p1, QPointF p2, qreal rx, qreal ry, int largeFlag, int sweepFlag, int angel, qreal* startAngle, qreal *sweepLength, QRectF *rect);
UTILSHARED_EXPORT void ellipseTransform(qreal startAngle, qreal sweepLength, const QRectF &rect,
	QPointF *p2, qreal *rx, qreal *ry, int *largeFlag, int *sweepFlag, int *angel);

UTILSHARED_EXPORT QVector<QPointF> vectorFrom2Points(QPointF p1, QPointF p2, int pad = 5, int penWidth = 0);
UTILSHARED_EXPORT QRegion regionFrom2Points(QPointF p1, QPointF p2,int pad = 5, int penWidth = 0);
#endif // SVGHELPER_H
