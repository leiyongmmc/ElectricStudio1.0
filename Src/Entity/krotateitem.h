#ifndef KROTATEITEM_H
#define KROTATEITEM_H
#include "entity_global.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QObject>
#include <QPainter>
#include <QColor>

class ENTITYSHARED_EXPORT KRotateItem  : public QObject,public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    KRotateItem(qreal len,QGraphicsItem *parent);
    void locateInHost();
private:
    QPointF mPos;
    qreal mWsize;
    QColor mColor;
    QPointF mLastPoint;
protected:
    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ) ;
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ) ;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void sigMousePressEvent(QGraphicsSceneMouseEvent *event);
    void sigMouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void sigMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // KROTATEITEM_H
