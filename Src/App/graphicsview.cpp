#include "graphicsview.h"

#include <QDebug>
#include <QApplication>
#include <QScrollBar>
#include <QPointF>
#include <QGraphicsSvgItem>
#include <QWheelEvent>
#include <QContextMenuEvent>
#include <QMenu>

#include "graphicsscene.h"
#include "svgnode.h"
#include "filesvgservice.h"
#include "fileservicefactory.h"
#include "isvgservice.h"
#include "appglobal.h"
#include "Trigger/menumanager.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    mScene = new GraphicsScene();
    this->setScene(mScene);

    // accept drop and drag
    this->setAcceptDrops(true);

    this->setMouseTracking(true);
    this->setAutoFillBackground(true);
    this->setCacheMode(QGraphicsView::CacheNone);
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}


GraphicsView::~GraphicsView()
{
}

GraphicsScene* GraphicsView::getScene()
{
    return mScene;
}

void GraphicsView::openFile(QFile* file)
{
    if(!file)
        return;

    resetTransform();
    mScene->createSceneNodeFromFile(file);
}

void GraphicsView::setViewSize(QSize size)
{
    this->setSceneRect(0,0,size.width(),size.height());
    this->update();
}

void GraphicsView::slotSetSceneScale(QString scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = this->matrix();
    this->resetMatrix();
    this->translate(oldMatrix.dx(), oldMatrix.dy());
    this->scale(newScale, newScale);
}

void GraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = NULL;
    if(MenuManager *mana = MenuManager::sharedMenuManager())
    {
        menu = mana->getGraphicsSceneContextMenu(mana->getGraphicsSceneContextMenuType());
        if(menu)
        {
            menu->exec(QPoint(QCursor::pos()));
        }
    }

    QGraphicsView::contextMenuEvent(event);
}


void GraphicsView:: dragMoveEvent(QDragMoveEvent *event)
{
//    qDebug()<<"drag move event in view";
    QGraphicsView::dragMoveEvent(event);
}


void GraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
//    qDebug()<<"drag enter event in view";
    // active
    this->activateWindow();
    this->setFocus();
    // Generate a scene event.
    QGraphicsSceneDragDropEvent sceneEvent(QEvent::GraphicsSceneDragEnter);
    // Send it to the scene.
    QApplication::sendEvent(mScene, &sceneEvent);
    // Accept the originating event if the scene accepted the scene event.
    if (sceneEvent.isAccepted())
    {
        event->setAccepted(true);
        event->setDropAction(sceneEvent.dropAction());
    }

    QGraphicsView::dragEnterEvent(event);
}

void GraphicsView::dropEvent(QDropEvent *event)
{
//    qDebug()<<"drop event in view";
    QGraphicsView::dropEvent(event);
}

void GraphicsView::mouseMoveEvent ( QMouseEvent * e )
{
//    qDebug()<<"mouse move in view";
    QGraphicsView::mouseMoveEvent(e);
}

void GraphicsView::mousePressEvent ( QMouseEvent * e )
{
//    qDebug()<<"mouse press in view";
    QGraphicsView::mousePressEvent(e);
}

void GraphicsView::mouseReleaseEvent ( QMouseEvent * e )
{
//    qDebug()<<"mouse release in view";
    QGraphicsView::mouseReleaseEvent(e);
}

//void GraphicsView::wheelEvent(QWheelEvent *event)
//{
//    // Scale the view / do the zoom
//    double scaleFactor = 1.15;

//    if(event->delta() > 0)
//    {
//        // Zoom in
//        this->scale(scaleFactor, scaleFactor);
//    }
//    else
//    {
//        // Zooming out
//        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
//    }
//}
