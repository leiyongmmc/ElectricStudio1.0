#ifndef TOOLBARMANAGER_H
#define TOOLBARMANAGER_H

#include <QObject>
#include <QToolBar>
#include <QApplication>

class QAction;
class QMainWindow;

class ToolBar;
class MainToolBar;
class EditorToolBar;
class ArrangeToolBar;
class TextFormattingToolBar;
class ShapeFormattingToolBar;
class LocationAndSizeToolBar;

class ToolbarManager : public QObject
{
    Q_OBJECT
public:
    static ToolbarManager* sharedToolbarManager();
    static void destroyManager();
    virtual void createToolbars(QMainWindow *parent);
public slots:
    void slotSetToolbarsVisible(QAction*);
protected:
    explicit ToolbarManager(QObject *parent = 0);
    virtual ~ToolbarManager();
private:
    void createConnect();
public:
    MainToolBar             *m_MainToolBar;
    EditorToolBar           *m_EditorToolBar;
    ArrangeToolBar          *m_ArrangeToolBar;
    TextFormattingToolBar   *m_TextFormattingToolBar;
    ShapeFormattingToolBar  *m_ShapeFormattingToolBar;
    LocationAndSizeToolBar  *m_LocationAndSizeToolBar;

    QList<ToolBar*> m_Toolbars;
private:
    static ToolbarManager *s_sharedToolbarManager;
};

#endif // TOOLBARMANAGER_H
