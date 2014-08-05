#ifndef TOOLBOXWINDOW_H
#define TOOLBOXWINDOW_H

#include <QDialog>
#include "appmanager.h"


class QGridLayout;
class QLabel;
class QLineEdit;
class ToolboxToolBar;
class ResourceTreeWidget;

class ToolboxWidget : public QDialog
{
    Q_OBJECT
public:
    ToolboxWidget(QWidget *parent = 0);
public slots:
    void slotImportFile();
    void slotImportFolder();
    void slotRefreshResource();
    void slotDeleteItemFromResource();
private:
    void createLayout();
    void createConnect();
signals:
    void signalSelectItemType(QString type);
    void sigItemType(int index);
private slots:
    void slotSetFindLineEditVisible(bool);
private:
    QGridLayout		*mGridLayout;
    QLabel          *mTitle;
    ToolboxToolBar  *mToolBar;
    QLineEdit       *mFindLineEdit;
    ResourceTreeWidget *mResTreeWidget;
};

#endif // TOOLBOXWINDOW_H
