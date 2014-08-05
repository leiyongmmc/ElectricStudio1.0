#include "propertiesandstyletoolbar.h"

#include <QDebug>
#include <QToolButton>
#include <QSpacerItem>

PropertiesAndStyleToolBar::PropertiesAndStyleToolBar(const QString& name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);
    this->setContentsMargins(0,0,0,0);

    this->createToolbar();
    this->createConnect();
}

void PropertiesAndStyleToolBar::createToolbar()
{
    mAddBtn = new QToolButton(this);
    mAddBtn->setObjectName("AddParamter");
    mAddBtn->setText(tr("Add Parameter"));
    mAddBtn->setToolTip(tr("Add Paramters"));
    mAddBtn->setIcon(QIcon(":/Add.png"));

    mRemoveBtn = new QToolButton(this);
    mRemoveBtn->setText(tr("RemoveParamter"));
    mRemoveBtn->setToolTip(tr("Remove Paramters"));
    mRemoveBtn->setIcon(QIcon(":/Remove.png"));

    mClearBtn = new QToolButton(this);
    mClearBtn->setText(tr("ClearParamter"));
    mClearBtn->setToolTip(tr("Clear Paramters"));
    mClearBtn->setIcon(QIcon(":/Clear.png"));
	mClearBtn->setVisible(false);

    mSubmitBtn = new QToolButton(this);
    mSubmitBtn->setText(tr("Submit"));
    mSubmitBtn->setToolTip(tr("Submit"));
    mSubmitBtn->setIcon(QIcon(":/Submit.png"));

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->addWidget(spacer);
    this->addWidget(mAddBtn);
    this->addWidget(mRemoveBtn);
    //this->addWidget(mClearBtn);
    this->addWidget(mSubmitBtn);
}

void PropertiesAndStyleToolBar::createConnect()
{
    connect(mAddBtn,SIGNAL(clicked()),this,SIGNAL(sigAddParamter()));
    connect(mRemoveBtn,SIGNAL(clicked()),this,SIGNAL(sigRemoveParamter()));
    connect(mClearBtn,SIGNAL(clicked()),this,SIGNAL(sigClearParameter()));;
    connect(mSubmitBtn,SIGNAL(clicked()),this,SIGNAL(sigSubumit()));
}

