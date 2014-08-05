#include "triggermanager.h"

#include <QMenu>
#include <QDebug>

#include "actionmanager.h"
#include "locationandsizetoolbar.h"
#include "shapeformattingtoolbar.h"
#include "textformattingtoolbar.h"
#include "toolbarmanager.h"
#include "menumanager.h"

TriggerManager* TriggerManager::s_SharedTriggerManager = NULL;

TriggerManager* TriggerManager::sharedTriggerManager()
{
    if(!s_SharedTriggerManager)
        s_SharedTriggerManager = new TriggerManager();

    return s_SharedTriggerManager;
}

void TriggerManager::destroyManager()
{
    delete s_SharedTriggerManager;
    s_SharedTriggerManager = NULL;
}

void TriggerManager::createMenubarAndToolBar(QMainWindow *parent)
{
    if(!parent)
        return;

    m_ActionManager = ActionManager::sharedActionManager();
    m_ToolbarManager  = ToolbarManager::sharedToolbarManager();
    m_MenuManager = MenuManager::sharedMenuManager();

    if(m_ActionManager && m_ToolbarManager && m_MenuManager)
    {
        m_ActionManager->createActions(parent);
        m_ToolbarManager->createToolbars(parent);
        m_MenuManager->createMenubar(parent);

        // toolbars visible
        connect(m_MenuManager->m_MenuToolbars,SIGNAL(triggered(QAction*)),m_ToolbarManager,SLOT(slotSetToolbarsVisible(QAction*)));
        // grid setting

    }
}

void TriggerManager::slotUpdateActionEnableState(int itemCnt)
{
    m_ActionManager->m_ActionCut->setEnabled((bool)itemCnt);
    m_ActionManager->m_ActionCopy->setEnabled((bool)itemCnt);
    m_ActionManager->m_ActionPaste->setEnabled(true);
    m_ActionManager->m_ActionDelete->setEnabled((bool)itemCnt);

    bool itemGroup = false;
    if(itemCnt >= 2)
    {
        itemGroup = true;
    }

    m_ActionManager->m_ActionGroup->setEnabled(itemGroup);
    m_ActionManager->m_ActionAlignLeft->setEnabled(itemGroup);
    m_ActionManager->m_ActionAlignCenter->setEnabled(itemGroup);
    m_ActionManager->m_ActionAlignRight->setEnabled(itemGroup);
    m_ActionManager->m_ActionAlignTop->setEnabled(itemGroup);
    m_ActionManager->m_ActionAlignMiddle->setEnabled(itemGroup);
    m_ActionManager->m_ActionAlignBottom->setEnabled(itemGroup);

    if(itemCnt ==0)
    {
        m_ActionManager->m_ActionDistributeH->setEnabled(false);
        m_ActionManager->m_ActionDistributeV->setEnabled(false);
    }
    else if(itemCnt >= 3)
    {
        m_ActionManager->m_ActionDistributeH->setEnabled(true);
        m_ActionManager->m_ActionDistributeV->setEnabled(true);
    }

    //
    m_ToolbarManager->m_LocationAndSizeToolBar->setEnabled((bool)itemCnt);
    m_ToolbarManager->m_ShapeFormattingToolBar->setEnabled((bool)itemCnt);
    //m_ToolbarManager->m_TextFormattingToolBar->setEnabled((bool)itemCnt);
}

void TriggerManager::slotUpateLocationAndSize(QRectF rect)
{
    m_ToolbarManager->m_LocationAndSizeToolBar->setLocationAndSize(rect);
}

void TriggerManager::slotUpdateTextToolbarEnableState(bool enable)
{
	m_ToolbarManager->m_TextFormattingToolBar->setEnabled(enable);
}

TriggerManager::TriggerManager(QObject *parent) :
    QObject(parent)
{
    m_ActionManager = NULL;
    m_ToolbarManager = NULL;
    m_MenuManager = NULL;
}

TriggerManager::~TriggerManager()
{
    if(m_ActionManager)
        ActionManager::destroyManager();
    if(m_ToolbarManager)
        ToolbarManager::destroyManager();
    if(m_MenuManager)
        MenuManager::destroyManager();
}

