#include "shapeformattingsetting.h"

ShapeFormattingSetting::ShapeFormattingSetting(QObject *parent) :
    QObject(parent)
{
    mLineColor = Qt::red;
    mLinePenPattern = Qt::SolidLine;
    mLineWidth = 1;
    mFillColor = Qt::white;
}

ShapeFormattingSetting::ShapeFormattingSetting(const ShapeFormattingSetting &other, QObject *parent)
{
    this->mLineColor = other.mLineColor;
    this->mLinePenPattern = other.mLinePenPattern;
    this->mLineWidth = other.mLineWidth;
    this->mFillColor = other.mFillColor;
}
