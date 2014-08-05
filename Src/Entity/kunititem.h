#ifndef KUNITITEM_H
#define KUNITITEM_H
#include "entity_global.h"
#include "kresizefocus.h"
#include "krotateitem.h"

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QFocusEvent>
#include <QList>
#include <QPointF>
#include <QGraphicsObject>
#include <QGraphicsSceneDragDropEvent>
#include <QUndoStack>
#include <QUndoCommand>

class ENTITYSHARED_EXPORT KUnitItem : public QGraphicsObject
{
    Q_OBJECT
public:
    enum MouseMode
    {
        MouseMode_NONE,
        MouseMode_MOVE,
        MouseMode_RESIZE,
        MouseMode_ROTATE,
        MouseMode_DRAW
    };
    enum { Type = UserType + 100 };

    KUnitItem(QGraphicsObject *parent = 0);

    KUnitItem(qreal w,qreal h,qreal m, qreal r, QGraphicsObject *parent = 0);

    ~KUnitItem();

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

    void setZoomInPercent(float percent);
    void setZoomOutPercent(float percent);
    void setAngle(qreal angle);

    void setAngle(QPointF pos,qreal angle);

	QPointF getCurCenterPos();

    QPointF getMovedCenterPosToOrig();

    QRectF m_frame;

    qreal m_rotationAngle;

    const QRectF& frame() const{
        return m_frame;
    }

    virtual void onResize(QRectF rect);

    virtual void onMoving();

    virtual void onRotate();

    virtual void onMoved();

    void updateChildItem();

    void setFlagsEnable(bool enable);
public slots:
    void slotFocusMousePress(QGraphicsSceneMouseEvent *event,KResizeFocus* curfocus);
    void slotMouseMove(QGraphicsSceneMouseEvent *event);
    void slotMouseRelease(QGraphicsSceneMouseEvent *event);

    void slotRotateMousePress(QGraphicsSceneMouseEvent *event);
 protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

    void showResizeFocus(bool visible);

    void showRotateItem(bool visible);

	void createResizeFocus();

    void createRotateItem();

    QPointF getOppositePos(QPointF curPos, KResizeFocus::PosInHost inHost, qreal angle = 0);

    QPointF getResizeItemPos(KResizeFocus::PosInHost inHost);

    QPointF getResizeItemoppositePos(KResizeFocus::PosInHost inHost);

    void setFocusAngle(qreal angle);

    void setMouseMode(MouseMode mode);

private:
    void init();

    void initConnect();

public:
    qreal width;
    qreal height;
    qreal margin;

    MouseMode myMode;

    QList<KResizeFocus*> resizeFocus;

    KResizeFocus *curResizeFocus;
    QPointF lastPoint;
    QPointF oppositePos;
    QPointF mLastRotatePoint;
    QGraphicsRectItem *dashRect;
    KRotateItem* mCurRotateItem;
};

#endif // KUNITITEM_H
