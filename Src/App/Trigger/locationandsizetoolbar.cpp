#include "locationandsizetoolbar.h"

#include <QToolButton>
#include <QLabel>
#include <QLineEdit>

LocationAndSizeToolBar::LocationAndSizeToolBar(const QString &name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);

    this->createToolbar();
    this->createConnect();

    this->setEnabled(false);
}

void LocationAndSizeToolBar::setLocationAndSize(QRectF rect)
{
    if(rect.isValid())
    {
        mXLineEdit->setText(QString::number(rect.y()));
        mYLineEdit->setText(QString::number(rect.x()));
        mWidthLineEdit->setText(QString::number(rect.width()));
        mHeightLineEdit->setText(QString::number(rect.height()));
    }
    else
    {
        mXLineEdit->clear();
        mYLineEdit->clear();
        mWidthLineEdit->clear();
        mHeightLineEdit->clear();
    }
}

void LocationAndSizeToolBar::createToolbar()
{
    mXLabel = new QLabel("x:",this);
    mXLineEdit = new QLineEdit(this);
    mXLineEdit->setFixedWidth(80);
    mXLineEdit->setReadOnly(true);
    mYLabel = new QLabel("y:",this);
    mYLineEdit = new QLineEdit(this);
    mYLineEdit->setFixedWidth(80);
    mYLineEdit->setReadOnly(true);
    mWidthLabel = new QLabel("w:",this);
    mWidthLineEdit = new QLineEdit(this);
    mWidthLineEdit->setFixedWidth(80);
    mWidthLineEdit->setReadOnly(true);
    mHeightLabel = new QLabel("h:",this);
    mHeightLineEdit = new QLineEdit(this);
    mHeightLineEdit->setFixedWidth(80);
    mHeightLineEdit->setReadOnly(true);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->addWidget(mXLabel);
    this->addWidget(mYLineEdit);
    this->addWidget(mYLabel);
    this->addWidget(mXLineEdit);
    this->addWidget(mWidthLabel);
    this->addWidget(mWidthLineEdit);
    this->addWidget(mHeightLabel);
    this->addWidget(mHeightLineEdit);
    this->addWidget(spacer);
}

void LocationAndSizeToolBar::createConnect()
{}


