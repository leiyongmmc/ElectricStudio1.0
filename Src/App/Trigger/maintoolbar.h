#ifndef MAINTOOLBAR_H
#define MAINTOOLBAR_H

#include "toolbar.h"

class QAction;

class MainToolBar : public ToolBar
{
    Q_OBJECT
public:
    MainToolBar(const QString &name,QWidget *parent = 0);
private:
    virtual void createToolbar();
    void createConnect();
};

#endif // MAINTOOLBAR_H
