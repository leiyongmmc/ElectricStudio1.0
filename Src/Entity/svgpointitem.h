#ifndef SVGPOINTITEM_H
#define SVGPOINTITEM_H

#include "entity_global.h"
#include <QGraphicsObject>
#include <QGraphicsItem>
#include <QColor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class ENTITYSHARED_EXPORT SvgPointItem : public QGraphicsObject
{
    Q_OBJECT
public:
    SvgPointItem(QGraphicsObject* parent = 0);

    SvgPointItem(qreal x, qreal y, qreal r = 3, QGraphicsObject* parent = 0);

    SvgPointItem(QPointF pos, qreal r, QGraphicsObject* parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;

    QPointF mPos;
    void setItemPos(QPointF pos);
    void setRadius(qreal r);
    void setLineWidth(qreal w);
    qreal getLIneWidth();
    void setFillColor(QColor color);
    void setLineColor(QColor color);
    QColor getLineColor();

    void setFlagEnable(bool enable);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private:

    qreal mRadius;
    QColor mFillColor;
    QColor mLineColor;
    qreal mLineWidth;
    void init();
signals:
    void sigMouseMove(QGraphicsSceneMouseEvent *event,SvgPointItem* item);
    void sigMouseRelease(QGraphicsSceneMouseEvent *event,SvgPointItem* item);

};

#endif // SVGPOINTITEM_H
