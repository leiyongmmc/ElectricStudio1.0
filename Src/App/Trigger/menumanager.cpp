#include "menumanager.h"

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>

#include "actionmanager.h"

MenuManager* MenuManager::s_SharedMenuManager = NULL;

MenuManager* MenuManager::sharedMenuManager()
{
    if(!s_SharedMenuManager)
        s_SharedMenuManager = new MenuManager();

    return s_SharedMenuManager;
}


void MenuManager::destroyManager()
{
    delete s_SharedMenuManager;
    s_SharedMenuManager = NULL;
}

void MenuManager::createMenubar(QMainWindow *parent)
{
    if(!parent)
        return;

    m_Menubar = new QMenuBar(parent);
    m_Menubar->setObjectName(tr("menuBar"));

    m_MenuFile = new QMenu(tr("File"),m_Menubar);
    m_MenuFile->setObjectName(tr("menuFile"));

    m_MenuImport = new QMenu(tr("Import"),m_MenuFile);
    m_MenuImport->setObjectName(tr("menuImport"));

    m_MenuEdit = new QMenu(tr("Edit"),m_Menubar);
    m_MenuEdit->setObjectName(tr("menuEdit"));

    m_MenuView = new QMenu(tr("View"),m_Menubar);
    m_MenuView->setObjectName(tr("menuView"));

    m_MenuToolbars = new QMenu(tr("Toolbars"),m_MenuView);
    m_MenuToolbars->setObjectName(tr("menuToolbars"));

    m_MenuPanes = new QMenu(tr("Panes"),m_MenuView);
    m_MenuPanes->setObjectName(tr("menuPanes"));

    m_MenuArrange = new QMenu(tr("Arrange"),m_Menubar);
    m_MenuArrange->setObjectName(tr("menuArrange"));

    m_MenuAlign = new QMenu(tr("Align"),m_MenuArrange);
    m_MenuAlign->setObjectName(tr("menuAlign"));

    m_MenuDistribute = new QMenu(tr("Distribute"),m_MenuArrange);
    m_MenuDistribute->setObjectName(tr("menuDistribute"));

    m_MenuGrid = new QMenu(tr("Grid"),m_MenuArrange);
    m_MenuGrid->setObjectName(tr("menuGrid"));

    m_MenuTools = new QMenu(tr("Tools"),m_Menubar);
    m_MenuTools->setObjectName(tr("menuTools"));

    m_Menubar->addAction(m_MenuFile->menuAction());
    m_Menubar->addAction(m_MenuEdit->menuAction());
    m_Menubar->addAction(m_MenuView->menuAction());
    m_Menubar->addAction(m_MenuArrange->menuAction());
    //m_Menubar->addAction(m_MenuTools->menuAction());

    parent->setMenuBar(m_Menubar);

    m_SceneContextMenu = new QMenu(tr("Scene Context Menu"));
    m_SceneContextMenu->setObjectName(tr("menuSceneContextMenu"));

    m_ItemContextMenu = new QMenu(tr("Item Context Menu"));
    m_ItemContextMenu->setObjectName(tr("menuItemContextMenu"));

    m_ZoomIn = new QMenu(tr("Zoom In"),m_ItemContextMenu);
    m_ZoomIn->setObjectName(tr("Zoom In"));

    m_ZoomOut = new QMenu(tr("Zoom Out"),m_ItemContextMenu);
    m_ZoomOut->setObjectName(tr("Zoom Out"));

    m_Rotate = new QMenu(tr("Rotate"),m_ItemContextMenu);
    m_Rotate->setObjectName(tr("Rotate"));

    m_ItemGroupContextMenu = new QMenu(tr("Item Group Context Menu"));
    m_ItemGroupContextMenu->setObjectName(tr("menuItemGroupContextMenu"));

    m_ResourceContextMenu = new QMenu(tr("Resource Context Menu"));
    m_ResourceContextMenu->setObjectName(tr("ResourceContextMenu"));

    ActionManager *mana = ActionManager::sharedActionManager();

    if(mana)
    {
        m_MenuFile->addAction(mana->m_ActionNew);
        m_MenuFile->addAction(mana->m_ActionOpen);
        m_MenuFile->addSeparator();
        m_MenuFile->addAction(mana->m_ActionSave);
        m_MenuFile->addAction(mana->m_ActionSaveAs);
        m_MenuFile->addSeparator();
        m_MenuFile->addAction(m_MenuImport->menuAction());
        m_MenuFile->addSeparator();
        m_MenuFile->addAction(mana->m_ActionExit);

        m_MenuImport->addAction(mana->m_ActionImportFile);
        m_MenuImport->addAction(mana->m_ActionImportFolder);

        m_MenuEdit->addAction(mana->m_ActionRedo);
        m_MenuEdit->addAction(mana->m_ActionUndo);
        m_MenuEdit->addSeparator();
        m_MenuEdit->addAction(mana->m_ActionCut);
        m_MenuEdit->addAction(mana->m_ActionCopy);
        m_MenuEdit->addAction(mana->m_ActionPaste);
        //m_MenuEdit->addSeparator();
        //m_MenuEdit->addAction(mana->m_ActionFind);
        //m_MenuEdit->addAction(mana->m_ActionReplace);
        m_MenuEdit->addSeparator();
        m_MenuEdit->addAction(mana->m_ActionSelectAll);
        m_MenuEdit->addSeparator();
        m_MenuEdit->addAction(mana->m_ActionDelete);

        m_MenuView->addAction(m_MenuToolbars->menuAction());
        m_MenuView->addAction(m_MenuPanes->menuAction());
        m_MenuView->addAction(mana->m_ActionResetView);

        m_MenuToolbars->addAction(mana->m_ActionMainToolBar);
        m_MenuToolbars->addAction(mana->m_ActionEditorToolBar);
        m_MenuToolbars->addAction(mana->m_ActionArrangeToolBar);
        m_MenuToolbars->addAction(mana->m_ActionShapeFormatToolBar);
        m_MenuToolbars->addAction(mana->m_ActionTextFormatToolBar);
        m_MenuToolbars->addAction(mana->m_ActionLocationAndSizeToolBar);

        m_MenuPanes->addAction(mana->m_ActionWidgetPane);
        m_MenuPanes->addAction(mana->m_ActionPropertyPane);
        //
        //m_MenuArrange->addAction(mana->m_ActionGroup);
        //m_MenuArrange->addAction(mana->m_ActionUngroup);
        //m_MenuArrange->addSeparator();
        m_MenuArrange->addAction(m_MenuAlign->menuAction());
        m_MenuArrange->addAction(m_MenuDistribute->menuAction());
        m_MenuArrange->addSeparator();
        //m_MenuArrange->addAction(m_MenuGrid->menuAction());

        m_MenuAlign->addAction(mana->m_ActionAlignLeft);
        m_MenuAlign->addAction(mana->m_ActionAlignCenter);
        m_MenuAlign->addAction(mana->m_ActionAlignRight);
        m_MenuAlign->addSeparator();
        m_MenuAlign->addAction(mana->m_ActionAlignTop);
        m_MenuAlign->addAction(mana->m_ActionAlignMiddle);
        m_MenuAlign->addAction(mana->m_ActionAlignBottom);

        m_MenuDistribute->addAction(mana->m_ActionDistributeH);
        m_MenuDistribute->addAction(mana->m_ActionDistributeV);

        m_MenuGrid->addAction(mana->m_ActionShowGrid);
        m_MenuGrid->addAction(mana->m_ActionSnaptoGrid);
        m_MenuGrid->addAction(mana->m_ActionGridSetting);

        //m_MenuTools->addAction(mana->m_ActionOptions);

        m_SceneContextMenu->addAction(mana->m_ActionPaste);
        m_SceneContextMenu->addAction(mana->m_ActionSelectAll);
        //m_SceneContextMenu->addAction(m_MenuGrid->menuAction());

        m_ItemContextMenu->addAction(mana->m_ActionCut);
        m_ItemContextMenu->addAction(mana->m_ActionCopy);
        m_ItemContextMenu->addAction(mana->m_ActionPaste);
        m_ItemContextMenu->addSeparator();
        m_ItemContextMenu->addAction(mana->m_ActionDelete);
        m_ItemContextMenu->addSeparator();
        m_ItemContextMenu->addAction(m_ZoomIn->menuAction());
        m_ItemContextMenu->addAction(m_ZoomOut->menuAction());
        m_ItemContextMenu->addSeparator();
        m_ItemContextMenu->addAction(m_Rotate->menuAction());

        m_ZoomIn->addAction(mana->m_ActionZoomIn10);
        m_ZoomIn->addAction(mana->m_ActionZoomIn20);
        m_ZoomIn->addAction(mana->m_ActionZoomIn50);
        m_ZoomIn->addAction(mana->m_ActionZoomIn100);


        m_ZoomOut->addAction(mana->m_ActionZoomOut10);
        m_ZoomOut->addAction(mana->m_ActionZoomOut20);
        m_ZoomOut->addAction(mana->m_ActionZoomOut50);
        m_ZoomOut->addAction(mana->m_ActionZoomOut100);


        m_Rotate->addAction(mana->m_ActionRotateR90);
        m_Rotate->addAction(mana->m_ActionRotateL90);
        m_Rotate->addAction(mana->m_ActionRotate180);
        //m_Rotate->addSeparator();
        //m_Rotate->addAction(mana->m_ActionFlipHorizontal);
        //m_Rotate->addAction(mana->m_ActionFlipVertical);

        m_ItemGroupContextMenu->addAction(mana->m_ActionCut);
        m_ItemGroupContextMenu->addAction(mana->m_ActionCopy);
        m_ItemGroupContextMenu->addAction(mana->m_ActionPaste);
        m_ItemGroupContextMenu->addSeparator();
        m_ItemGroupContextMenu->addAction(mana->m_ActionDelete);
        //m_ItemGroupContextMenu->addSeparator();
        //m_ItemGroupContextMenu->addAction(mana->m_ActionGroup);
        //m_ItemGroupContextMenu->addAction(mana->m_ActionUngroup);
        m_ItemGroupContextMenu->addSeparator();
        m_ItemGroupContextMenu->addAction(m_MenuAlign->menuAction());

        m_ResourceContextMenu->addAction(mana->m_ActionImportFile);
        m_ResourceContextMenu->addAction(mana->m_ActionImportFolder);
        m_ResourceContextMenu->addSeparator();
        m_ResourceContextMenu->addAction(mana->m_actionRefreshrRes);
        m_ResourceContextMenu->addAction(mana->m_ActionDeleteRes);
    }
    connect(m_ZoomIn,SIGNAL(triggered(QAction*)),this,SLOT(slotZoomIn(QAction*)));
    connect(m_ZoomOut,SIGNAL(triggered(QAction*)),this,SLOT(slotZoomOut(QAction*)));
    connect(m_Rotate,SIGNAL(triggered(QAction*)),this,SLOT(slotRotate(QAction*)));
}

void MenuManager::slotZoomIn(QAction*action)
{
    if(!action)
        return;
    float in = 0.0f;
    in = action->text().left(action->text().indexOf(tr("%"))).toFloat() /100.0;
    emit sigZoomIn(in);
}

void MenuManager::slotZoomOut(QAction*action)
{
    if(!action)
        return;
    float out = 0.0f;
    out = action->text().left(action->text().indexOf(tr("%"))).toFloat() /100.0;
    emit sigZoomOut(out);
}

void MenuManager::slotRotate(QAction *action)
{
    if(!action)
        return;
    ActionManager *mana = ActionManager::sharedActionManager();
    if(mana)
    {
        QList<QAction*> actions;
        actions.clear();
        actions.append(mana->m_ActionRotateR90);
        actions.append(mana->m_ActionRotateL90);
        actions.append(mana->m_ActionRotate180);
        //actions.append(mana->m_ActionFlipHorizontal);
        //actions.append(mana->m_ActionFlipVertical);

        for(int i =0; i < actions.count(); i++)
        {
            if(action == actions.at(i))
            {
                emit sigRotatePara(i);
            }
        }
    }
}

QMenu* MenuManager::getGraphicsSceneContextMenu(GraphicsSceneContextMenuType type)
{
    if(type == NoContextMenu)
        return NULL;
    else if(type == SceneContextMenu)
        return m_SceneContextMenu;
    else if(type == ItemContextMenu)
        return m_ItemContextMenu;
    else if(type == ItemGroupContextMenu)
        return m_ItemGroupContextMenu;
}

void MenuManager::setGraphicsSceneContextMenuType(GraphicsSceneContextMenuType type)
{
    m_ContextMenuType = type;
}

MenuManager::GraphicsSceneContextMenuType MenuManager::getGraphicsSceneContextMenuType()
{
    return m_ContextMenuType;
}

MenuManager::MenuManager(QObject *parent) :
    QObject(parent)
{
    m_ContextMenuType = SceneContextMenu;
}

MenuManager::~MenuManager()
{

}
