#ifndef POINTITEMCONTAINERDELEGATE_H
#define POINTITEMCONTAINERDELEGATE_H
#include <QList>
#include <QPointF>
class PointItemContainerDelegate
{
public:
    PointItemContainerDelegate();

	virtual QList<QPointF> actualScenePoints() const = 0;

    virtual void onPointPosChanged(int idx, QPointF newPoint) = 0;

	virtual bool tiePointCheckDelegate(QPointF curr, QPointF *res) = 0;

};

#endif // POINTITEMCONTAINERDELEGATE_H
