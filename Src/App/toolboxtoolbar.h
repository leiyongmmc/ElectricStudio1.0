#ifndef TOOLBOXMENUBAR_H
#define TOOLBOXMENUBAR_H

#include "Trigger/toolbar.h"

class QToolButton;

class ToolboxToolBar : public ToolBar
{
    Q_OBJECT
public:
    ToolboxToolBar(const QString& name,QWidget *parent= 0);
public slots:
    void slotSetBtnEnableState(int index);
private:
    virtual void createToolbar();
    void createConnect();
signals:
    void sigFilterLineEditVisible(bool);
private slots:
    void slotSetFindLineEditVisible();
public:
    QToolButton *mImportFileBtn;
    QToolButton *mImportFolderBtn;
    QToolButton *mRefreshBtn;
    QToolButton *mFindBtn;
};

#endif // TOOLBOXMENUBAR_H
