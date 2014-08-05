#include "itemcommand.h"

#include "kunititem.h"
#include "svgnode.h"
#include "svgNodeElementImpl/svgtextelement.h"

ItemCommand* ItemCommand::sItemCommand = NULL;
ItemCommand* ItemCommand::getItemCommand()
{
    if(!sItemCommand)
    {
        sItemCommand = new ItemCommand();
    }

    return sItemCommand;
}

void ItemCommand::destroyItemCommand()
{
    delete sItemCommand;
    sItemCommand = NULL;
}

QUndoStack* ItemCommand::getUndoStack()
{
    return mStack;
}


ItemCommand::ItemCommand()
{
    mStack = new QUndoStack();
}

ItemCommand::~ItemCommand()
{
    delete mStack;
    mStack = NULL;
}

AngleCommand::AngleCommand(KUnitItem *item,qreal angle,QUndoCommand*parent):
QUndoCommand(parent),
  mItem(item),
  mAngle(angle)
{

}

void AngleCommand::redo()
{
    if(mItem)
    {
        mItem->setAngle(mItem->m_frame.center(),mAngle);
    }
}

void AngleCommand::undo()
{
    if(mItem)
    {
        mItem->setAngle(mItem->m_frame.center(),-mAngle);
    }
}

ShapeFormattingCommand::ShapeFormattingCommand(SvgNode *item
                                               , QColor clineColor
                                               , int clineWidth
                                               , QColor cfillColor
                                               , QColor plineColor
                                               , int plineWidth
                                               , QColor pfillColor
                                               , QUndoCommand *parent):
QUndoCommand(parent),
  mNode(item),
  mclineColor(clineColor),
  mclineWidth(clineWidth),
  mcfillColor(cfillColor),
  mplineColor(plineColor),
  mplineWidth(plineWidth),
  mpfillColor(pfillColor)
{

}

void ShapeFormattingCommand::redo()
{
    if(mNode)
    {
       mNode->setStroke(mclineColor);
       mNode->setStrokeWidth(mclineWidth);
       mNode->setFill(mcfillColor);
    }
}

void ShapeFormattingCommand::undo()
{
    if(mNode)
    {
       mNode->setStroke(mplineColor);
       mNode->setStrokeWidth(mplineWidth);
       mNode->setFill(mpfillColor);
    }
}

TextFormattingCommand::TextFormattingCommand(SvgTextElement *node, TextFormattingSetting c, TextFormattingSetting p, QUndoCommand *parent) :
    QUndoCommand(parent),
    mNode(node),
    mCurrentSetting(c),
    mPreviousSetting(p)
{

}

void TextFormattingCommand::redo()
{
    if(mNode)
    {
        mNode->setFontFamily(mCurrentSetting.mFamily);
        mNode->setFontSize(mCurrentSetting.mPointSize);
        mNode->setFontStyle(mCurrentSetting.mStyle);
        mNode->setBold(mCurrentSetting.mBold);
        mNode->setItalic(mCurrentSetting.mItalic);
        mNode->setUnderline(mCurrentSetting.mUnderline);
        mNode->setAlignFlag(mCurrentSetting.mTextAlignFlag);
        mNode->setTextColor(mCurrentSetting.mTextColor);
    }
}

void TextFormattingCommand::undo()
{
    if(mNode)
    {
        mNode->setFontFamily(mPreviousSetting.mFamily);
        mNode->setFontSize(mPreviousSetting.mPointSize);
        mNode->setFontStyle(mPreviousSetting.mStyle);
        mNode->setBold(mPreviousSetting.mBold);
        mNode->setItalic(mPreviousSetting.mItalic);
        mNode->setUnderline(mPreviousSetting.mUnderline);
        mNode->setAlignFlag(mPreviousSetting.mTextAlignFlag);
        mNode->setTextColor(mPreviousSetting.mTextColor);
    }
}

ResizeCommand::ResizeCommand(KUnitItem *item,QRectF preRect,QRectF curRect,QUndoCommand*parent):
QUndoCommand(parent),
  mItem(item),
  mPreRect(preRect),
  mCurRect(curRect)
{

}

void ResizeCommand::redo()
{
    if(mItem)
    {
        mItem->onResize(mCurRect);
    }
}

void ResizeCommand::undo()
{
    if(mItem)
    {
        mItem->onResize(mPreRect);
    }
}
