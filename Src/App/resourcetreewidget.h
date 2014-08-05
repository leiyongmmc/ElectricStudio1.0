#ifndef RESOURCETREEWIDGET_H
#define RESOURCETREEWIDGET_H

#include <QTreeWidget>
#include <QMouseEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QIcon>
#include <QMap>

class QTreeWidgetItem;
class SvgItem;

class ResourceTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    enum ItemType
    {
        RootItem,
        FolderItem,
        FileItem
    };
    ResourceTreeWidget(QWidget *parent = 0);
    void importFile(QString filename);
    void importFolder(QString foldername);
    void refreshRes();
    void deleteRes();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
signals:
    void signalSelectItemType(QString );
    void sigItemType(int index);
private:
    void init();
    void createTreeView();
    void createConnect();
private slots:
    void slotUpdateState(QModelIndex index);
    void slotUpdateState(QTreeWidgetItem *);
private:
    QIcon  mFolderIcon;
    QPoint mClickStartPos;
    QMap<QTreeWidgetItem*,QTreeWidgetItem*> mGroupMap;
    QMap<QString,SvgItem*> mItemMaps;
    QTreeWidgetItem *mRootItem;
};

#endif // RESOURCETREEWIDGET_H
