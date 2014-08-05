#include "kunititem.h"
#include "util.h"

#include <QDebug>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QTransform>
#include <QDebug>
#include <math.h>

#include "itemcommand.h"

KUnitItem::KUnitItem(QGraphicsObject *parent)
    :width(100),height(100),margin(6),m_rotationAngle(0), QGraphicsObject(parent)
{
    init();
}
KUnitItem::KUnitItem(qreal w,qreal h,qreal m, qreal r,QGraphicsObject *parent)
    :width(w),height(h),margin(m),m_rotationAngle(r),QGraphicsObject(parent)
{
    init();
}
void KUnitItem::init()
{
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

    m_frame = QRectF(0, 0, 0, 0);

    createResizeFocus();
    createRotateItem();
}

KUnitItem::~KUnitItem()
{

}

QRectF KUnitItem::boundingRect() const
{
    return m_frame;
}

void KUnitItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(painter);

    if(option->state & QStyle::State_Selected)
    {
        if(myMode != MouseMode_DRAW)
        {
            showResizeFocus(true);
            showRotateItem(true);
        }

    }
    else
    {
        if(myMode != MouseMode_DRAW)
        {
            showResizeFocus(false);
            showRotateItem(false);
        }

    }
}

void KUnitItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}
void KUnitItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    onMoving();
    QGraphicsItem::mouseMoveEvent(event);
}
void KUnitItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    onMoved();
    QGraphicsItem::mouseReleaseEvent(event);
}
void KUnitItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    onMoving();
    QGraphicsItem::dropEvent(event);
}

void KUnitItem::showResizeFocus(bool visible)
{
    for(int i = 0; i < resizeFocus.count(); i++)
    {
        resizeFocus.at(i)->locateInHost();
        resizeFocus.at(i)->setVisible(visible);
    }
}
void KUnitItem::updateChildItem()
{
    for(int i = 0; i < resizeFocus.count(); i++)
    {
        resizeFocus.at(i)->locateInHost();
    }
    mCurRotateItem->locateInHost();
}

void KUnitItem::showRotateItem(bool visible)
{
    mCurRotateItem->locateInHost();
    mCurRotateItem->setVisible(visible);
}
void KUnitItem::createRotateItem()
{
    mCurRotateItem = new KRotateItem(10,this);

    connect(mCurRotateItem,SIGNAL(sigMousePressEvent(QGraphicsSceneMouseEvent*)),this,SLOT(slotRotateMousePress(QGraphicsSceneMouseEvent*)));
    connect(mCurRotateItem,SIGNAL(sigMouseMoveEvent(QGraphicsSceneMouseEvent*)),this,SLOT(slotMouseMove(QGraphicsSceneMouseEvent*)));
    connect(mCurRotateItem,SIGNAL(sigMouseReleaseEvent(QGraphicsSceneMouseEvent*)),this,SLOT(slotMouseRelease(QGraphicsSceneMouseEvent*)));
}
void KUnitItem::createResizeFocus()
{
    KResizeFocus *north_middle = new KResizeFocus(margin,KResizeFocus::NORTH_MIDDLE,this);
    resizeFocus.append(north_middle);
    KResizeFocus *north_east = new KResizeFocus(margin,KResizeFocus::NORTH_EAST,this);
    resizeFocus.append(north_east);
    KResizeFocus *north_west = new KResizeFocus(margin,KResizeFocus::NORTH_WEST,this);
    resizeFocus.append(north_west);
    KResizeFocus *south_middle = new KResizeFocus(margin,KResizeFocus::SOUTH_MIDDLE,this);
    resizeFocus.append(south_middle);
    KResizeFocus *south_east = new KResizeFocus(margin,KResizeFocus::SOUTH_EAST,this);
    resizeFocus.append(south_east);
    KResizeFocus *south_west = new KResizeFocus(margin,KResizeFocus::SOUTH_WEST,this);
    resizeFocus.append(south_west);
    KResizeFocus *east_middle = new KResizeFocus(margin,KResizeFocus::EAST_MIDDLE,this);
    resizeFocus.append(east_middle);
    KResizeFocus *west_middle = new KResizeFocus(margin,KResizeFocus::WEST_MIDDLE,this);
    resizeFocus.append(west_middle);

    initConnect();
}

void KUnitItem::setAngle(QPointF pos,qreal angle)
{
    m_rotationAngle += angle;
	if (m_rotationAngle >= 360)
	{
		m_rotationAngle = m_rotationAngle - 360;
	}
	else if (m_rotationAngle < 0)
	{
		m_rotationAngle = 360 + m_rotationAngle;
	}

	this->setTransform(QTransform().translate(pos.x(), pos.y()).rotate(angle).translate(-pos.x(), -pos.y()), true);

    setFocusAngle(m_rotationAngle);
}

void KUnitItem::setZoomInPercent(float percent)
{
    //qDebug()<<"zoom in percent"<<percent;
    QRectF newFrame;
    newFrame.setX(m_frame.x());
    newFrame.setY(m_frame.y());
    newFrame.setWidth(m_frame.width() * (1 + percent));
    newFrame.setHeight(m_frame.height() * (1 + percent));

    ItemCommand::getItemCommand()->getUndoStack()->push(new ResizeCommand(this,m_frame,newFrame));
}

void KUnitItem::setZoomOutPercent(float percent)
{
    //qDebug()<<"zoom out percent"<<percent;
    QRectF newFrame;
    newFrame.setX(m_frame.x());
    newFrame.setY(m_frame.y());
    newFrame.setWidth(m_frame.width() * (1 - percent));
    newFrame.setHeight(m_frame.height() * (1 - percent));

    ItemCommand::getItemCommand()->getUndoStack()->push(new ResizeCommand(this,m_frame,newFrame));
}

void KUnitItem::setAngle(qreal angle)
{
    // use command replace the following code
//  QPointF p = m_frame.center();
//	this->setAngle(p, angle);
    // angle command
    ItemCommand::getItemCommand()->getUndoStack()->push(new AngleCommand(this,angle));
}
QPointF KUnitItem::getCurCenterPos()
{
    QPointF pos = this->boundingRect().center();
    QPointF out = this->mapToScene(pos);
    return out;
}
QPointF KUnitItem::getMovedCenterPosToOrig()
{
    QPointF pos = this->boundingRect().center();
    QPointF out = this->mapToScene(-pos);
    return out;
}
void KUnitItem::onResize(QRectF rect)
{

}
void KUnitItem::onRotate()
{

}

void KUnitItem::onMoving()
{

}
void KUnitItem::onMoved()
{
    qDebug()<<"dragLeave"<<this->pos().x()<<this->pos().y();
}

void KUnitItem::slotFocusMousePress(QGraphicsSceneMouseEvent *event,KResizeFocus* curfocus)
{
    curResizeFocus = curfocus;

    if(curResizeFocus)
    {
        myMode = MouseMode_RESIZE;
        dashRect = new QGraphicsRectItem();
        QPen pen(Qt::DashLine);
        pen.setWidthF(1);
        dashRect->setPen(pen);
        dashRect->setParentItem(this);
        dashRect->setRect(m_frame);

        lastPoint = getResizeItemPos(curResizeFocus->getInHost());
        oppositePos = getResizeItemoppositePos(curResizeFocus->getInHost());
    }
    else
    {
        myMode = MouseMode_MOVE;
        QGraphicsItem::mousePressEvent(event);
    }
}
void KUnitItem::slotMouseMove(QGraphicsSceneMouseEvent *event)
{
    if (myMode == MouseMode_RESIZE)
    {
        QPointF curPoint(event->scenePos());
        QPointF curPointItem = this->mapFromScene(curPoint);

        bool flagx = lastPoint.x() > oppositePos.x();
        bool flagx1 = curPointItem.x() > oppositePos.x();
        bool flagy = lastPoint.y() > oppositePos.y();
        bool flagy1 = curPointItem.y() > oppositePos.y();


        qreal dist = 0;

        QRectF rectf;
        rectf.setRect(m_frame.x()
                      , m_frame.y()
                      , m_frame.width()
                      , m_frame.height());


        KResizeFocus::PosInHost pos = curResizeFocus->getInHost();
        if (pos == KResizeFocus::NORTH_MIDDLE)
        {
            QPointF br = dashRect->rect().bottomRight();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                dist = 20;
            }
            rectf.setY(curPointItem.y());
            rectf.setHeight(dist);
        }
        else if(pos == KResizeFocus::SOUTH_MIDDLE)
        {
            QPointF br = dashRect->rect().topRight();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                dist = 20;
            }
            rectf.setHeight(dist);
        }
        else if(pos == KResizeFocus::EAST_MIDDLE)
        {
            QPointF br = dashRect->rect().bottomLeft();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                dist = 20;
            }
            rectf.setWidth(dist);
        }
        else if(pos == KResizeFocus::WEST_MIDDLE)
        {
            QPointF br = dashRect->rect().bottomRight();
            dist = Util::GetPointDistLine(oppositePos,br,curPointItem);

            if (dist < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                dist = 20;
            }
            rectf.setX(curPointItem.x());
            rectf.setWidth(dist);
        }
        else if(pos == KResizeFocus::NORTH_WEST)
        {
            QPointF topRight = dashRect->rect().topRight();
            QPointF bottomLeft = dashRect->rect().bottomLeft();

            qreal distx = Util::GetPointDistLine(oppositePos,topRight,curPointItem);
            qreal disty = Util::GetPointDistLine(oppositePos,bottomLeft,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }

            rectf.setTopLeft(curPointItem);
        }
        else if(pos == KResizeFocus::NORTH_EAST)
        {
            QPointF topLeft = dashRect->rect().topLeft();
            QPointF bottomRight = dashRect->rect().bottomRight();

            qreal distx = Util::GetPointDistLine(oppositePos,topLeft,curPointItem);
            qreal disty = Util::GetPointDistLine(oppositePos,bottomRight,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }

            rectf.setTopRight(curPointItem);
        }
        else if(pos == KResizeFocus::SOUTH_EAST)
        {
            QPointF topRight = dashRect->rect().topRight();
            QPointF bottomLeft = dashRect->rect().bottomLeft();

            qreal disty = Util::GetPointDistLine(oppositePos,topRight,curPointItem);
            qreal distx = Util::GetPointDistLine(oppositePos,bottomLeft,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }

            rectf.setBottomRight(curPointItem);
        }
        else if(pos == KResizeFocus::SOUTH_WEST)
        {
            QPointF topLeft = dashRect->rect().topLeft();
            QPointF bottomRight = dashRect->rect().bottomRight();

            qreal disty = Util::GetPointDistLine(oppositePos,topLeft,curPointItem);
            qreal distx = Util::GetPointDistLine(oppositePos,bottomRight,curPointItem);

            if (distx < 20 || flagx != flagx1)
            {
                if (flagx)
                {
                    curPointItem.setX(oppositePos.x() + 20);
                }
                else
                {
                    curPointItem.setX(oppositePos.x() - 20);
                }
                distx = 20;
            }
            if (disty < 20 || flagy != flagy1)
            {
                if (flagy)
                {
                    curPointItem.setY(oppositePos.y() + 20);
                }
                else
                {
                    curPointItem.setY(oppositePos.y() - 20);
                }
                disty = 20;
            }
            rectf.setBottomLeft(curPointItem);
        }

        dashRect->setRect(rectf);
    }
    else if(myMode == MouseMode_ROTATE)
    {
        QPointF curPos = event->scenePos();
        QPointF cpos = this->mapToScene(frame().center());
//        qDebug()<<cpos;
		qreal angleLast = Util::ComputeAngle(mLastRotatePoint, cpos);
		qreal angleCur = Util::ComputeAngle(curPos, cpos);
        qreal angle = angleCur - angleLast;

        setAngle(angle);
        mLastRotatePoint = curPos;
        onRotate();
    }
    else if(myMode == MouseMode_MOVE)
    {
        onMoving();
    }
    else
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}
void KUnitItem::slotMouseRelease(QGraphicsSceneMouseEvent *event)
{
    if(myMode == MouseMode_RESIZE)
    {
        ItemCommand::getItemCommand()->getUndoStack()->push(new ResizeCommand(this,m_frame,dashRect->rect()));

        delete dashRect;
        myMode = MouseMode_NONE;
    }
    else if(myMode == MouseMode_ROTATE)
    {
        myMode = MouseMode_NONE;
    }
    else
        QGraphicsItem::mouseReleaseEvent(event);
}
void KUnitItem::slotRotateMousePress(QGraphicsSceneMouseEvent *event)
{
    myMode = MouseMode_ROTATE;
    mLastRotatePoint.setX(event->scenePos().x());
    mLastRotatePoint.setY(event->scenePos().y());
}
void KUnitItem::initConnect()
{
    foreach(KResizeFocus* focus,resizeFocus)
    {
        if(focus)
        {
            connect(focus,SIGNAL(sigMouseMoveEvent(QGraphicsSceneMouseEvent*)),this,SLOT(slotMouseMove(QGraphicsSceneMouseEvent*)));
            connect(focus,SIGNAL(sigMousePressEvent(QGraphicsSceneMouseEvent*,KResizeFocus*)),this,SLOT(slotFocusMousePress(QGraphicsSceneMouseEvent*,KResizeFocus*)));
            connect(focus,SIGNAL(sigMouseReleaseEvent(QGraphicsSceneMouseEvent*)),this,SLOT(slotMouseRelease(QGraphicsSceneMouseEvent*)));
        }
    }
}
QPointF KUnitItem::getResizeItemPos(KResizeFocus::PosInHost inHost)
{
    qreal x1 = m_frame.x();
    qreal y1 = m_frame.y();
    qreal x = 0;
    qreal y = 0;
    if(inHost == KResizeFocus::NORTH_MIDDLE)
    {
        x = x1 + m_frame.width()/2 ;
        y = y1;
    }
    else if(inHost ==  KResizeFocus::SOUTH_MIDDLE)
    {
        x = x1 + m_frame.width()/2 ;
        y = y1 + m_frame.height();
    }
    else if(inHost ==  KResizeFocus::WEST_MIDDLE)
    {
        x = x1;
        y = y1 + m_frame.height()/2;
    }
    else if(inHost ==  KResizeFocus::EAST_MIDDLE)
    {
        x = x1 + m_frame.width() ;
        y = y1 + m_frame.height()/2;
    }
    else if(inHost == KResizeFocus::NORTH_WEST)
    {
        QPointF topLeft = m_frame.topLeft();
        x = topLeft.x();
        y = topLeft.y();
    }
    else if(inHost == KResizeFocus::SOUTH_EAST)
    {
        QPointF bottomRight = m_frame.bottomRight();
        x = bottomRight.x();
        y = bottomRight.y();
    }
    else if(inHost == KResizeFocus::NORTH_EAST)
    {
        QPointF topRight = m_frame.topRight();
        x = topRight.x();
        y = topRight.y();
    }
    else if(inHost == KResizeFocus::SOUTH_WEST)
    {
        QPointF bottomLeft = m_frame.bottomLeft();
        x = bottomLeft.x();
        y = bottomLeft.y();
    }
    return QPointF(x,y);
}
QPointF KUnitItem::getResizeItemoppositePos(KResizeFocus::PosInHost inHost)
{
    qreal x1 = m_frame.x();
    qreal y1 = m_frame.y();
    qreal x = 0;
    qreal y = 0;
    if(inHost == KResizeFocus::NORTH_MIDDLE)
    {
        x = x1 + m_frame.width()/2 ;
        y = y1 + m_frame.height();
    }
    else if(inHost ==  KResizeFocus::SOUTH_MIDDLE)
    {
        x = x1 + m_frame.width()/2 ;
        y = y1;
    }
    else if(inHost ==  KResizeFocus::WEST_MIDDLE)
    {
        x = x1 + m_frame.width() ;
        y = y1 + m_frame.height()/2;
    }
    else if(inHost ==  KResizeFocus::EAST_MIDDLE)
    {
        x = x1;
        y = y1 + m_frame.height()/2;
    }
    else if(inHost == KResizeFocus::NORTH_WEST)
    {
        QPointF bottomRight = m_frame.bottomRight();
        x = bottomRight.x();
        y = bottomRight.y();
    }
    else if(inHost == KResizeFocus::SOUTH_EAST)
    {
        QPointF topLeft = m_frame.topLeft();
        x = topLeft.x();
        y = topLeft.y();
    }
    else if(inHost == KResizeFocus::NORTH_EAST)
    {
        QPointF bottomLeft = m_frame.bottomLeft();
        x = bottomLeft.x();
        y = bottomLeft.y();
    }
    else if(inHost == KResizeFocus::SOUTH_WEST)
    {
        QPointF topRight = m_frame.topRight();
        x = topRight.x();
        y = topRight.y();
    }
    return QPointF(x,y);
}
QPointF KUnitItem::getOppositePos(QPointF curPos, KResizeFocus::PosInHost inHost,qreal angle)
{
    qreal x1 = curPos.x();
    qreal y1 = curPos.y();
    qreal edge = 0;
//    qreal angle = this->m_rotationAngle;
    qreal x = 0;
    qreal y = 0;
    if(inHost == KResizeFocus::NORTH_MIDDLE)
    {
        edge = frame().height();
        x = x1 - sin(angle*M_PI/180)*edge ;
        y = y1 + cos(angle*M_PI/180)*edge ;
    }
    else if(inHost ==  KResizeFocus::SOUTH_MIDDLE)
    {
        edge = frame().height();
        x = x1 + sin(angle*M_PI/180)*edge ;
        y = y1 - cos(angle*M_PI/180)*edge ;
    }
    else if(inHost ==  KResizeFocus::WEST_MIDDLE)
    {
        edge = frame().width();
        x = x1 + cos(angle*M_PI/180)*edge ;
        y = y1 + sin(angle*M_PI/180)*edge ;
    }
    else if(inHost ==  KResizeFocus::EAST_MIDDLE)
    {
        edge = frame().width();
        x = x1 - cos(angle*M_PI/180)*edge ;
        y = y1 - sin(angle*M_PI/180)*edge ;
    }
    else if(inHost == KResizeFocus::NORTH_WEST)
    {
        QPointF bottomRight = this->mapToScene(frame().bottomRight());
        x = bottomRight.x();
        y = bottomRight.y();
    }
    else if(inHost == KResizeFocus::SOUTH_EAST)
    {
        QPointF topLeft = this->mapToScene(frame().topLeft());
        x = topLeft.x();
        y = topLeft.y();
    }
    else if(inHost == KResizeFocus::NORTH_EAST)
    {
        QPointF bottomLeft = this->mapToScene(frame().bottomLeft());
        x = bottomLeft.x();
        y = bottomLeft.y();
    }
    else if(inHost == KResizeFocus::SOUTH_WEST)
    {
        QPointF topRight = this->mapToScene(frame().topRight());
        x = topRight.x();
        y = topRight.y();
    }
//    qDebug()<<angle<<"cupos"<<x1<<y1<<"oppositepos"<<x<<y;
    return QPointF(x,y);
}
void KUnitItem::setFocusAngle(qreal angle)
{
    foreach (KResizeFocus* focus,resizeFocus) {
        if(focus)
        {
            focus->mParentAngle = angle;
        }
    }
}
void KUnitItem::setMouseMode(MouseMode mode)
{
    myMode = mode;
}
void KUnitItem::setFlagsEnable(bool enable)
{
    if(enable)
    {
        setFlags(QGraphicsItem::ItemIsMovable |
                 QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsFocusable );
        this->setMouseMode(MouseMode_NONE);
    }
    else
    {
//        setFlag(QGraphicsItem::ItemIsMovable,false);
        setFlag(QGraphicsItem::ItemIsSelectable,false);
        setFlag(QGraphicsItem::ItemIsFocusable,false);
        this->setMouseMode(MouseMode_DRAW);
    }
}
