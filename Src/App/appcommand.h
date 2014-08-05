#ifndef APPCOMMAND_H
#define APPCOMMAND_H

#include <QObject>
#include <QUndoCommand>
#include <QUndoStack>

class QGraphicsScene;
class QGraphicsItem;

class AppCommand : public QObject
{
	Q_OBJECT
public:
	static AppCommand* getAppCommand();
	static void destroyAppCommand();
	QUndoStack* getUndoStack();
protected:
	AppCommand();
	~AppCommand();
private:
	static AppCommand* sAppCommand;
	QUndoStack* mStack;
};

class DeleteCommand : public QUndoCommand
{
public:
	DeleteCommand(QGraphicsScene *scene, QList<QGraphicsItem*> items,QUndoCommand *parent = 0);
	virtual void undo();
	virtual void redo();
private:
	QGraphicsScene* mScene;
	QList<QGraphicsItem*> mItems;
};

class AddCommand: public QUndoCommand
{
public:
    AddCommand(QGraphicsScene *scene, QGraphicsItem* item,QUndoCommand *parent = 0);
    virtual void undo();
    virtual void redo();
private:
    QGraphicsScene* mScene;
    QGraphicsItem* mItem;
};

#endif // APPCOMMAND_H
