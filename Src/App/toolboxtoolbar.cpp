#include "toolboxtoolbar.h"

#include <QDebug>
#include <QToolButton>
#include <QSpacerItem>

#include "resourcemanager.h"

#include "util.h"

ToolboxToolBar::ToolboxToolBar(const QString& name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);
    this->setContentsMargins(0,0,0,0);

    this->createToolbar();
    this->createConnect();
}

void ToolboxToolBar::createToolbar()
{
    mImportFileBtn = new QToolButton(this);
    mImportFileBtn->setObjectName(tr("ImportFile"));
    mImportFileBtn->setText(tr("Import File"));
    mImportFileBtn->setToolTip(tr("Import Resource File"));
    mImportFileBtn->setIcon(QIcon(":/File.png"));
    mImportFileBtn->setEnabled(false);

    mImportFolderBtn = new QToolButton(this);
    mImportFolderBtn->setObjectName(tr("ImportFolder"));
    mImportFolderBtn->setToolTip(tr("Import Resource Folder"));
    mImportFolderBtn->setText(tr("Import Folder"));
    mImportFolderBtn->setIcon(QIcon(":/Folder.png"));
    mImportFolderBtn->setEnabled(true);

    mRefreshBtn = new QToolButton(this);
    mRefreshBtn->setObjectName(tr("Refresh"));
    mRefreshBtn->setToolTip(tr("Refresh Resource"));
    mRefreshBtn->setText(tr("Refresh"));
    mRefreshBtn->setIcon(QIcon(":/Refresh.png"));

    mFindBtn = new QToolButton(this);
    mFindBtn->setObjectName(tr("Find"));
    mFindBtn->setText(tr("Find"));
    mFindBtn->setToolTip(tr("Filter"));
    mFindBtn->setCheckable(true);
    mFindBtn->setChecked(false);
    mFindBtn->setIcon(QIcon(":/Find.png"));
    mFindBtn->setVisible(false);

    this->addWidget(mImportFileBtn);
    this->addWidget(mImportFolderBtn);
    this->addWidget(mRefreshBtn);
    this->addWidget(mFindBtn);
}

void ToolboxToolBar::createConnect()
{
    connect(mFindBtn,SIGNAL(clicked()),this,SLOT(slotSetFindLineEditVisible()));
}

void ToolboxToolBar::slotSetFindLineEditVisible()
{
    emit sigFilterLineEditVisible(mFindBtn->isChecked());
}

void ToolboxToolBar::slotSetBtnEnableState(int index)
{
    mImportFileBtn->setEnabled(false);
    mImportFolderBtn->setEnabled(false);
    if(index == 0)
    {
        mImportFolderBtn->setEnabled(true);
    }
    else if(index == 1)
    {
        mImportFileBtn->setEnabled(true);
    }
}
