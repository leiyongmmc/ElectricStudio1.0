#include "svgpointitem.h"
#include <QDebug>

SvgPointItem::SvgPointItem(QGraphicsObject *parent) :
    mPos(0,0),
    mRadius(3),
    QGraphicsObject(parent)
{
    init();
}

SvgPointItem::SvgPointItem(qreal x, qreal y, qreal r, QGraphicsObject *parent) :
    mPos(x,y),
    mRadius(r),
    QGraphicsObject(parent)
{
    init();
}
SvgPointItem::SvgPointItem(QPointF pos, qreal r, QGraphicsObject *parent) :
    mPos(pos),
    mRadius(r),
    QGraphicsObject(parent)
{
    init();
}

void SvgPointItem::init()
{
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemIsSelectable |
             QGraphicsItem::ItemIsFocusable );
    setVisible(true);

    mLineWidth = 1;
}
void SvgPointItem::setFlagEnable(bool enable)
{
    if(enable)
    {
        setFlags(QGraphicsItem::ItemIsMovable |
                 QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable );
    }
    else
    {
        setFlag(QGraphicsItem::ItemIsMovable,false);
        setFlag(QGraphicsItem::ItemIsSelectable,false);
        setFlag(QGraphicsItem::ItemIsFocusable,false);
    }
}

void SvgPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    if(option->state & QStyle::State_Selected)
    {

    }
    else
    {

    }
    painter->setBrush(QBrush(mFillColor));
    painter->setPen(QPen(mLineColor,mLineWidth));

    painter->drawEllipse(mPos,mRadius,mRadius);

}
QRectF SvgPointItem::boundingRect() const
{
    return QRectF(mPos.x()-mRadius*2,mPos.y()-mRadius*2,mRadius*4,mRadius*4);
}
QPainterPath SvgPointItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
void SvgPointItem::setItemPos(QPointF pos)
{
    this->mPos = pos;
}

void SvgPointItem::setRadius(qreal r)
{
    this->mRadius = r;
}
void SvgPointItem::setFillColor(QColor color)
{
    this->mFillColor = color;
}
void SvgPointItem::setLineColor(QColor color)
{
    this->mLineColor = color;
}
void SvgPointItem::setLineWidth(qreal w)
{
    this->mLineWidth = w;
}
QColor SvgPointItem::getLineColor()
{
    return this->mLineColor;
}
qreal SvgPointItem::getLIneWidth()
{
    return this->mLineWidth;
}
void SvgPointItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::hoverEnterEvent(event);
}
void SvgPointItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}
void SvgPointItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}
void SvgPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    emit sigMouseMove(event,this);

}
void SvgPointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit sigMouseRelease(event,this);
    QGraphicsItem::mouseReleaseEvent(event);
}
