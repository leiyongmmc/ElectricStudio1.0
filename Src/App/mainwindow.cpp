#include "mainwindow.h"

#include <QCloseEvent>
#include <QSplitter>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>
#include <QUndoStack>
#include <QUndoCommand>

#include "appmanager.h"
#include "Trigger/actionmanager.h"
#include "Trigger/editortoolbar.h"
#include "Trigger/toolbarmanager.h"
#include "Trigger/menumanager.h"
#include "Trigger/triggermanager.h"
#include "Trigger/textformattingtoolbar.h"
#include "Trigger/shapeformattingtoolbar.h"
#include "Trigger/statubar.h"
#include "shapeformattingsetting.h"
#include "textformattingsetting.h"

#include "FileInfo/fileservice.h"


#include "toolboxwidget.h"
#include "Grid/coordinateframe.h"

#include "graphicsscene.h"
#include "graphicsview.h"
#include "Property/propertiesandstylewidget.h"

#include "griddialog.h"
#include "gridsetting.h"

#include "svgnode.h"

#include "itemcommand.h"
#include "appcommand.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->init();
    // set init window title
    if(mGraphicsScene)
    {
        this->setWindowTitle(QObject::tr("%1-%2").arg(mGraphicsScene->getOpenedFileTagName()).arg(AppManager::getAppManager()->getAppName()));
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // destroy appcommand
    ItemCommand::destroyItemCommand();
    AppCommand::destroyAppCommand();
    // destroy manager instance
    TriggerManager::destroyManager();
    // save property
	if (mPropWgd)
	{
		mPropWgd->saveProps();
	}

    int bRet = FileService::sharedFileService()->saveInfo(mGraphicsScene,this);
    if(bRet == QMessageBox::Yes || bRet == QMessageBox::No)
    {
        // close window
        event->accept();
    }
    else if(bRet == QMessageBox::Cancel)
    {
        // not close window
        event->ignore();
    }

    event->accept();
}

void MainWindow::init()
{
    // read config
    AppManager::getAppManager()->readConfig(AppManager::getAppManager()->getConfigFileName());
    // create menu menubar toolbar
    TriggerManager::sharedTriggerManager()->createMenubarAndToolBar(this);
    // create center layout
    this->createCenterLayout();
    // create connect
    this->createConnect();

    QRect rect = AppManager::getAppManager()->getScreenRect();
    this->setWindowFlags(Qt::Dialog);

    //
    mToolboxWgd->setFixedWidth(240);
    mPropWgd->setFixedWidth(240);
    mGraphicsView->setFixedWidth(505);
    this->setFixedHeight(642);
    this->setFixedWidth(987);

    // add statu bar
    mStatuBar = new StatuBar(this);
    this->setStatusBar(mStatuBar);
}

void MainWindow::createCenterLayout()
{
    mHSplitter = new QSplitter(Qt::Horizontal,this);
    mHSplitter->setObjectName("mainSplitter");
    mHSplitter->setHandleWidth(1);

    mToolboxWgd    = new ToolboxWidget(this);
    mGraphicsScene = NULL;

    mGraphicsView  = new GraphicsView(this);
    mGraphicsScene = mGraphicsView->getScene();
    mGraphicsView->setViewSize(AppManager::getAppManager()->getViewSize());
    mPropWgd            = new PropertiesAndStyleWidget(this);
    mPropWgd->initProp(mGraphicsScene->getSceneNode());

    mHSplitter->addWidget(mToolboxWgd);
    mHSplitter->addWidget(mGraphicsView);
    mHSplitter->addWidget(mPropWgd);
    mHSplitter->setStretchFactor(1,1);
    mHSplitter->setOpaqueResize(false);

    this->setCentralWidget(mHSplitter);
}

void MainWindow::createConnect()
{
    ActionManager* aMana = ActionManager::sharedActionManager();
    if(aMana)
    {
        // File
        connect(aMana->m_ActionNew,SIGNAL(triggered()),this,SLOT(slotNew()));
        connect(aMana->m_ActionOpen,SIGNAL(triggered()),this,SLOT(slotOpen()));
        connect(aMana->m_ActionSave,SIGNAL(triggered()),this,SLOT(slotSave()));
        connect(aMana->m_ActionSaveAs,SIGNAL(triggered()),this,SLOT(slotSaveAs()));
        connect(aMana->m_ActionImportFile,SIGNAL(triggered()),mToolboxWgd,SLOT(slotImportFile()));
        connect(aMana->m_ActionImportFolder,SIGNAL(triggered()),mToolboxWgd,SLOT(slotImportFolder()));
        connect(aMana->m_actionRefreshrRes,SIGNAL(triggered()),mToolboxWgd,SLOT(slotRefreshResource()));
        connect(aMana->m_ActionDeleteRes,SIGNAL(triggered()),mToolboxWgd,SLOT(slotDeleteItemFromResource()));
        connect(aMana->m_ActionExit,SIGNAL(triggered()),this,SLOT(close()));
        // view
        connect(aMana->m_ActionWidgetPane,SIGNAL(triggered(bool)),this,SLOT(slotSetWidgetPaneVisible(bool)));
        connect(aMana->m_ActionPropertyPane,SIGNAL(triggered(bool)),this,SLOT(slotSetPropertyPaneVisible(bool)));
        connect(aMana->m_ActionResetView,SIGNAL(triggered()),this,SLOT(slotSetPanesVisible()));

        connect(mGraphicsScene,SIGNAL(sigIsOnlySceneNode(bool)),aMana->m_ActionSave,SLOT(setDisabled(bool)));
        connect(mGraphicsScene,SIGNAL(sigIsOnlySceneNode(bool)),aMana->m_ActionSaveAs,SLOT(setDisabled(bool)));
        connect(mGraphicsScene, SIGNAL(sigSelectedTextItem(bool)), TriggerManager::sharedTriggerManager(), SLOT(slotUpdateTextToolbarEnableState(bool)));
        connect(mGraphicsScene,SIGNAL(sigSelectedItemCnt(int)),TriggerManager::sharedTriggerManager(),SLOT(slotUpdateActionEnableState(int)));
        connect(mGraphicsScene,SIGNAL(sigSelectItemRectF(QRectF)),TriggerManager::sharedTriggerManager(),SLOT(slotUpateLocationAndSize(QRectF)));

        // redo undo
        connect(AppCommand::getAppCommand()->getUndoStack(),SIGNAL(canRedoChanged(bool)),aMana->m_ActionRedo,SLOT(setEnabled(bool)));
        connect(AppCommand::getAppCommand()->getUndoStack(),SIGNAL(canUndoChanged(bool)),aMana->m_ActionUndo,SLOT(setEnabled(bool)));
        connect(aMana->m_ActionRedo,SIGNAL(triggered()),this,SLOT(slotRedo()));
        connect(aMana->m_ActionUndo,SIGNAL(triggered()),this,SLOT(slotUndo()));
        connect(ItemCommand::getItemCommand()->getUndoStack(),SIGNAL(canRedoChanged(bool)),aMana->m_ActionRedo,SLOT(setEnabled(bool)));
        connect(ItemCommand::getItemCommand()->getUndoStack(),SIGNAL(canUndoChanged(bool)),aMana->m_ActionUndo,SLOT(setEnabled(bool)));
        connect(aMana->m_ActionCut,SIGNAL(triggered()),mGraphicsScene,SLOT(slotCut()));
        connect(aMana->m_ActionCopy,SIGNAL(triggered()),mGraphicsScene,SLOT(slotCopy()));
        connect(aMana->m_ActionPaste,SIGNAL(triggered()),mGraphicsScene,SLOT(slotPaste()));
        connect(aMana->m_ActionSelectAll,SIGNAL(triggered()),mGraphicsScene,SLOT(slotSelectAll()));
        connect(aMana->m_ActionDelete,SIGNAL(triggered()),mGraphicsScene,SLOT(slotDelete()));
        // group align
        connect(aMana->m_ActionGroup,SIGNAL(triggered()),mGraphicsScene,SLOT(slotGroupItems()));
        connect(aMana->m_ActionUngroup,SIGNAL(triggered()),mGraphicsScene,SLOT(slotUngroupItems()));
        connect(aMana->m_ActionAlignLeft,SIGNAL(triggered()),mGraphicsScene,SLOT(slotSetSelectedItemsAlignLeft()));
        connect(aMana->m_ActionAlignCenter,SIGNAL(triggered()),mGraphicsScene,SLOT(slotSetSelectedItemsAlignCenter()));
        connect(aMana->m_ActionAlignRight,SIGNAL(triggered()),mGraphicsScene,SLOT(slotSetSelectedItemsAlignRight()));
        connect(aMana->m_ActionAlignTop,SIGNAL(triggered()),mGraphicsScene,SLOT(slotSetSelectedItemsAlignTop()));
        connect(aMana->m_ActionAlignMiddle,SIGNAL(triggered()),mGraphicsScene,SLOT(slotSetSelectedItemsAlignMiddle()));
        connect(aMana->m_ActionAlignBottom,SIGNAL(triggered()),mGraphicsScene,SLOT(slotSetSelectedItemsAlignBottom()));
        // distribute
        connect(aMana->m_ActionDistributeH,SIGNAL(triggered()),mGraphicsScene,SLOT(slotDistributeHorizontal()));
        connect(aMana->m_ActionDistributeV,SIGNAL(triggered()),mGraphicsScene,SLOT(slotDistributeVertical()));
        // grid
        connect(aMana->m_ActionShowGrid,SIGNAL(triggered(bool)),mGraphicsScene,SLOT(slotSetGridVisible(bool)));
        connect(aMana->m_ActionSnaptoGrid,SIGNAL(triggered(bool)),mGraphicsScene,SLOT(slotSetSnapToGrid(bool)));

        //
        connect(mToolboxWgd,SIGNAL(sigItemType(int)),aMana,SLOT(slotSetResourceActionsState(int)));
    }

    MenuManager *mMana = MenuManager::sharedMenuManager();
    if(mMana)
    {
        connect(mMana,SIGNAL(sigZoomIn(float)),mGraphicsScene,SLOT(slotSetItemZoomIn(float)));
        connect(mMana,SIGNAL(sigZoomOut(float)),mGraphicsScene,SLOT(slotSetItemZoomOut(float)));
        connect(mMana,SIGNAL(sigRotatePara(int)),mGraphicsScene,SLOT(slotSetItemRotate(int)));
        connect(mToolboxWgd,SIGNAL(sigItemType(int)),mMana,SLOT(slotUpdateResourceMenuState(int)));
    }

    ToolbarManager *tMana = ToolbarManager::sharedToolbarManager();
    if(tMana)
    {
        connect(tMana->m_EditorToolBar,SIGNAL(sigZoomPercentChanged(QString)),mGraphicsView,SLOT(slotSetSceneScale(QString)));
        connect(tMana->m_EditorToolBar,SIGNAL(sigSceneModeChanged(SceneMode)),mGraphicsScene,SLOT(slotSetSceneMode(SceneMode)));
        connect(tMana->m_TextFormattingToolBar,SIGNAL(sigTextFormattingChanged(TextFormattingSetting)),mGraphicsScene,SLOT(slotSetItemTextFormatting(TextFormattingSetting)));
        connect(tMana->m_ShapeFormattingToolBar,SIGNAL(sigShapeFormattingChanged(ShapeFormattingSetting)),mGraphicsScene,SLOT(slotSetItemShapeFormatting(ShapeFormattingSetting)));
        connect(mGraphicsScene, SIGNAL(sigTextItemSetting(TextFormattingSetting)), tMana->m_TextFormattingToolBar, SLOT(slotSetTextFormatting(TextFormattingSetting)));
        connect(mGraphicsScene, SIGNAL(sigShapItemSetting(ShapeFormattingSetting)), tMana->m_ShapeFormattingToolBar, SLOT(slotSetShapeFormatting(ShapeFormattingSetting)));
    }
    connect(mToolboxWgd,SIGNAL(signalSelectItemType(QString)),mGraphicsScene,SLOT(slotSetDropItemFilePath(QString)));

    connect(mGraphicsScene,SIGNAL(sigMousePos(QPointF)),mStatuBar,SLOT(slotUpdateMousePos(QPointF)));
}

void MainWindow::clearSceneAndProp()
{
    // clear scene
    mGraphicsScene->clearScene();
    // reset prop tree
    mPropWgd->clearProp();
    mPropWgd->initProp(mGraphicsScene->getSceneNode());
    this->setWindowTitle(QObject::tr("%1-%2").arg(mGraphicsScene->getOpenedFileTagName()).arg(AppManager::getAppManager()->getAppName()));
}

void MainWindow::slotNew()
{
    int bRet = FileService::sharedFileService()->saveInfo(mGraphicsScene,this);
    if(bRet == QMessageBox::Cancel)
        return;

    this->clearSceneAndProp();
}

void MainWindow::slotOpen()
{
    int bRet = FileService::sharedFileService()->saveInfo(mGraphicsScene,this);
    if(bRet == QMessageBox::Cancel)
    {
        return;
    }
    else if(bRet == QMessageBox::Yes)
    {
        this->clearSceneAndProp();
    }


    mGraphicsScene->createSceneNodeFromFile(AppManager::getAppManager()->getOpenFile(this));
    mPropWgd->initProp(mGraphicsScene->getSceneNode());
    this->setWindowTitle(QObject::tr("%1-%2").arg(mGraphicsScene->getOpenedFileTagName()).arg(AppManager::getAppManager()->getAppName()));
}

void MainWindow::slotSave()
{
    // 保存
    FileService::sharedFileService()->saveInfoWithoutQues(mGraphicsScene);
    this->setWindowTitle(QObject::tr("%1-%2").arg(mGraphicsScene->getOpenedFileTagName()).arg(AppManager::getAppManager()->getAppName()));
}

void MainWindow::slotSaveAs()
{
    FileService::sharedFileService()->saveAsInfo(mGraphicsScene);
}

void MainWindow::slotSetWidgetPaneVisible(bool v)
{
    if(mToolboxWgd->isVisible() != v)
        mToolboxWgd->setVisible(v);
}

void MainWindow::slotSetPropertyPaneVisible(bool v)
{
    if(mPropWgd->isVisible() != v)
        mPropWgd->setVisible(v);
}

void MainWindow::slotSetPanesVisible()
{
    if(!mToolboxWgd->isVisible())
        mToolboxWgd->setVisible(true);

    if(!mPropWgd->isVisible())
        mPropWgd->setVisible(true);
}

void MainWindow::slotRedo()
{
    AppCommand::getAppCommand()->getUndoStack()->redo();
    ItemCommand::getItemCommand()->getUndoStack()->redo();
    mGraphicsScene->update();
}
void MainWindow::slotUndo()
{
    AppCommand::getAppCommand()->getUndoStack()->undo();
    ItemCommand::getItemCommand()->getUndoStack()->undo();
    mGraphicsScene->update();
}
