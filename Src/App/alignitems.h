#ifndef ALIGNITEMS_H
#define ALIGNITEMS_H

#include <QObject>
#include <QGraphicsItem>

class  AlignItems : public QObject
{
    Q_OBJECT
public:
    explicit AlignItems(QObject *parent = 0);

    static qreal left(QGraphicsItem *item);
    static qreal right(QGraphicsItem *item);
    static qreal top(QGraphicsItem *item);
    static qreal bottom(QGraphicsItem *item);
    static qreal centerX(QGraphicsItem *item);
    static qreal centerY(QGraphicsItem *item);
    static QPointF center(QGraphicsItem *item);

    static void descItemsWithCenterX(QList<QGraphicsItem*> items);
    static void descItemsWithCenterY(QList<QGraphicsItem*> items);

    static void alignLeft(QList<QGraphicsItem*> items);
    static void alignCenter(QList<QGraphicsItem*> items);
    static void alignRight(QList<QGraphicsItem*> items);
    static void alignTop(QList<QGraphicsItem*> items);
    static void alignMiddle(QList<QGraphicsItem*> items);
    static void alignBottom(QList<QGraphicsItem*> items);

    static void distributeH(QList<QGraphicsItem*> items);
    static void distributeV(QList<QGraphicsItem*> items);
};

#endif // ALIGNITEMS_H
