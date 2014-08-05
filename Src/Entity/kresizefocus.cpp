#include "kresizefocus.h"

#include <QDebug>
KResizeFocus::KResizeFocus(PosInHost pos, QGraphicsItem *parent)
    : QGraphicsRectItem(0,0,6,6,parent),posInHost(pos),wsize(6)
{
//	setAcceptsHoverEvents(true);
    setAcceptHoverEvents(true);
    setVisible(false);

    locateInHost();
    mParentAngle = 0;
}

KResizeFocus::KResizeFocus(qreal len, PosInHost pos, QGraphicsItem *parent)
    :QGraphicsRectItem(0,0,len,len,parent),posInHost(pos),wsize(len)
{
//	setAcceptsHoverEvents(true);
    setAcceptHoverEvents(true);
    setVisible(false);

    locateInHost();
    mParentAngle = 0;
}

QRectF KResizeFocus::boundingRect() const
{
    return QRectF(-wsize,-wsize,wsize*3,wsize*3);
}
QPainterPath KResizeFocus::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
void KResizeFocus::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
//    setCurCursor();
    switch(posInHost){
        case NORTH_MIDDLE:
//            setCursor(Qt::SizeVerCursor);
            setCurCursor(0);
            break;
        case SOUTH_MIDDLE:
//            setCursor(Qt::SizeVerCursor);
        setCurCursor(180);
            break;
        case EAST_MIDDLE:
//            setCursor(Qt::SizeHorCursor);
            setCurCursor(90);
            break;
        case WEST_MIDDLE:
//            setCursor(Qt::SizeHorCursor);
        setCurCursor(270);
            break;
        case NORTH_WEST:
//            setCursor(Qt::SizeFDiagCursor);
        setCurCursor(315);
            break;
        case SOUTH_EAST:
//            setCursor(Qt::SizeFDiagCursor);
        setCurCursor(135);
            break;
        case NORTH_EAST:
//            setCursor(Qt::SizeBDiagCursor);
        setCurCursor(45);
            break;
        case SOUTH_WEST:
//            setCursor(Qt::SizeBDiagCursor);
        setCurCursor(225);
            break;
        default:
            break;
    }
    QGraphicsRectItem::hoverEnterEvent(event);
}

void KResizeFocus::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    QGraphicsRectItem::hoverLeaveEvent(event);
}

void KResizeFocus::locateInHost()
{
    const QRectF parentRect = this->parentItem()->boundingRect();
    qreal x = 0, y = 0;

    switch(posInHost){
        case NORTH_MIDDLE:
            x = parentRect.x() + parentRect.width() / 2 - wsize/2;
            y = parentRect.y() - wsize;
            break;
        case SOUTH_MIDDLE:
            x = parentRect.x() + parentRect.width() / 2 - wsize/2;
            y = parentRect.y()+parentRect.height() ;
            break;
        case EAST_MIDDLE:
            x = parentRect.x() + parentRect.width() ;
            y = parentRect.y()+parentRect.height() / 2 - wsize/2;
            break;
        case WEST_MIDDLE:
            x = parentRect.x() - wsize;
            y = parentRect.y()+parentRect.height() / 2 - wsize/2 ;
            break;
        case NORTH_WEST:
            x = parentRect.x() - wsize;
            y = parentRect.y() - wsize;
            break;
        case SOUTH_EAST:
            x = parentRect.x() + parentRect.width() ;
            y = parentRect.y()+parentRect.height() ;
            break;
        case NORTH_EAST:
            x = parentRect.x() + parentRect.width() ;
            y = parentRect.y() - wsize;
            break;
        case SOUTH_WEST:
            x = parentRect.x() - wsize ;
            y = parentRect.y()+parentRect.height() ;
            break;
        default:
            break;
    }
    setPos(x,y);
}
void KResizeFocus::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMousePressEvent(event,this);
}

void KResizeFocus::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMouseMoveEvent(event);
}

void KResizeFocus::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMouseReleaseEvent(event);
}
void KResizeFocus::setCurCursor(qreal startAngle)
{
//    qreal angle = this->parentItem()->rotation() + startAngle;
    qreal angle = mParentAngle + startAngle;

    if(angle >360 )
    {
        angle -= 360;
    }
    qreal step = 360/16;
    if(angle>=step*15 || angle<step)
    {
        setCursor(Qt::SizeVerCursor);
    }
    else if(angle>=step && angle<step*3)
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if(angle >= step*3 && angle<step*5)
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if(angle >= step*5 && angle < step*7)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(angle >= step*7 && angle<step*9)
    {
        setCursor(Qt::SizeVerCursor);
    }
    else if(angle >= step*9 && angle<step*11)
    {
        setCursor(Qt::SizeBDiagCursor);
    }
    else if(angle >= step*11 && angle<step*13)
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if(angle >= step*13 && angle<step*15)
    {
        setCursor(Qt::SizeFDiagCursor);
    }
}
