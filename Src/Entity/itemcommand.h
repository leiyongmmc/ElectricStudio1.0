#ifndef ITEMCOMMAND_H
#define ITEMCOMMAND_H

#include "entity_global.h"
#include "textformattingsetting.h"

#include <QObject>
#include <QColor>
#include <QUndoCommand>
#include <QUndoStack>
#include <QRectF>

class KUnitItem;
class SvgNode;
class SvgTextElement;

class ENTITYSHARED_EXPORT ItemCommand : public QObject
{
    Q_OBJECT
public:
    static ItemCommand* getItemCommand();
    static void destroyItemCommand();
    QUndoStack* getUndoStack();
public:
    ItemCommand();
    ~ItemCommand();
private:
    static ItemCommand* sItemCommand;
    QUndoStack* mStack;
};

class ENTITYSHARED_EXPORT AngleCommand: public QUndoCommand
{
public:
    AngleCommand(KUnitItem *item,qreal angle,QUndoCommand*parent = 0);
    virtual void undo();
    virtual void redo();
private:
    KUnitItem* mItem;
    qreal mAngle;
};

class ENTITYSHARED_EXPORT ShapeFormattingCommand : public QUndoCommand
{
public:
    ShapeFormattingCommand(SvgNode *item
                           , QColor clineColor
                           , int clineWidth
                           , QColor cfillColor
                           , QColor plineColor
                           , int plineWidth
                           , QColor pfillColor
                           , QUndoCommand*parent = 0);
    virtual void undo();
    virtual void redo();
private:
    SvgNode* mNode;
    // current color
    QColor mclineColor;
    int mclineWidth;
    QColor mcfillColor;
    // old color
    QColor mplineColor;
    int mplineWidth;
    QColor mpfillColor;
};

class ENTITYSHARED_EXPORT TextFormattingCommand : public QUndoCommand
{
public:
    TextFormattingCommand(SvgTextElement *ItemCommand,
                          TextFormattingSetting c,
                          TextFormattingSetting p,
                          QUndoCommand*parent = 0);
    virtual void undo();
    virtual void redo();
private:
    SvgTextElement* mNode;
    TextFormattingSetting mCurrentSetting;
    TextFormattingSetting mPreviousSetting;
};

class ENTITYSHARED_EXPORT ResizeCommand: public QUndoCommand
{
public:
    ResizeCommand(KUnitItem *item, QRectF preRect, QRectF curRect, QUndoCommand*parent = 0);
    virtual void undo();
    virtual void redo();
private:
    KUnitItem* mItem;
    QRectF mPreRect;
    QRectF mCurRect;
};


#endif // ITEMCOMMAND_H
