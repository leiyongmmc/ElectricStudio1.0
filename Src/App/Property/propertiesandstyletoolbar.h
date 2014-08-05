#ifndef PROPERTIESANDSTYLETOOLBAR_H
#define PROPERTIESANDSTYLETOOLBAR_H

#include "../Trigger/toolbar.h"

class QToolButton;

class PropertiesAndStyleToolBar: public ToolBar
{
    Q_OBJECT
public:
    PropertiesAndStyleToolBar(const QString &name, QWidget *parent = 0);
private:
    void createToolbar();
    void createConnect();
signals:
    void sigAddParamter();
    void sigRemoveParamter();
    void sigClearParameter();
    void sigSubumit();
private:
    QToolButton *mAddBtn;
    QToolButton *mRemoveBtn;
    QToolButton *mClearBtn;
    QToolButton *mSubmitBtn;
};

#endif // PROPERTIESANDSTYLETOOLBAR_H
