#ifndef ARRANGETOOLBAR_H
#define ARRANGETOOLBAR_H

#include "toolbar.h"

class QToolButton;

class ArrangeToolBar : public ToolBar
{
    Q_OBJECT
public:
    ArrangeToolBar(const QString &name,QWidget *parent = 0);
private:
    virtual void createToolbar();
    void createConnect();
};

#endif // ARRANGETOOLBAR_H
