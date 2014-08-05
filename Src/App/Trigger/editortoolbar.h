#ifndef EDITORTOOLBAR_H
#define EDITORTOOLBAR_H

#include "toolbar.h"
#include "../appmanager.h"

class QComboBox;
class QAction;
class QToolButton;

class EditorToolBar : public ToolBar
{
    Q_OBJECT
public:
    EditorToolBar(const QString &name,QWidget *parent = 0);
private:
    virtual void createToolbar();
    void createConnect();
signals:
    void sigZoomPercentChanged(QString);
    void sigSceneModeChanged(SceneMode);
private slots:
    void slotHandleActrionTriggered(QAction*);
private:
    QComboBox *mZoom;
    // select mode
    QAction *mSelectMode;
    // connect mode
    QAction *mConnectorMode;
};

#endif // EDITORTOOLBAR_H
