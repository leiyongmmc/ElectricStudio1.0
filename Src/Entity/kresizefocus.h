#ifndef KRESIZEFOCUS_H
#define KRESIZEFOCUS_H
#include "entity_global.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QObject>

class ENTITYSHARED_EXPORT KResizeFocus : public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum PosInHost{NORTH_MIDDLE,NORTH_EAST,EAST_MIDDLE,SOUTH_EAST,SOUTH_MIDDLE,SOUTH_WEST,WEST_MIDDLE,NORTH_WEST};
    enum { Type = UserType + 1 };
    KResizeFocus(PosInHost pos, QGraphicsItem *parent);
    KResizeFocus(qreal len, PosInHost pos, QGraphicsItem *parent);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    int type() const {return Type;}
    void setInHost(PosInHost pos){posInHost = pos;}
    PosInHost getInHost(){return posInHost;}

    void locateInHost();
    qreal mParentAngle;

protected:
    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ) ;
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ) ;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    PosInHost posInHost;
    qreal wsize;
    void setCurCursor(qreal startAngle);
signals:
    void sigMousePressEvent(QGraphicsSceneMouseEvent *event,KResizeFocus* curFocus);
    void sigMouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void sigMouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // KRESIZEFOCUS_H
