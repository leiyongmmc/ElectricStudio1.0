#include "arrangetoolbar.h"

#include "actionmanager.h"

ArrangeToolBar::ArrangeToolBar(const QString& name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);

    this->createToolbar();
    this->createConnect();
}

void ArrangeToolBar::createToolbar()
{
    if(ActionManager *mana = ActionManager::sharedActionManager())
    {
        //this->addAction(mana->m_ActionGroup);
        //this->addAction(mana->m_ActionUngroup);
        //this->addSeparator();
        this->addAction(mana->m_ActionAlignLeft);
        this->addAction(mana->m_ActionAlignCenter);
        this->addAction(mana->m_ActionAlignRight);
        this->addAction(mana->m_ActionAlignTop);
        this->addAction(mana->m_ActionAlignMiddle);
        this->addAction(mana->m_ActionAlignBottom);
        this->addSeparator();
        this->addAction(mana->m_ActionDistributeH);
        this->addAction(mana->m_ActionDistributeV);
    }
}


void ArrangeToolBar::createConnect()
{

}
