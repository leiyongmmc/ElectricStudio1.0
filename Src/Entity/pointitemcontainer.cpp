#include "pointitemcontainer.h"
#include "pointitemcontainerdelegate.h"
#include <QDebug>
PointItemContainer::PointItemContainer(QGraphicsObject *parent) :
    m_r(3),
    QGraphicsObject(parent)
{
    mMousePos = QPointF(0,0);
}
QRectF PointItemContainer::boundingRect() const
{
    //reset frame
    qreal minx = 999999;
    qreal miny = 999999;
    qreal maxx = -999999;
    qreal maxy = -999999;
    foreach( SvgPointItem* p, mPointData) {

        if (minx > p->mPos.x())
            minx = p->mPos.x();
        if (miny > p->mPos.y())
            miny = p->mPos.y();

        if (maxx < p->mPos.x())
            maxx = p->mPos.x();
        if (maxy < p->mPos.y())
            maxy = p->mPos.y();

    }

    minx -= m_r-10;
    miny -= m_r-10;
    maxx += m_r+10;
    maxy += m_r+10;
//    QRectF m_frame = QRectF(minx - 1 / 2.f, miny - 1 / 2.f, (maxx - minx) + 1, (maxy - miny) + 1);
    return QRectF(0,0,0,0);
}

void PointItemContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    SvgPointItem* lastItem = getLastItem();
    if(lastItem && mMode == PointItemMode_DRAW)
    {
        QColor color = lastItem->getLineColor();
        qreal linewidth = lastItem->getLIneWidth();
        painter->setPen(QPen(Qt::red,2,Qt::DashLine,Qt::RoundCap,Qt::RoundJoin));

        painter->drawLine(this->mapToParent(lastItem->mPos),this->mapFromScene(mMousePos));
    }

	QList<QPointF> list = this->m_delegate->actualScenePoints();
	if (list.count() > mPointData.count())
	{
//		if (list.count() == mPointData.count()+1)
//		{
//			this->setPointItemMode(PointItemMode_DRAW);
//		}
		
		for (int i = mPointData.count(); i < list.count()  ; i++)
		{
			addNewItem(list.at(i));
		}
		
	}

    int idx = 0;
    foreach (SvgPointItem *p , mPointData)
    {
        p->setItemPos(this->mapFromScene(list.at(idx++))-p->pos());
    }
}
SvgPointItem* PointItemContainer::getLastItem()
{
    if(mPointData.count()>0)
    {
        int count = mPointData.count();
        SvgPointItem* item = mPointData.at(count-1);
        return item;
    }
    return NULL;
}
void PointItemContainer::pointsToItems()
{
    if(m_delegate)
    {
        QList<QPointF> list = m_delegate->actualScenePoints();
        foreach (QPointF pos, list)
        {
            SvgPointItem* pointItem = new SvgPointItem(this->mapFromScene(pos),m_r,this);
            mPointData.append(pointItem);
        }
    }
}

void PointItemContainer::itemPosChanged(int index,SvgPointItem* item)
{
    /*if(item == NULL || m_delegate == NULL)
        return;

    m_delegate->onPointPosChanged(index, item->mapToScene(pos()));*/
}

void PointItemContainer::addNewItem(QPointF point)
{
    QPointF newpoint = this->mapFromScene(point);
    SvgPointItem* newItem = new SvgPointItem(newpoint,m_r,this);

    newItem->setFlagEnable(false);
    connect(newItem,SIGNAL(sigMouseMove(QGraphicsSceneMouseEvent*,SvgPointItem*)),this,SLOT(slotMouseMove(QGraphicsSceneMouseEvent*,SvgPointItem*)));
    connect(newItem,SIGNAL(sigMouseRelease(QGraphicsSceneMouseEvent*,SvgPointItem*)),this,SLOT(slotMouseRelease(QGraphicsSceneMouseEvent*,SvgPointItem*)));
    mPointData.append(newItem);
    if(mPointData.count() == 1)
    {
        mMousePos = point;
    }
}

bool PointItemContainer::containsPoint(QPointF point)
{
    foreach (SvgPointItem* item, mPointData) {
       if(item)
       {
           if(item->pos() == point)
           {
               return true;
           }
       }
    }
    return false;
}
void PointItemContainer::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
}
void PointItemContainer::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseMoveEvent(event);
}
void PointItemContainer::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
}
void PointItemContainer::setPointItemMode(PointItemMode mode)
{
    this->mMode = mode;
}
PointItemMode PointItemContainer::getPointItemMode()
{
    return this->mMode;
}

void PointItemContainer::slotMouseMove(QGraphicsSceneMouseEvent *event,SvgPointItem* item)
{
    if(mMode == PointItemMode_EDIT)
    {
        if(item)
        {
            int index = getPointItemIndex(item);
            if(index == -1)
                return;
            QPointF pos = event->scenePos();
            int count = mPointData.count();
            if(index == 0 || index == count -1)
            {
                QPointF res;
                if(m_delegate->tiePointCheckDelegate(pos,&res))
                {
                    m_delegate->onPointPosChanged(index,res);
                    this->update(this->boundingRect());
                    return;
                }
            }
            m_delegate->onPointPosChanged(index,pos);
        }
    }
}
void PointItemContainer::slotMouseRelease(QGraphicsSceneMouseEvent *event, SvgPointItem *item)
{
    if(mMode == PointItemMode_EDIT)
    {
        if(item)
        {
            int index = getPointItemIndex(item);
            if(index == -1)
                return;
            QPointF pos = event->scenePos();
            int count = mPointData.count();
            if(index == 0 || index == count -1)
            {

                QPointF res;
                if(m_delegate->tiePointCheckDelegate(pos,&res))
                {
//                    QPointF point = m_delegate->actualScenePoints().at(index);
//                    item->setItemPos(this->mapFromScene(point));
//                    item->setPos(item->mPos+this->mapFromScene(res));
                    m_delegate->onPointPosChanged(index,res);
                    item->setItemPos(this->mapFromScene(res-this->pos()));
                    return;
                }
            }
            m_delegate->onPointPosChanged(index,pos);
        }
    }
}

int PointItemContainer::getPointItemIndex(SvgPointItem* item)
{
    int index = -1;
    if(item == NULL || mPointData.count() == 0)
        return index;
    for(int i=0;i<mPointData.count();i++)
    {
        if(mPointData.at(i) == item)
        {
            index = i;
            break;
        }
    }
    return index;
}
void PointItemContainer::showPointItems(bool visible)
{
    for(int i=0;i<mPointData.count();i++)
    {
        mPointData.at(i)->setFlagEnable(visible);
        mPointData.at(i)->setVisible(visible);
    }
}
bool PointItemContainer::isPointItemHaveSelected()
{
    bool selected = false;
    for(int i=0;i<mPointData.count();i++)
    {
        if(mPointData.at(i)->isSelected())
        {
            selected = true;
            return selected;
        }
    }
    return selected;
}
