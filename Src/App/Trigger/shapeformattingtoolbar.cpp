#include "shapeformattingtoolbar.h"

#include <QToolButton>
#include <QColorDialog>
#include <QMenu>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>

#include "util.h"

ShapeFormattingToolBar::ShapeFormattingToolBar(const QString &name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);

    this->createToolbar();
    this->createConnect();

    this->setEnabled(false);
}

void ShapeFormattingToolBar::initFromShapeFormattingSetting(ShapeFormattingSetting setting)
{
    mShapeSetting.mLineColor = setting.mLineColor;
    mShapeSetting.mLinePenPattern = setting.mLinePenPattern;
    mShapeSetting.mLineWidth = setting.mLineWidth;
    mShapeSetting.mFillColor = setting.mFillColor;

	if (mLineColor)
		mLineColor->setIcon(Util::createColorToolButtonIcon(":/LineColor.png", mShapeSetting.mLineColor));
}

void ShapeFormattingToolBar::slotSetShapeFormatting(ShapeFormattingSetting setting)
{
	this->initFromShapeFormattingSetting(setting);
}

ShapeFormattingSetting& ShapeFormattingToolBar::getShapeFormattingSetting()
{
    return mShapeSetting;
}

void ShapeFormattingToolBar::createToolbar()
{
    mLineWidthMenu = new QMenu(tr("Line Width"));
    mLineWidthBtns = new QList<QToolButton*>();
    mLineWidthBtns->clear();
    QMap<int,QIcon> widthIcons = Util::createLineWidthIcons();
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0.5);
    gridLayout->setContentsMargins(0,0,0,0);
    for(int i = 0; i < widthIcons.count(); i++)
    {
        QToolButton *btn = new QToolButton();
        btn->setToolTip(tr("%1").arg(widthIcons.keys().at(i)));
        btn->setIcon(widthIcons.values().at(i));
        btn->setIconSize(QSize(200,24));
        gridLayout->addWidget(btn,i,0,1,1);
        mLineWidthBtns->append(btn);
    }

    mLineWidthMenu->setLayout(gridLayout);


    mLineColor = new QToolButton(this);
    mLineColor->setObjectName(tr("LineColor"));
    mLineColor->setToolTip(tr("Line Color"));
    mLineColor->setText(tr("Line Color"));
    mLineColor->setIcon(Util::createColorToolButtonIcon(":/LineColor.png",Qt::red));

    mLineWidth = new QToolButton(this);
    mLineWidth->setObjectName(tr("LineWidth"));
    mLineWidth->setToolTip(tr("Line Width"));
    mLineWidth->setText(tr("Line Width"));
    mLineWidth->setIcon(QIcon(":/LineWidth.png"));
    mLineWidth->setPopupMode(QToolButton::MenuButtonPopup);
    mLineWidth->setMenu(mLineWidthMenu);

    mLinePattern = new QToolButton(this);
    mLinePattern->setObjectName(tr("LinePattern"));
    mLinePattern->setToolTip(tr("Line Pattern"));
    mLinePattern->setText(tr("Line Pattern"));
    mLinePattern->setIcon(QIcon(":/LinePattern.png"));
    mLinePattern->setPopupMode(QToolButton::MenuButtonPopup);
	mLinePattern->setVisible(false);

    mFillColor = new QToolButton(this);
    mFillColor->setObjectName(tr("FillColor"));
    mFillColor->setToolTip(tr("Fill Color"));
    mFillColor->setText(tr("Fill Color"));
    mFillColor->setIcon(QIcon(":/FillColor.png"));

    this->addWidget(mLineColor);
    this->addWidget(mLineWidth);
    this->addWidget(mLinePattern);
    this->addWidget(mFillColor);
}

void ShapeFormattingToolBar::createConnect()
{
    connect(mLineColor,SIGNAL(clicked()),this,SLOT(slotSetLineColor()));
    connect(mFillColor,SIGNAL(clicked()),this,SLOT(slotSetFillColor()));

    if(mLineWidthBtns)
    {
        int cnt = mLineWidthBtns->count();
        for(int i = 0; i < cnt; i++)
        {
            QToolButton *btn = mLineWidthBtns->at(i);
            connect(btn,SIGNAL(clicked()),this,SLOT(slotSetLineWidth()));
        }
    }
}

void ShapeFormattingToolBar::slotSetLineColor()
{
    QColor color = QColorDialog::getColor(mShapeSetting.mLineColor,this,tr("Line Color"));
    if(color.isValid())
    {
        mShapeSetting.mLineColor = color;
        mLineColor->setIcon(Util::createColorToolButtonIcon(":/LineColor.png",color));
    }

    emit sigShapeFormattingChanged(mShapeSetting);
}

void ShapeFormattingToolBar::slotSetFillColor()
{
    QColor color = QColorDialog::getColor(mShapeSetting.mFillColor,this,tr("Fill Color"));
    if(color.isValid())
    {
        mShapeSetting.mFillColor = color;
    }

    emit sigShapeFormattingChanged(mShapeSetting);
}

void ShapeFormattingToolBar::slotSetLineWidth()
{
    QToolButton* item =static_cast<QToolButton*>(this->sender());
    for(int i = 0; i < mLineWidthBtns->count(); i++)
    {
        QToolButton *child = mLineWidthBtns->at(i);
        if(child == item)
        {
            mShapeSetting.mLineWidth = child->toolTip().toInt();
            emit sigShapeFormattingChanged(mShapeSetting);
            return;
        }
    }
}
