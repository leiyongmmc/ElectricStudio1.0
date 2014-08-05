#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "svgnode.h"
#include "appmanager.h"

#include "svgNodeElementImpl/svgpolylineelement.h"

#include "textformattingsetting.h"
#include "shapeformattingsetting.h"

class KUnitItem;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = 0);
	~GraphicsScene();
    // opened file
    void setOpenedFileName(const QString &fileName);
    QString getOpenedFileName() const;
    QString getOpenedFileTagName() const;
    // set scene mode
    void setSceneMode(SceneMode mode);
    // get scene item count
    int getSceneChildNodeCnt() const;
    // drop item cnt
    int getDropIntoSceneItemCnt();
    // scene node
    void setSceneNode(SvgNode *svg);
	// create default prop
	void createDefaultProp(SvgNode *svg);
    SvgNode *getSceneNode();
    // is scene empty only
    bool isOnlySceneNode();
    // clear scene
    void clearScene();
    // set drop item file path
    void setDropItemFilePath(QString);
    // open file and create scene node
    void createSceneNodeFromFile(QFile* file);
    // save current scene node
    void saveSceneNode(QFile *file);
    void saveSceneNode(QString filename);
    void saveSceneNode();
    // draw scene background
    virtual void drawBackground(QPainter * painter, const QRectF & rect );
    // draw foreground
    virtual void drawForeground(QPainter *painter, const QRectF &rect);
public slots:
    void slotSetSceneMode(SceneMode mode);
    void slotSetDropItemFilePath(QString path);
    // group
    void slotGroupItems();
    void slotUngroupItems();
    // align
    void slotSetSelectedItemsAlignLeft();
    void slotSetSelectedItemsAlignCenter();
    void slotSetSelectedItemsAlignRight();
    void slotSetSelectedItemsAlignTop();
    void slotSetSelectedItemsAlignMiddle();
    void slotSetSelectedItemsAlignBottom();
    // distrubute
    void slotDistributeHorizontal();
    void slotDistributeVertical();
    // edit
    void slotCut();
    void slotCopy();
    void slotPaste();
    void slotSelectAll();
    void slotUnSelectAll();
    void slotDelete();
    // grid
    void slotSetGridVisible(bool);
    void slotSetSnapToGrid(bool);
    // zoom
    void slotSetItemZoomIn(float);
    void slotSetItemZoomOut(float);
    // rotate
    void slotSetItemRotate(int);
    // text formatting
    void slotSetItemTextFormatting(TextFormattingSetting setting);
    // shape formatting
    void slotSetItemShapeFormatting(ShapeFormattingSetting setting);
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
signals:
    void sigSelectItemRectF(QRectF);
    void sigIsOnlySceneNode(bool);
    void sigDropItemCnt(int cnt);
    void sigSelectedItemCnt(int);
	void sigSelectedTextItem(bool);
	void sigTextItemSetting(TextFormattingSetting setting);
	void sigShapItemSetting(ShapeFormattingSetting setting);
    void sigMousePos(QPointF pos);
private slots:
    void slotUpdateSignals();
private:
    void selectedItemsFromRect(const QRectF &rect);
     QList<QGraphicsItem *> selectedItemsWithoutSceneItem();
private:
    // current opened file name
    QString mOpenedFileName;
    // was drop item into scene only change one time
    bool mIsDropItem;
    // scene is empty
    bool mIsOnlySceneNode;
    // current drop item file path
    QString mDropItemFilePath;
    // drop item cnt
    int mdropIntoSceneItemCnt;
    // current scene mode for operator select-polygon or draw connect line
    SceneMode mSceneMode;
    // scene node
    SvgNode *mSceneNode;
    QPointF mSelectStartPos;
    QPointF mSelectEndPos;
    QGraphicsRectItem *mSelectRectItem;
    QList<QGraphicsItem*> mCopyCutItems;
    // connector
    SvgPolylineElement *mActivePolylineItem;
};

#endif // GRAPHICSSCENE_H
