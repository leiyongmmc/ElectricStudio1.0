#ifndef MENUBAR_H
#define MENUBAR_H

#include <QToolBar>

class ToolBar :public QToolBar
{
    Q_OBJECT
public:
    ToolBar(const QString& name,QWidget *parent = 0);
    // object name
    QString getToolBarName();
protected:
    virtual void createToolbar() = 0;
protected:
    QString mName;
};

#endif // MENUBAR_H
