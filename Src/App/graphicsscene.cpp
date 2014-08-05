#include "graphicsscene.h"
#include <QFile>
#include <QFileInfo>

#include <QLinkedList>
#include <QGraphicsItemGroup>
#include <QDropEvent>
#include <QGraphicsSceneDragDropEvent>

#include <QPainter>
#include <QPoint>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include "FileInfo/fileservice.h"
#include "kunititem.h"
#include "gridsetting.h"
#include "svgnode.h"
#include "graphprimitiveprop.h"
#include "appglobal.h"
#include "isvgservice.h"
#include "Trigger/menumanager.h"
#include "appcommand.h"
#include "alignitems.h"
#include "svgNodeElementImpl/svgtextelement.h"

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    mOpenedFileName = QString::null;
    mIsDropItem       = false;
    mDropItemFilePath = QString::null;
    mdropIntoSceneItemCnt      = 0;
    mIsOnlySceneNode        = true;
    mSceneMode      = SceneMode_Select;
    mSceneNode      = NULL;
    mSelectStartPos = QPointF(0.0,0.0);
    mSelectEndPos   = QPointF(0.0,0.0);
    mSelectRectItem = NULL;
    mCopyCutItems.clear();
    mActivePolylineItem = NULL;

    // create scene node
    this->clearScene();
}

GraphicsScene::~GraphicsScene()
{
    delete mSceneNode;
    mSceneNode = NULL;
}

void GraphicsScene::setOpenedFileName(const QString &fileName)
{
    mOpenedFileName = fileName;
}

QString GraphicsScene::getOpenedFileName() const
{
    return mOpenedFileName;
}

QString GraphicsScene::getOpenedFileTagName() const
{
    QFileInfo file(mOpenedFileName);
    return FileService::sharedFileService()->vaildFile(file.fileName()) == true ? file.fileName() : QObject::tr("Unname");
}

void GraphicsScene::setSceneMode(SceneMode mode)
{
    this->mSceneMode = mode;
}

int GraphicsScene::getSceneChildNodeCnt() const
{
    if(mSceneNode)
    {
        return mSceneNode->childNodes().count();
    }

    return 0;
}

void GraphicsScene::setSceneNode(SvgNode *svg)
{
    this->clear();
    mSceneNode = svg;
    mSceneNode->setPos(0,0);
    this->addItem(mSceneNode);
}

void GraphicsScene::createDefaultProp(SvgNode *svg)
{
	if (!svg)
		return;
	
	const QLinkedList<GraphPrimitiveProp>& props = svg->props();
	
	QLinkedList<GraphPrimitiveProp>::const_iterator begin = props.cbegin();
	QLinkedList<GraphPrimitiveProp>::const_iterator end = props.cend();
	for (QLinkedList<GraphPrimitiveProp>::const_iterator itr = begin; itr != end; itr++)
	{
		if ((*itr).type() == GraphPrimitiveProp::DEVICETYPE)
		{
			return;
		}
	}

	// if not existed add default props
	const IDeviceTypeService &ser = AppGlobal::instance().serviceFactory().createDeviceTypeService();
	QList<QSharedPointer<DeviceType>> list = ser.List();
}

SvgNode* GraphicsScene::getSceneNode()
{
    return mSceneNode;
}

bool GraphicsScene::isOnlySceneNode()
{
    bool bRet = true;
    if(mSceneNode && this->items(this->itemsBoundingRect()).count())
    {
        bRet = false;
    }

    return bRet;
}

void GraphicsScene::clearScene()
{
    mdropIntoSceneItemCnt = 0;
    mIsOnlySceneNode = true;
    mOpenedFileName = QString::null;
    this->setSceneNode(AppGlobal::instance().serviceFactory().createSvgService().create());
	this->createDefaultProp(mSceneNode);
    this->slotUpdateSignals();
}

void GraphicsScene::setDropItemFilePath(QString str)
{
    mDropItemFilePath = str;
}

int GraphicsScene::getDropIntoSceneItemCnt()
{
    return mdropIntoSceneItemCnt;
}


void GraphicsScene::createSceneNodeFromFile(QFile *file)
{
    if(!file)
        return;

    mOpenedFileName = file->fileName();

    const ISvgService &ser = AppGlobal::instance().serviceFactory().createSvgService();
    SvgNode *svg = ser.Get(mOpenedFileName);
    if(svg)
    {
        svg->setFlag(QGraphicsItem::ItemIsMovable,false);
        svg->setFlag(QGraphicsItem::ItemIsSelectable,false);
        svg->setFlag(QGraphicsItem::ItemIsFocusable,false);
        this->setSceneNode(svg);
        mIsOnlySceneNode = false;
        this->slotUpdateSignals();
    }

    file->close();

    delete file;
    file = NULL;
}

void GraphicsScene::saveSceneNode(QFile *file)
{
    if(!file)
        return;

    QString filename = file->fileName();
    this->saveSceneNode(filename);

    file->close();
    delete file;
    file = NULL;
}

void GraphicsScene::saveSceneNode(QString filename)
{
    if(mSceneNode && FileService::sharedFileService()->vaildFile(filename))
    {
        if(!filename.endsWith(".svg"))
        {
            filename += ".svg";
        }

        const ISvgService &ser = AppGlobal::instance().serviceFactory().createSvgService();
        ser.SaveOrUpdate(mSceneNode, filename);
    }
}

void GraphicsScene::saveSceneNode()
{
    this->saveSceneNode(mOpenedFileName);
}

void GraphicsScene::drawBackground(QPainter * painter, const QRectF & rect )
{
    QRect screenRect = AppManager::getAppManager()->getScreenRect();
    GridSetting::getGridSetting()->drawGridWithIntersection(painter,screenRect);
}

void GraphicsScene::drawForeground(QPainter *painter, const QRectF &rect)
{
    QRect screenRect = AppManager::getAppManager()->getScreenRect();
    GridSetting::getGridSetting()->drawCoordinate(Qt::Horizontal,painter,screenRect);
    GridSetting::getGridSetting()->drawCoordinate(Qt::Vertical,painter,screenRect);
}

void GraphicsScene::slotSetSceneMode(SceneMode mode)
{
    this->setSceneMode(mode);
}

void GraphicsScene::slotSetDropItemFilePath(QString path)
{
    mDropItemFilePath = path;
}

void GraphicsScene::slotGroupItems()
{}

void GraphicsScene::slotUngroupItems()
{}

void GraphicsScene::slotSetSelectedItemsAlignLeft()
{
    AlignItems::alignLeft(this->selectedItems());
}

void GraphicsScene::slotSetSelectedItemsAlignCenter()
{
    AlignItems::alignCenter(this->selectedItems());
}

void GraphicsScene::slotSetSelectedItemsAlignRight()
{
    AlignItems::alignRight(this->selectedItems());
}

void GraphicsScene::slotSetSelectedItemsAlignTop()
{
    AlignItems::alignTop(this->selectedItems());
}

void GraphicsScene::slotSetSelectedItemsAlignMiddle()
{
    AlignItems::alignMiddle(this->selectedItems());
}

void GraphicsScene::slotSetSelectedItemsAlignBottom()
{
    AlignItems::alignBottom(this->selectedItems());
}

void GraphicsScene::slotDistributeHorizontal()
{
    AlignItems::distributeH(this->selectedItems());
}

void GraphicsScene::slotDistributeVertical()
{
    AlignItems::distributeV(this->selectedItems());
}

void GraphicsScene::slotCut()
{
    foreach (QGraphicsItem *item, mCopyCutItems)
    {
        delete item;
    }

    mCopyCutItems.clear();

    foreach (QGraphicsItem *item, this->selectedItems())
    {
		SvgNode* node = dynamic_cast<SvgNode*>(item);
        SvgNode* newNode = node->clone();
        newNode->setPos(node->pos().x(),node->pos().y());
        node->setSelected(false);
		mCopyCutItems.append(dynamic_cast<QGraphicsItem*>(newNode));

        this->removeItem(item);
    }
}

void GraphicsScene::slotPaste()
{
    this->slotUnSelectAll();

    foreach (QGraphicsItem *item, mCopyCutItems)
    {
		SvgNode* node = dynamic_cast<SvgNode*>(item);
        SvgNode* newnode = node->clone();
		QGraphicsItem *newItem = dynamic_cast<QGraphicsItem*>(newnode);
        //this->addItem(newItem);
		newnode->setParentItem(mSceneNode);
		newnode->setParentNode(mSceneNode);
		mSceneNode->add(newnode);
        newItem->setSelected(true);

        //qDebug()<<item->pos().x()<<item->pos().y();
        newItem->setPos(item->pos().x() + 10, item->pos().y() + 10);
        // update item pos
        item->setPos(item->pos().x() + 10, item->pos().y() + 10);
        item->setSelected(false);
    }
}
void GraphicsScene::slotCopy()
{
    foreach (QGraphicsItem *item, mCopyCutItems)
    {
        delete item;
    }

	//memory leak solve
	//qDeleteAll(mCopyCutItems);
    mCopyCutItems.clear();

    foreach (QGraphicsItem *item, this->selectedItems())
    {
		 SvgNode* node = dynamic_cast<SvgNode*>(item); 
         SvgNode* newNode = node->clone();
         newNode->setPos(node->pos().x(),node->pos().y());
         node->setSelected(false);
		 mCopyCutItems.append(dynamic_cast<QGraphicsItem*>(newNode));
    }
}

void GraphicsScene::slotSelectAll()
{
    if(!mSceneNode)
        return;

    foreach(QGraphicsItem *item, this->items())
    {
		if (item == dynamic_cast<QGraphicsItem*>(mSceneNode))
        {
            continue;
        }
        else
        {
		    item->setSelected(true);
        }
    }
}

void GraphicsScene::slotUnSelectAll()
{
    if(!mSceneNode)
        return;

    foreach(QGraphicsItem *item, this->items())
    {
		if (item == dynamic_cast<QGraphicsItem*>(mSceneNode))
        {
            continue;
        }
        else
        {
            item->setSelected(false);
        }
    }
}

void GraphicsScene::slotDelete()
{
    if(!mSceneNode)
        return;

	AppCommand::getAppCommand()->getUndoStack()->push(new DeleteCommand(this, this->selectedItems()));

    if(this->items(this->itemsBoundingRect()).count())
    {
        mIsOnlySceneNode = false;
    }
    else
    {
        mIsOnlySceneNode = true;
        mdropIntoSceneItemCnt = 0;
    }
}

void GraphicsScene::slotSetGridVisible(bool visible)
{
}

void GraphicsScene::slotSetSnapToGrid(bool snap)
{

}

void GraphicsScene::slotSetItemZoomIn(float in)
{
    foreach (QGraphicsItem *item, this->selectedItems())
    {
        SvgNode* node = dynamic_cast<SvgNode*>(item);
        node->setZoomInPercent(in);
    }
}

void GraphicsScene::slotSetItemZoomOut(float out)
{
    foreach (QGraphicsItem *item, this->selectedItems())
    {
        SvgNode* node = dynamic_cast<SvgNode*>(item);
        node->setZoomOutPercent(out);
    }
}

void GraphicsScene::slotSetItemRotate(int index)
{
    qreal angle = 0;
    if(index == 0)
    {
        angle = 45;
    }
    else if(index == 1)
    {
        angle = -45;
    }
    else if(index == 2)
    {
        angle = 180;
    }
    foreach (QGraphicsItem *item, this->selectedItems())
    {
		SvgNode* node = dynamic_cast<SvgNode*>(item);
        node->setAngle(angle);
        node->onRotate();
    }
}

void GraphicsScene::slotSetItemTextFormatting(TextFormattingSetting setting)
{
    foreach(QGraphicsItem *item, this->selectedItems())
    {
		SvgNode *node = dynamic_cast<SvgNode*>(item);
        if(node && node->svgType() == SVG_TEXT)
        {
			dynamic_cast<SvgTextElement*>(node)->updateTextFormattingSetting(setting);
        }
    }

	this->update();
}

void GraphicsScene::slotSetItemShapeFormatting(ShapeFormattingSetting setting)
{
    foreach(QGraphicsItem *item, this->selectedItems())
    {
		SvgNode *node = dynamic_cast<SvgNode*>(item);
        if(node)
        {
            node->updateShapeFormattingSetting(setting);
        }
    }

	this->update();
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    if(event->button() == Qt::LeftButton)
    {
		QList<QGraphicsItem*> items =  this->items(QRectF(event->scenePos().x(), event->scenePos().y(), 10, 10));
		emit sigSelectedItemCnt(items.count());
		if (!items.isEmpty())
		{
			for each (QGraphicsItem *item in items)
			{
				SvgTextElement *ele = dynamic_cast<SvgTextElement*>(item);
				if (ele)
				{
						emit sigSelectedTextItem(true);
						emit sigTextItemSetting(ele->textFormattingSetting());
					
				}
				else
				{
					emit sigSelectedTextItem(false);
				}
			}
			
		}
		else
		{
			emit sigSelectedTextItem(false);
		}

        if(mSceneMode == SceneMode_Select)
        {
            mSelectStartPos = event->scenePos();

            if(mActivePolylineItem)
            {
                mActivePolylineItem->setEnableFlag(true);
                mActivePolylineItem = NULL;
            }
        }
        else if(mSceneMode ==SceneMode_Connector)
        {
            if(mActivePolylineItem == NULL)
            {
                const ISvgService &svgService = AppGlobal::instance().serviceFactory().createSvgService();
                SvgNode* newItem = svgService.create(SvgType::SVG_POLYLINE,mSceneNode);

                if (newItem)
                {
                    newItem->setPos(pos);
                    mdropIntoSceneItemCnt++;
                }
                mActivePolylineItem = qobject_cast<SvgPolylineElement*>(newItem);
                mActivePolylineItem->setEnableFlag(false);
            }

            QPointF res;
            bool flag = mSceneNode->tiePointCheck(pos,&res);
            if(flag)
            {
                mActivePolylineItem->appendPoint(res);
            }
            else
            {
                mActivePolylineItem->appendPoint(pos);
            }
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if(mActivePolylineItem)
        {
            mActivePolylineItem->setEnableFlag(true);
            mActivePolylineItem = NULL;
        }
        else
        {
            QList<QGraphicsItem *> items = this->selectedItems();
            if(items.count() == 0)
            {
                MenuManager::sharedMenuManager()->setGraphicsSceneContextMenuType(MenuManager::SceneContextMenu);
            }
            else if(items.count() == 1)
            {
                MenuManager::sharedMenuManager()->setGraphicsSceneContextMenuType(MenuManager::ItemContextMenu);
            }
            else
            {
                MenuManager::sharedMenuManager()->setGraphicsSceneContextMenuType(MenuManager::ItemGroupContextMenu);
            }
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // mouse clicked and move
    QPointF pos = event->scenePos();
    if(mSceneMode == SceneMode_Select)
    {
        if(this->selectedItems().count())
        {
            this->slotUpdateSignals();
        }
        else
        {
            if(mSelectRectItem)
            {
                this->removeItem(mSelectRectItem);
                delete mSelectRectItem;
                mSelectRectItem= NULL;
            }

            if(mSelectStartPos.x() != 0 && mSelectStartPos.y() != 0)
            {
                mSelectEndPos = event->scenePos();
                mSelectRectItem = new QGraphicsRectItem(mSelectStartPos.x(),mSelectStartPos.y()
                                                        , mSelectEndPos.x() - mSelectStartPos.x()
                                                        , mSelectEndPos.y() - mSelectStartPos.y());

                mSelectRectItem->setPen(QPen(QBrush(QColor(49,176,224)),1,Qt::SolidLine));
                mSelectRectItem->setBrush(QBrush(QColor(228,244,251,100)));

                this->addItem(mSelectRectItem);
            }
        }
    }
    else if(mSceneMode == SceneMode_Connector)
    {
        QPointF res;
        bool flag = mSceneNode->tiePointCheck(pos,&res);
        if(mActivePolylineItem)
        {
            if(flag)
            {
                mActivePolylineItem->setMouseMovePos(res);
            }
            else
            {
                mActivePolylineItem->setMouseMovePos(pos);
            }
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(mSceneMode == SceneMode_Select)
    {
        if(mSelectRectItem)
        {
            // selected item from rect
            this->selectedItemsFromRect(mSelectRectItem->rect());
            // remove select rect item
            this->removeItem(mSelectRectItem);
            delete mSelectRectItem;
            mSelectRectItem= NULL;
        }

        mSelectStartPos = QPointF(0.0,0.0);
        mSelectEndPos = QPointF(0.0,0.0);
    }
    else if(mSceneMode == SceneMode_Connector)
    {
        if(mActivePolylineItem)
        {
            if(mActivePolylineItem->twoEndpointsLinked())
            {
                mActivePolylineItem->setEnableFlag(true);
                mActivePolylineItem = NULL;
            }
        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();

    mIsDropItem = true;
}

void GraphicsScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();
}

void GraphicsScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();

    mIsDropItem = false;
}


void GraphicsScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    event->accept();

    if(mIsDropItem)
    {
        QPointF pos = event->scenePos();

        const ISvgService &ser = AppGlobal::instance().serviceFactory().createSvgService();
        SvgNode *newItem = ser.Get(mDropItemFilePath.replace("png", "svg"),mSceneNode);
		if (newItem)
        {
			if (SvgTextElement *textNode = dynamic_cast<SvgTextElement*>(newItem))
			{
				if (textNode->svgType() == SVG_TEXT)
				{
					emit sigSelectedTextItem(true);
				}
			}
			else
			{
				emit sigSelectedTextItem(false);
			}

            this->slotUnSelectAll();
            newItem->setSelected(true);
            newItem->setPos(pos);

            mdropIntoSceneItemCnt++;
            mIsOnlySceneNode = false;
            mIsDropItem = false;
		}
    }

    this->slotUpdateSignals();
}
void GraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(mActivePolylineItem)
        {
            mActivePolylineItem->setEnableFlag(true);
            mActivePolylineItem = NULL;
        }
    }
	if (event->key() == Qt::Key_Delete)
	{
		this->slotDelete();
	}
}

void GraphicsScene::slotUpdateSignals()
{
    emit sigIsOnlySceneNode(mIsOnlySceneNode);

    int cnt = this->selectedItemsWithoutSceneItem().count();
    if(cnt == 0)
    {
        emit QRectF();
        emit sigSelectedItemCnt(cnt);
    }
    else if(cnt == 1)
    {
        QGraphicsItem *item = this->selectedItemsWithoutSceneItem().at(0);
        emit sigSelectItemRectF(QRectF(item->pos().x(),
                                       item->pos().y(),
                                       item->boundingRect().width(),
                                       item->boundingRect().height()));
        emit sigSelectedItemCnt(cnt);

		SvgNode *node = dynamic_cast<SvgNode*>(item);
		if (node)
		{
			emit sigShapItemSetting(node->shapeFormattingSetting());
		}
		
    }
    else if(cnt > 1)
    {
        for(int i = 0; i < cnt; i++)
        {

        }
        emit sigSelectedItemCnt(cnt);
    }
}

void GraphicsScene::selectedItemsFromRect(const QRectF &rect)
{
    QList<QGraphicsItem*> items =  this->items(rect);
    foreach(QGraphicsItem *item, items)
    {
        if(item)
        {
			if (item == dynamic_cast<QGraphicsItem*>(mSceneNode))
			{
				continue;
			}

            item->setSelected(true);
        }
    }

	if (!items.isEmpty())
	{
		for each (QGraphicsItem *item in items)
		{
			SvgTextElement *ele = dynamic_cast<SvgTextElement*>(item);
			if (ele)
			{
				emit sigSelectedTextItem(true);
				emit sigTextItemSetting(ele->textFormattingSetting());

			}
			else
			{
				emit sigSelectedTextItem(false);
			}
		}

	}
	else
	{
		emit sigSelectedTextItem(false);
	}

    this->slotUpdateSignals();
}

QList<QGraphicsItem*> GraphicsScene::selectedItemsWithoutSceneItem()
{
    QList<QGraphicsItem*> items = this->selectedItems();

    QList<QGraphicsItem*> newItems;
    newItems.clear();

    for(int i = 0; i < items.count(); i++)
    {
		if (items.at(i) == dynamic_cast<QGraphicsItem*>(mSceneNode))
        {
            continue;
        }

        newItems.append(items.at(i));
    }

    return newItems;
}
