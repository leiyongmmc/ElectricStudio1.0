#include "resourcetreewidget.h"


#include <qdebug.h>
#include <QFile>
#include <QFileInfo>
#include <QTreeWidgetItem>
#include <QContextMenuEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QMenu>

#include "svgitem.h"
#include "resourcelibrary.h"
#include "resourcemanager.h"


#include "Trigger/menumanager.h"

ResourceTreeWidget::ResourceTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    this->setColumnCount(1);
    this->setHeaderHidden(true);
    mFolderIcon = QIcon(":/Folder.png");
    mClickStartPos = QPoint(0,0);


    mGroupMap.clear();
    mItemMaps.clear();

    mRootItem = new QTreeWidgetItem(this);
    mRootItem->setText(0,tr("Resource"));
    mRootItem->setIcon(0,mFolderIcon);
    mRootItem->setSelected(true);
    this->addTopLevelItem(mRootItem);

    mGroupMap.insert(mRootItem,mRootItem);

    this->setAcceptDrops(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->init();
}

void ResourceTreeWidget::importFile(QString filepath)
{
    QFileInfo info(filepath);
    QString filename = info.fileName().left(info.fileName().lastIndexOf("."));

    QTreeWidgetItem *folder = this->currentItem();

    if(folder == mRootItem || folder != mGroupMap.value(folder))
        return;

    // was existed
    for(int i = 0; i < folder->childCount(); i++)
    {
        if(folder->child(i)->text(0) == filename)
        {
            return;
        }
    }

    // add file
    SvgItem *newItem = ResourceManager::getManager()->importFile(folder->text(0),filepath);
    if(newItem)
    {
        // add to tree
        QTreeWidgetItem *file = new QTreeWidgetItem(folder);
        file->setText(0,tr("%1").arg(filename));
        file->setIcon(0,QIcon(filepath));
        mGroupMap.insert(file,folder);
        mItemMaps.insert(file->text(0),newItem);
    }
}

void ResourceTreeWidget::importFolder(QString folderpath)
{
    qDebug()<<folderpath;
    QFileInfo info(folderpath);

    QTreeWidgetItem *root = this->currentItem();

    if(root != mRootItem)
        return;

    // was folder existed
    QTreeWidgetItem *folder = NULL;
    bool bExisted = false;
    for(int i = 0; i < mRootItem->childCount(); i++)
    {
        QTreeWidgetItem* child = mRootItem->child(i);

        if(child && child->text(0) == info.fileName())
        {
            folder = child;
            bExisted = true;
            break;
        }
    }

    ResourceLibrary *lib = ResourceManager::getManager()->importFolder(folderpath);
    if(!lib)
        return;

    if(false == bExisted)
    {
        // add tree item
        folder = new QTreeWidgetItem(mRootItem);
        folder->setText(0,tr("%1").arg(info.fileName()));
        folder->setIcon(0,QIcon(mFolderIcon));
        mRootItem->addChild(folder);
        mGroupMap.insert(folder,folder);
    }

    // insert child item was not existed
    folder->takeChildren();

    QList<SvgItem*>* svgItems = lib->getItems();
    if(svgItems)
    {
        for(int j = 0; j < svgItems->count(); j++)
        {
			if (svgItems->at(j)->getAbsolutePath().endsWith(".svg"))
				continue;

            QTreeWidgetItem *file = new QTreeWidgetItem(folder);
            file->setText(0,tr("%1").arg(svgItems->at(j)->getName()));
            file->setIcon(0,QIcon(svgItems->at(j)->getIcon()));

            mGroupMap.insert(file,folder);
            mItemMaps.insert(file->text(0),svgItems->at(j));
        }
    }

}

void ResourceTreeWidget::refreshRes()
{
    if(!mRootItem)
        return;

    mRootItem->takeChildren();
    mItemMaps.clear();
    mGroupMap.clear();
    mGroupMap.insert(mRootItem,mRootItem);

    ResourceManager::getManager()->refreshAllResources();
    this->createTreeView();
}

void ResourceTreeWidget::deleteRes()
{
    if(QTreeWidgetItem *item = this->currentItem())
    {
        if(item == mRootItem)
            return;

        // folder
        if(item == mGroupMap.value(item))
        {
            ResourceManager::getManager()->removeLib(item->text(0));
        }
        // file
        else
        {
            ResourceManager::getManager()->removeItem(item->parent()->text(0),item->text(0));
        }

        if(!item->isDisabled())
        {
            item->parent()->removeChild(item);
        }
    }
}

void ResourceTreeWidget::init()
{
    this->createTreeView();
    this->createConnect();
}

void ResourceTreeWidget::createTreeView()
{
    if(!mRootItem)
        return;

    QList<ResourceLibrary*>* resLibs = ResourceManager::getManager()->getResLibs();
    if(resLibs)
    {
        for(int i = 0; i < resLibs->count(); i++)
        {
            ResourceLibrary *lib = resLibs->at(i);
            if(lib)
            {
                QTreeWidgetItem *folder = new QTreeWidgetItem(mRootItem);
                folder->setText(0,tr("%1").arg(lib->getName()));
                folder->setIcon(0,QIcon(mFolderIcon));
                mRootItem->addChild(folder);
                mGroupMap.insert(folder,folder);

                QList<SvgItem*>* svgItems = lib->getItems();
                if(svgItems)
                {
                    for(int j = 0; j < svgItems->count(); j++)
                    {
						if (svgItems->at(j)->getAbsolutePath().endsWith(".svg"))
							continue;

                        QTreeWidgetItem *file = new QTreeWidgetItem(folder);
                        file->setText(0,tr("%1").arg(svgItems->at(j)->getName()));
                        file->setIcon(0,QIcon(svgItems->at(j)->getIcon()));

                        mGroupMap.insert(file,folder);
                        mItemMaps.insert(file->text(0),svgItems->at(j));
                    }
                }
            }
        }
    }

    this->expandAll();
}

void ResourceTreeWidget::createConnect()
{
   connect(this,SIGNAL(clicked(QModelIndex)),this,SLOT(slotUpdateState(QModelIndex)));
}

void ResourceTreeWidget::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        mClickStartPos = event->pos();
    }
    else if(event->button() == Qt::RightButton)
    {
        QTreeWidgetItem *posItem = this->itemAt(event->pos());
        if(posItem)
        {
            this->slotUpdateState(posItem);
            QMenu *menu = NULL;
            if(MenuManager *mana = MenuManager::sharedMenuManager())
            {
                menu = mana->m_ResourceContextMenu;
                if(menu)
                {
                    menu->exec(QPoint(QCursor::pos()));
                }
            }
        }
    }

    QTreeWidget::mousePressEvent(event);
}

void ResourceTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        int distance = (event->pos() - mClickStartPos).manhattanLength();
        if (distance >= QApplication::startDragDistance())
        {
            QTreeWidgetItem *item = this->currentItem();
            // not folder item
            if(item && item != mGroupMap.value(item))
            {
                emit signalSelectItemType(mItemMaps.value(item->text(0))->getAbsolutePath());

                QMimeData *mimeData = new QMimeData;
                mimeData->setText(item->text(0));

                QDrag *drag = new QDrag(this);
                drag->setMimeData(mimeData);

//                QPixmap pixmap(QSize(100,60));
//                QPainter p(&pixmap);
//                p.drawRect(QRectF(0,0,100,60));
//                p.fillRect(QRectF(0,0,100,60),QBrush(Qt::lightGray));
//                drag->setPixmap(pixmap);

                if (drag->start(Qt::MoveAction) == Qt::MoveAction)
                {
                    delete item;
                }
            }
        }
    }

    QTreeWidget::mouseMoveEvent(event);
}

void ResourceTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    ResourceTreeWidget *source = (ResourceTreeWidget *)((void*)(event->source()));

    if (source && source == this)
   {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->acceptProposedAction();
    }
}


void ResourceTreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    ResourceTreeWidget *source = (ResourceTreeWidget *)((void*)(event->source()));

    if (source && source == this)
   {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->acceptProposedAction();
    }
}

void ResourceTreeWidget::slotUpdateState(QModelIndex index)
{
    QTreeWidgetItem *item = static_cast<QTreeWidgetItem*>(index.internalPointer());
    if(!item)
        return;

   this->slotUpdateState(item);
}

void ResourceTreeWidget::slotUpdateState(QTreeWidgetItem *item)
{
    if(!item)
        return;

    if(item == mRootItem)
    {
        emit sigItemType((int)RootItem);
    }
    else if(item == mGroupMap.value(item))
    {
        emit sigItemType((int)FolderItem);
    }
    else
    {
        emit sigItemType((int)FileItem);
    }
}
