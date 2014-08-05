#include "appcommand.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

#include "svgnode.h"

AppCommand* AppCommand::sAppCommand = NULL;
AppCommand* AppCommand::getAppCommand()
{
    if (!sAppCommand)
    {
        sAppCommand = new AppCommand();
    }
    return sAppCommand;
}

void AppCommand::destroyAppCommand()
{
    delete sAppCommand;
    sAppCommand = NULL;
}

QUndoStack* AppCommand::getUndoStack()
{
    return mStack;
}

AppCommand::AppCommand()
{
    mStack = new QUndoStack();
}

AppCommand::~AppCommand()
{
    delete mStack;
    mStack = NULL;
}

DeleteCommand::DeleteCommand(QGraphicsScene *scene, QList<QGraphicsItem*> items, QUndoCommand *parent) :
    QUndoCommand(parent),
    mScene(scene)
{
	for each (QGraphicsItem *item in items)
	{
		mItems.append(item);
	}
}

void DeleteCommand::undo()
{
	if (mScene)
	{
		for each (QGraphicsItem *item in mItems)
		{
			SvgNode *node = dynamic_cast<SvgNode *>(item);
			if (node)
			{
				SvgNode *parent = node->parentNode();
				if (parent)
					parent->add(node);

				mScene->addItem(node);
			}
		}
	}
}

void DeleteCommand::redo()
{
	if (mScene)
	{
		for each (QGraphicsItem *item in mItems)
		{
			SvgNode *node = dynamic_cast<SvgNode *>(item);
			if (node)
			{
				SvgNode *parent = node->parentNode();
				if (parent)
				{
					parent->remove(node);
				}

				mScene->removeItem(node);
			}
		}
	}
}

AddCommand::AddCommand(QGraphicsScene *scene, QGraphicsItem* item, QUndoCommand *parent) :
    QUndoCommand(parent),
    mScene(scene),
    mItem(item)
{

}

void AddCommand::undo()
{
    if(mScene)
        mScene->removeItem(mItem);
}

void AddCommand::redo()
{

    if(mScene)
        mScene->addItem(mItem);
}
