#include "toolbarmanager.h"

#include <QMainWindow>
#include <QAction>

#include "toolbar.h"
#include "maintoolbar.h"
#include "editortoolbar.h"
#include "arrangetoolbar.h"
#include "textformattingtoolbar.h"
#include "shapeformattingtoolbar.h"
#include "locationandsizetoolbar.h"


ToolbarManager* ToolbarManager::s_sharedToolbarManager = NULL;

ToolbarManager* ToolbarManager::sharedToolbarManager()
{
    if(!s_sharedToolbarManager)
        s_sharedToolbarManager = new ToolbarManager();

    return s_sharedToolbarManager;
}

void ToolbarManager::destroyManager()
{
    delete s_sharedToolbarManager;
    s_sharedToolbarManager = NULL;
}

void ToolbarManager::createToolbars(QMainWindow *parent)
{
    if(!parent)
        return;

    m_Toolbars.clear();
    m_MainToolBar                = new MainToolBar(tr("MainToolBar"),parent);
    m_EditorToolBar              = new EditorToolBar(tr("EditorToolBar"),parent);
    m_TextFormattingToolBar      = new TextFormattingToolBar(tr("TextFormattingToolBar"),parent);
    m_TextFormattingToolBar->initFromTextFormattingSetting();
    m_ArrangeToolBar             = new ArrangeToolBar(tr("ArrangeToolBar"),parent);
    m_ShapeFormattingToolBar     = new ShapeFormattingToolBar(tr("ShapeFormattingToolBar"),parent);
    m_ShapeFormattingToolBar->initFromShapeFormattingSetting();
    m_LocationAndSizeToolBar     = new LocationAndSizeToolBar(tr("LocationAndSizeToolBar"),parent);

    parent->addToolBar(m_MainToolBar);
    parent->addToolBar(m_EditorToolBar);
    parent->addToolBar(m_TextFormattingToolBar);
    parent->addToolBarBreak();
    parent->addToolBar(m_ArrangeToolBar);
    parent->addToolBar(m_ShapeFormattingToolBar);
    parent->addToolBar(m_LocationAndSizeToolBar);

    m_Toolbars.append(m_MainToolBar);
    m_Toolbars.append(m_EditorToolBar);
    m_Toolbars.append(m_TextFormattingToolBar);
    m_Toolbars.append(m_ArrangeToolBar);
    m_Toolbars.append(m_ShapeFormattingToolBar);
    m_Toolbars.append(m_LocationAndSizeToolBar);
}

ToolbarManager::ToolbarManager(QObject *parent) :
    QObject(parent)
{
}

ToolbarManager::~ToolbarManager()
{}

void ToolbarManager::createConnect()
{

}

void ToolbarManager::slotSetToolbarsVisible(QAction *action)
{
    foreach (QToolBar *toolbar, m_Toolbars)
    {
        if(action->objectName() == toolbar->objectName())
        {
            toolbar->setVisible(action->isChecked());
        }
    }
}
