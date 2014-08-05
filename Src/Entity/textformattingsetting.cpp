#include "textformattingsetting.h"

TextFormattingSetting::TextFormattingSetting()
{
	mFamily = "Arial";
	mStyle = QFont::StyleNormal;
	mPointSize = 24;
	mBold = false;
	mItalic = false;
	mUnderline = false;
    mTextAlignFlag = Qt::AlignCenter;
    mTextColor = Qt::black;
}

TextFormattingSetting::TextFormattingSetting(const TextFormattingSetting &other)
{
	this->mFamily = other.mFamily;
	this->mStyle = other.mStyle;
	this->mPointSize = other.mPointSize;
	this->mBold = other.mBold;
	this->mItalic = other.mItalic;
	this->mUnderline = other.mUnderline;
    this->mTextAlignFlag = other.mTextAlignFlag;
    this->mTextColor = other.mTextColor;
}