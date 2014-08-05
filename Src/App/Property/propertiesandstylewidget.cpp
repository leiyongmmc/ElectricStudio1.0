#include "propertiesandstylewidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QAction>

#include "propertiesandstyletoolbar.h"
#include "electricpropertytablewidget.h"

PropertiesAndStyleWidget::PropertiesAndStyleWidget(QWidget *parent) :
    QDialog(parent)
{
    // 创建布局显示
    this->createLayout();
    this->createConnect();
}

PropertiesAndStyleWidget::~PropertiesAndStyleWidget()
{

}

void PropertiesAndStyleWidget::clearProp()
{
    mPropTableWidget->slotClear();
}

void PropertiesAndStyleWidget::initProp(SvgNode *svg)
{
    if(svg)
    {
        mPropTableWidget->initFromSvg(svg);
    }
}

void PropertiesAndStyleWidget::saveProps()
{
    if(mPropTableWidget)
    {
        mPropTableWidget->slotSubmit();
    }
}

// 创建显示
void PropertiesAndStyleWidget::createLayout()
{
    mGridLayout = new QGridLayout(this);
    mGridLayout->setSpacing(0);
    mGridLayout->setContentsMargins(0,0,0,0);

    mTitle          = new QLabel(tr("Property"),this);
    mTitle->setAlignment(Qt::AlignHCenter);
    mTitle->setObjectName("propertytitle");
    mTitle->setFixedHeight(20);
    mToolBar            = new PropertiesAndStyleToolBar(tr("ToolBox"),this);
    mPropTableWidget     = new ElectricPropertyTableWidget(this);

    mGridLayout->addWidget(mTitle,0,0,1,1);
    mGridLayout->addWidget(mToolBar,1,0,1,1);
    mGridLayout->addWidget(mPropTableWidget,2,0,1,1);

}

void PropertiesAndStyleWidget::createConnect()
{
    connect(mToolBar,SIGNAL(sigAddParamter()),mPropTableWidget,SLOT(slotAdd()));
    connect(mToolBar,SIGNAL(sigRemoveParamter()),mPropTableWidget,SLOT(slotRemove()));
    connect(mToolBar,SIGNAL(sigClearParameter()),mPropTableWidget,SLOT(slotClear()));
    connect(mToolBar,SIGNAL(sigSubumit()),mPropTableWidget,SLOT(slotSubmit()));

    connect(mPropTableWidget,SIGNAL(sigAddDeleteEnable(bool,bool)),mToolBar,SLOT(slotSetBtnsEnable(bool,bool)));
}


