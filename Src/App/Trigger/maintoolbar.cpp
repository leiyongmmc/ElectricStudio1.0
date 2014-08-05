#include "maintoolbar.h"

#include "actionmanager.h"

MainToolBar::MainToolBar(const QString& name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);

    this->createToolbar();
    this->createConnect();
}

void MainToolBar::createToolbar()
{
    if(ActionManager *mana = ActionManager::sharedActionManager())
    {
        this->addAction(mana->m_ActionNew);
        this->addAction(mana->m_ActionOpen);
        this->addAction(mana->m_ActionSave);
        this->addSeparator();
        this->addAction(mana->m_ActionCut);
        this->addAction(mana->m_ActionCopy);
        this->addAction(mana->m_ActionPaste);
        this->addSeparator();
        this->addAction(mana->m_ActionUndo);
        this->addAction(mana->m_ActionRedo);
    }
}


void MainToolBar::createConnect()
{

}
