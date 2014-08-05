#include "krotateitem.h"
#include <QDebug>

KRotateItem::KRotateItem(qreal len, QGraphicsItem *parent) :
    QGraphicsEllipseItem(0,0,len,len,parent),
    mWsize(len)
{
    setAcceptHoverEvents(true);
    setVisible(false);
    mColor = QColor(Qt::green);
    this->setBrush(QBrush(mColor));
}
void KRotateItem::locateInHost()
{
    QPointF cpos = this->parentItem()->boundingRect().center();
    qreal cHeight = this->parentItem()->boundingRect().height();
    QPointF ncpos = QPointF(cpos.x()-mWsize/2,cpos.y()-cHeight/2-40);
    setPos(ncpos);
}

void KRotateItem::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    QCursor cur;
    QPixmap pix(":/loop_12x12.png");
    cur = QCursor(pix);
    setCursor(cur);
    QGraphicsItem::hoverEnterEvent(event);
}
void KRotateItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}
void KRotateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMousePressEvent(event);
}

void KRotateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMouseMoveEvent(event);
}

void KRotateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMouseReleaseEvent(event);
}
