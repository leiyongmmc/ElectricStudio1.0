#include "textformattingtoolbar.h"

#include <QDebug>
#include <QAction>
#include <QFont>
#include <QFontComboBox>
#include <QComboBox>
#include <QToolButton>
#include <QSpacerItem>
#include <QStringList>
#include <QColorDialog>

#include "util.h"

TextFormattingToolBar::TextFormattingToolBar(const QString &name,QWidget *parent) :
    ToolBar(name,parent)
{
    this->setObjectName(name);

    this->createToolbar();
    this->createConnect();

    this->setEnabled(false);
}

void TextFormattingToolBar::initFromTextFormattingSetting(TextFormattingSetting setting)
{
	mTextSetting = setting;

	mFontFamily->setCurrentFont(QFont(mTextSetting.mFamily));
	mFontStyle->setCurrentIndex((int)mTextSetting.mStyle);
	mFontSize->setCurrentText(QString::number(mTextSetting.mPointSize));

	mBold->setChecked(mTextSetting.mBold);
	mItalic->setChecked(mTextSetting.mItalic);
	mUnderline->setChecked(mTextSetting.mUnderline);

    if(mTextSetting.mTextAlignFlag== Qt::AlignLeft)
    {
        mAlignLeft->setChecked(true);
        mAlignCenter->setChecked(false);
        mAlignRight->setChecked(false);
    }
	else if (mTextSetting.mTextAlignFlag == Qt::AlignHCenter)
    {
        mAlignLeft->setChecked(false);
        mAlignCenter->setChecked(true);
        mAlignRight->setChecked(false);
    }
	else if (mTextSetting.mTextAlignFlag == Qt::AlignRight)
    {
        mAlignLeft->setChecked(false);
        mAlignCenter->setChecked(false);
        mAlignRight->setChecked(true);
    }
}

void TextFormattingToolBar::slotSetTextFormatting(TextFormattingSetting setting)
{
	this->initFromTextFormattingSetting(setting);
}

TextFormattingSetting& TextFormattingToolBar::getTextFormattingSetting()
{
    return mTextSetting;
}

void TextFormattingToolBar::createToolbar()
{
    mFontFamily = new QFontComboBox(this);
    mFontFamily->setObjectName(tr("FontFaimly"));
    mFontFamily->setToolTip(tr("Font Faimly"));
    mFontFamily->setEditable(false);

    mFontStyle  = new QComboBox(this);
    mFontStyle->setObjectName(tr("FontStyle"));
    mFontStyle->setToolTip(tr("Font Style"));
    mFontStyle->setMinimumWidth(80);
    //mFontStyle->setEditable(true);
    QStringList fontStyle;
    Util::getFontStyle(fontStyle);
    mFontStyle->addItems(fontStyle);
	mFontStyle->setVisible(false);

    mFontSize = new QComboBox(this);
    mFontSize->setObjectName(tr("FontSize"));
    mFontSize->setToolTip(tr("Font Size"));
    mFontSize->setMinimumWidth(60);
    //mFontSize->setEditable(true);
    QStringList fontSize;
    Util::getFontSize(fontSize);
    mFontSize->addItems(fontSize);

    mBold = new QToolButton(this);
    mBold->setObjectName(tr("Bold"));
    mBold->setToolTip(tr("Bold"));
    mBold->setText(tr("Bold"));
    mBold->setIcon(QIcon(":/Bold.png"));
    mBold->setShortcut(QKeySequence(QKeySequence::Bold));
    mBold->setCheckable(true);

    mItalic = new QToolButton(this);
    mItalic->setObjectName(tr("Italic"));
    mItalic->setToolTip(tr("Italic"));
    mItalic->setText(tr("Italic"));
    mItalic->setIcon(QIcon(":/Italic.png"));
    mItalic->setShortcut(QKeySequence(QKeySequence::Italic));
    mItalic->setCheckable(true);

    mUnderline = new QToolButton(this);
    mUnderline->setObjectName(tr("Underline"));
    mUnderline->setToolTip(tr("Underline"));
    mUnderline->setText(tr("Underline"));
    mUnderline->setIcon(QIcon(":/Underline.png"));
    mUnderline->setCheckable(true);

    mAlignLeft = new QToolButton(this);
    mAlignLeft->setObjectName("AlignLeft");
    mAlignLeft->setToolTip("Align Left");
    mAlignLeft->setText("Align Left");
    mAlignLeft->setIcon(QIcon(":/TextAlignLeft.png"));
    mAlignLeft->setCheckable(true);
    mAlignLeft->setChecked(true);
	mAlignLeft->setVisible(false);

    mAlignCenter = new QToolButton(this);
    mAlignCenter->setObjectName("AlignCenter");
    mAlignCenter->setToolTip("Align Center");
    mAlignCenter->setText("Align Center");
    mAlignCenter->setIcon(QIcon(":/TextAlignCenter.png"));
    mAlignCenter->setCheckable(true);
	mAlignCenter->setVisible(false);

    mAlignRight = new QToolButton(this);
    mAlignRight->setObjectName("AlignRight");
    mAlignRight->setToolTip("Align Right");
    mAlignRight->setText("Align Right");
    mAlignRight->setIcon(QIcon(":/TextAlignRight.png"));
    mAlignRight->setCheckable(true);
	mAlignRight->setVisible(false);

    mTextColor = new QToolButton(this);
    mTextColor->setObjectName(tr("TextColor"));
    mTextColor->setToolTip(tr("Text Color"));
    mTextColor->setText(tr("Text Color"));
    mTextColor->setIcon(QIcon(":/TextColor.png"));

    this->addWidget(mFontFamily);
    //this->addWidget(mFontStyle);
    this->addWidget(mFontSize);
    this->addSeparator();
    this->addWidget(mBold);
    this->addWidget(mItalic);
    this->addWidget(mUnderline);
    this->addSeparator();
    //this->addWidget(mAlignLeft);
    //this->addWidget(mAlignCenter);
    //this->addWidget(mAlignRight);
    //this->addSeparator();
    this->addWidget(mTextColor);
}


void TextFormattingToolBar::createConnect()
{
    connect(mFontFamily,SIGNAL(currentTextChanged(QString)),this,SLOT(slotSetFontFamily(QString)));
    connect(mFontStyle,SIGNAL(currentTextChanged(QString)),this,SLOT(slotSetFontStyle(QString)));
    connect(mFontSize,SIGNAL(currentTextChanged(QString)),this,SLOT(slotSetFontSize(QString)));

    connect(mBold,SIGNAL(clicked(bool)),this,SLOT(slotSetTextBIU(bool)));
    connect(mItalic,SIGNAL(clicked(bool)),this,SLOT(slotSetTextBIU(bool)));
    connect(mUnderline,SIGNAL(clicked(bool)),this,SLOT(slotSetTextBIU(bool)));

    connect(mAlignLeft,SIGNAL(clicked()),this,SLOT(slotSetTextHorizontalAlign()));
    connect(mAlignCenter,SIGNAL(clicked()),this,SLOT(slotSetTextHorizontalAlign()));
    connect(mAlignRight,SIGNAL(clicked()),this,SLOT(slotSetTextHorizontalAlign()));

    connect(mTextColor,SIGNAL(clicked()),this,SLOT(slotSetTextColor()));
}

void TextFormattingToolBar::slotSetFontFamily(QString family)
{
	mTextSetting.mFamily = family;

    emit sigTextFormattingChanged(mTextSetting);
}

void TextFormattingToolBar::slotSetFontStyle(QString styleStr)
{
    QFont::Style style;
    if(styleStr == tr("Normal"))
    {
        style = QFont::StyleNormal;
    }
    else if(styleStr == tr("Italic"))
    {
        style = QFont::StyleItalic;
    }
    else if(styleStr == tr("Oblique"))
    {
        style = QFont::StyleOblique;
    }

	mTextSetting.mStyle = style;

    emit sigTextFormattingChanged(mTextSetting);
}

void TextFormattingToolBar::slotSetFontSize(QString sizestr)
{
	mTextSetting.mPointSize = sizestr.toInt();

    emit sigTextFormattingChanged(mTextSetting);
}

void TextFormattingToolBar::slotSetTextColor()
{
    QColor color = QColorDialog::getColor(mTextSetting.mTextColor,this,tr("Text Color"));
    if(color.isValid())
    {
        mTextSetting.mTextColor = color;
    }

    emit sigTextFormattingChanged(mTextSetting);
}

void TextFormattingToolBar::slotSetTextHorizontalAlign()
{
    QAction *action = (QAction*)this->sender();

    if(action->objectName() == "AlignLeft")
    {
        mAlignLeft->setChecked(true);
        mAlignCenter->setChecked(false);
        mAlignRight->setChecked(false);

        mTextSetting.mTextAlignFlag = Qt::AlignLeft;
    }
    else if(action->objectName() == "AlignCenter")
    {
        mAlignLeft->setChecked(false);
        mAlignCenter->setChecked(true);
        mAlignRight->setChecked(false);

		mTextSetting.mTextAlignFlag = Qt::AlignHCenter;
    }
    else if(action->objectName() == "AlignRight")
    {
        mAlignLeft->setChecked(false);
        mAlignCenter->setChecked(false);
        mAlignRight->setChecked(true);

		mTextSetting.mTextAlignFlag = Qt::AlignRight;
    }


    emit sigTextFormattingChanged(mTextSetting);
}

void TextFormattingToolBar::slotSetTextBIU(bool b)
{
    QAction *action = (QAction*)this->sender();

    if(action->objectName() == tr("Bold"))
    {
		mTextSetting.mBold = b;
    }
    else if(action->objectName() == tr("Italic"))
    {
		mTextSetting.mItalic = b;
    }
    else if(action->objectName() == tr("Underline"))
    {
		mTextSetting.mUnderline = b;
    }

	TextFormattingSetting newSetting(mTextSetting);

    emit sigTextFormattingChanged(mTextSetting);
}
