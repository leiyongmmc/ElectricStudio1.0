#include "alignitems.h"
#include <QtAlgorithms>
#include <QDebug>
#include "../Entity/svgnode.h"

bool cmpX(QGraphicsItem *a,QGraphicsItem *b)
{
    return (a->pos().x() + a->boundingRect().width() / 2) - (b->pos().x() + b->boundingRect().width() / 2);
}

bool cmpY(QGraphicsItem *a,QGraphicsItem *b)
{
    return (a->pos().y() + a->boundingRect().height() / 2) - (b->pos().y() + b->boundingRect().height() / 2);
}


AlignItems::AlignItems(QObject *parent) :
    QObject(parent)
{
}

qreal AlignItems::left(QGraphicsItem *item)
{
    return item->pos().x();
}

qreal AlignItems::right(QGraphicsItem *item)
{
    return item->pos().x() + item->boundingRect().width();
}

qreal AlignItems::top(QGraphicsItem *item)
{
    return item->pos().y();
}

qreal AlignItems::bottom(QGraphicsItem *item)
{
    return item->pos().y() + item->boundingRect().height();
}

qreal AlignItems::centerX(QGraphicsItem *item)
{
    return item->pos().x() + item->boundingRect().width() / 2;
}

qreal AlignItems::centerY(QGraphicsItem *item)
{
    return item->pos().y() + item->boundingRect().height() / 2;
}

QPointF AlignItems::center(QGraphicsItem *item)
{
    return QPointF(item->pos().x() + item->boundingRect().width() / 2,
                   item->pos().y() + item->boundingRect().height() / 2);
}

void AlignItems::descItemsWithCenterX(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;

    QList<QGraphicsItem*>::iterator begin = items.begin();
    QList<QGraphicsItem*>::iterator end = items.end();

    qSort(begin,end,cmpX);
}

void AlignItems::descItemsWithCenterY(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;

    QList<QGraphicsItem*>::iterator begin = items.begin();
    QList<QGraphicsItem*>::iterator end = items.end();

    qSort(begin,end,cmpY);
}



void AlignItems::alignLeft(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;


	qreal min = 1.e10;
	qreal left, top, right, bottom;
	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			if (left < min)
				min = left;
		}
	}

	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			node->moveBy( min - left,0);
		}
	}
}

void AlignItems::alignCenter(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;

    // horizon
	qreal min = 1.e10;
	qreal left, top, right, bottom;
	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			if ((top + bottom) / 2. < min)
				min = (left + right) / 2.;
		}
	}

	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			node->moveBy( min - (left + right) / 2., 0 );
		}
	}
}


void AlignItems::alignRight(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;

	qreal max = -1.e10;
	qreal left, top, right, bottom;
	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			if (right > max)
				max = right;
		}
	}

	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			node->moveBy(max - right, 0);
		}
	}
}


void AlignItems::alignTop(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;

	qreal min = 1.e10;
	qreal left, top, right, bottom;
	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			if (top < min)
				min = top;
		}
	}

	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			node->moveBy(0, min - top);
		}
	}
    
}

void AlignItems::alignMiddle(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;

	qreal min = 1.e10;
	qreal left, top, right, bottom;
	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			if ((top + bottom) / 2. < min)
				min = (top + bottom) / 2.;
		}
	}

	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			node->moveBy(0, min - (top + bottom) / 2.);
		}
	}
}

void AlignItems::alignBottom(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 2)
        return;

	qreal max = -1.e10;
	qreal left, top, right, bottom;
	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			if (bottom > max)
				max = bottom;
		}
	}

	for each (QGraphicsItem* item in items)
	{
		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			node->boundaryRangeInScene(left, top, right, bottom);
			node->moveBy(0,max - bottom);
		}
	}
}

void AlignItems::distributeH(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 3)
        return;

    descItemsWithCenterX(items);

    qreal minCenterX = centerX(items.at(cnt -1));
    qreal maxCenterX = centerX(items.at(0));

    int offsetX = (maxCenterX - minCenterX) / (cnt-1);

    for(int i = 1 ; i <cnt-1; i++)
    {
        items.at(i)->setPos(centerX(items.at(0)) - items.at(i)->boundingRect().width()/2 - i*offsetX,items.at(i)->pos().y());
    }
}

void AlignItems::distributeV(QList<QGraphicsItem *> items)
{
    int cnt = items.count();
    if(cnt < 3)
        return;

    descItemsWithCenterY(items);

    qreal minCenterY = centerY(items.at(cnt -1));
    qreal maxCenterY = centerY(items.at(0));


    int offsetY = (maxCenterY - minCenterY) / (cnt-1);

    for(int i = 1 ; i <cnt-1; i++)
    {
        items.at(i)->setPos(items.at(i)->pos().x(),centerY(items.at(0)) - items.at(i)->boundingRect().height()/2 - i*offsetY);
    }
}
