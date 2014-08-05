#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>
#include <QAction>
#include <QApplication>

class QMainWindow;

class ActionManager : public QObject
{
    Q_OBJECT
public:
    static ActionManager* sharedActionManager();
    static void destroyManager();
    virtual void createActions(QMainWindow *parent);
    void resetEnableState();
protected:
    explicit ActionManager(QObject *parent = 0);
    virtual ~ActionManager();
private slots:
    void slotSetResourceActionsState(int);
    void slotResetPanes();
    void slotShowOptionsWidget();
public:
    //
    QAction *m_ActionNew;
    QAction *m_ActionOpen;
    QAction *m_ActionSave;
    QAction *m_ActionSaveAs;
    QAction *m_ActionImportFile;
    QAction *m_ActionImportFolder;
    QAction *m_ActionExit;

    //
    QAction *m_ActionRedo;
    QAction *m_ActionUndo;
    QAction *m_ActionCut;
    QAction *m_ActionCopy;
    QAction *m_ActionPaste;
    QAction *m_ActionFind;
    QAction *m_ActionReplace;
    QAction *m_ActionSelectAll;
    QAction *m_ActionDelete;

    //
    QAction *m_ActionMainToolBar;
    QAction *m_ActionEditorToolBar;
    QAction *m_ActionArrangeToolBar;
    QAction *m_ActionShapeFormatToolBar;
    QAction *m_ActionTextFormatToolBar;
    QAction *m_ActionLocationAndSizeToolBar;

    //
    QAction* m_ActionPropertyPane;
    QAction* m_ActionWidgetPane;

    QAction* m_ActionResetView;

    QAction* m_ActionGroup;
    QAction* m_ActionUngroup;
    QAction* m_ActionAlignLeft;
    QAction* m_ActionAlignCenter;
    QAction* m_ActionAlignRight;
    QAction* m_ActionAlignTop;
    QAction* m_ActionAlignMiddle;
    QAction* m_ActionAlignBottom;

    QAction* m_ActionDistributeH;
    QAction* m_ActionDistributeV;

    QAction* m_ActionShowGrid;
    QAction* m_ActionSnaptoGrid;
    QAction* m_ActionGridSetting;

    QAction* m_ActionOptions;

    QAction* m_ActionZoomIn10;
    QAction* m_ActionZoomIn20;
    QAction* m_ActionZoomIn50;
    QAction* m_ActionZoomIn100;

    QAction* m_ActionZoomOut10;
    QAction* m_ActionZoomOut20;
    QAction* m_ActionZoomOut50;
    QAction* m_ActionZoomOut100;

    QAction* m_ActionRotateR90;
    QAction* m_ActionRotateL90;
    QAction* m_ActionRotate180;
    QAction* m_ActionFlipHorizontal;
    QAction* m_ActionFlipVertical;


    QAction* m_actionRefreshrRes;
    QAction* m_ActionDeleteRes;

private:
    static ActionManager* s_SharedActionManager;
};

#endif // ACTIONMANAGER_H
