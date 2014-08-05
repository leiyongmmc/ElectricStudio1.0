#include "toolbar.h"

ToolBar::ToolBar(const QString& name,QWidget *parent) :
    QToolBar(parent)
{
    this->setObjectName(name);
    mName = name;
}


QString ToolBar::getToolBarName()
{
    return mName;
}
