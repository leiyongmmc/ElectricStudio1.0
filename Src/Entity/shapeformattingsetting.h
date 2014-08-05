#ifndef SHAPEFORMATTINGSETTING_H
#define SHAPEFORMATTINGSETTING_H

#include <QObject>
#include "entity_global.h"

#include <QColor>

class ENTITYSHARED_EXPORT ShapeFormattingSetting : public QObject
{
    Q_OBJECT
public:
    ShapeFormattingSetting(QObject *parent = 0);
    ShapeFormattingSetting(const ShapeFormattingSetting &other,QObject *parent = 0);

    QColor  mLineColor;
    int     mLineWidth;
    Qt::PenStyle    mLinePenPattern;
    QColor  mFillColor;

};

#endif // SHAPEFORMATTINGSETTING_H
