#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QFile>
#include "svgnode.h"

#include "appmanager.h"

class GraphicsScene;

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent=0);
    ~GraphicsView();
    // get scene
    GraphicsScene* getScene();
    // open svg file
    void openFile(QFile *file);
    void setViewSize(QSize);
public slots:
    void slotSetSceneScale(QString);
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mouseMoveEvent ( QMouseEvent*e) ;
    void mousePressEvent(QMouseEvent*e);
    void mouseReleaseEvent(QMouseEvent*e);
//    void wheelEvent(QWheelEvent* event);
private:
    GraphicsScene *mScene;
};

#endif // GRAPHICSVIEW_H
