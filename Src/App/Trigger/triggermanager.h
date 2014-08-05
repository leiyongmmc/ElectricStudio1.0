#ifndef TRIGGERMANAGER_H
#define TRIGGERMANAGER_H

#include <QObject>
#include <QRectF>
class QMainWindow;

class ActionManager;
class ToolbarManager;
class MenuManager;
class FileService;



class TriggerManager : public QObject
{
    Q_OBJECT
public:
    static TriggerManager* sharedTriggerManager();
    static void destroyManager();
    void createMenubarAndToolBar(QMainWindow* parent);
public slots:
    void slotUpdateActionEnableState(int);
    void slotUpateLocationAndSize(QRectF);
	void slotUpdateTextToolbarEnableState(bool);
protected:
    explicit TriggerManager(QObject *parent = 0);
    virtual ~TriggerManager();
public:
    ActionManager *m_ActionManager;
    ToolbarManager *m_ToolbarManager;
    MenuManager *m_MenuManager;
private:
    static TriggerManager *s_SharedTriggerManager;
};

#endif // TRIGGERMANAGER_H
