#ifndef POINTITEMCONTAINER_H
#define POINTITEMCONTAINER_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include "svgpointitem.h"

enum PointItemMode
{
    PointItemMode_DRAW,
    PointItemMode_EDIT
};

class PointItemContainerDelegate;
class PointItemContainer : public QGraphicsObject
{
    Q_OBJECT
public:
	PointItemContainer(QGraphicsObject *parent = 0);

	virtual QRectF boundingRect() const;

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void setDelegate(PointItemContainerDelegate *delegate){
		this->m_delegate = delegate;
	}

	PointItemContainerDelegate *delegate() {
		return m_delegate; 
	}

    SvgPointItem* getLastItem();

    void pointsToItems();

    bool containsPoint(QPointF point);

   

    QPointF mMousePos;

    void setPointItemMode(PointItemMode mode);

    PointItemMode getPointItemMode();

    void showPointItems(bool visible);

    bool isPointItemHaveSelected();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
	void addNewItem(QPointF point);

	PointItemContainerDelegate *m_delegate;

    QList<SvgPointItem*> mPointData;

    qreal m_r;

    PointItemMode mMode;

    int getPointItemIndex(SvgPointItem* item);


public slots:
    void itemPosChanged(int index,SvgPointItem* item);

    void slotMouseMove(QGraphicsSceneMouseEvent *event,SvgPointItem* item);

    void slotMouseRelease(QGraphicsSceneMouseEvent *event,SvgPointItem* item);

};

#endif // POINTITEMCONTAINER_H
