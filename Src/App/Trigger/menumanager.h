#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <QObject>

class QMainWindow;
class QMenu;
class QMenuBar;
class QAction;

class MenuManager : public QObject
{
    Q_OBJECT
public:
    enum GraphicsSceneContextMenuType
    {
      NoContextMenu,
      SceneContextMenu,
      ItemContextMenu,
      ItemGroupContextMenu
    };
    static MenuManager* sharedMenuManager();
    static void destroyManager();
    virtual void createMenubar(QMainWindow *parent);
    QMenu* getGraphicsSceneContextMenu(GraphicsSceneContextMenuType type);
    void setGraphicsSceneContextMenuType(GraphicsSceneContextMenuType type = SceneContextMenu);
    GraphicsSceneContextMenuType getGraphicsSceneContextMenuType();
protected:
    explicit MenuManager(QObject *parent = 0);
    virtual ~MenuManager();
private slots:
    void slotZoomIn(QAction*);
    void slotZoomOut(QAction*);
    void slotRotate(QAction*);
signals:
    void sigZoomIn(float);
    void sigZoomOut(float);
    void sigRotatePara(int);
public:
    QMenuBar *m_Menubar;
    QMenu *m_MenuFile;
    QMenu *m_MenuImport;
    QMenu *m_MenuEdit;
    QMenu *m_MenuView;
    QMenu *m_MenuToolbars;
    QMenu *m_MenuPanes;
    QMenu *m_MenuArrange;
    QMenu *m_MenuAlign;
    QMenu *m_MenuDistribute;
    QMenu *m_MenuGrid;
    QMenu *m_MenuTools;

    // context menu
    QMenu *m_SceneContextMenu;
    QMenu *m_ItemContextMenu;
    QMenu *m_ZoomIn;
    QMenu *m_ZoomOut;
    QMenu *m_Rotate;
    QMenu *m_ItemGroupContextMenu;

    // tree context menu
    QMenu *m_ResourceContextMenu;
private:
    static MenuManager *s_SharedMenuManager;

    GraphicsSceneContextMenuType m_ContextMenuType;
};

#endif // MENUMANAGER_H
