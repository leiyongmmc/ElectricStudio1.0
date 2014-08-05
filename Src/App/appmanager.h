#ifndef APP_H
#define APP_H

#include <QObject>
#include <QFile>
#include <QSize>

// scene mode for interactive 
enum SceneMode
{
    SceneMode_Select,    // select mode
    SceneMode_Connector, // connect mode
    SceneMode_Cnt 
};

// grid style for draw scene background
enum GridStyle
{
    GridStyle_Line,          // line
    GridStyle_Intersection,  // intersection dot

    GridStyle_Cnt
};

class AppManager : public QObject
{
    Q_OBJECT
public:
    static AppManager* getAppManager();

    // app name

    // read config file
    void readConfig(const QString& file);
    // save config file
    void saveConfig(const QString& file);
    // create default config
    void createDefaultConfig();
    // config file
    void setConfigFileName(const QString &name);
    QString getConfigFileName() const;
    // app name
    void setAppName(const QString& name);
    QString getAppName() const;
    void setOpenFileName(const QString& name);
    QString getOpenFileName() const;

    QString getGlobalTitle();

    // open and save
    QFile* getOpenFile(QWidget *parent,const QString &path = QString());
    QFile* getSaveFile(QWidget *parent,const QString &path = QString());
    // scene mode
    void setSceneMode(SceneMode mode);
    SceneMode getSceneMode();

    // default view and scene size
    QRect getScreenRect();
    QSize getSceneSize();
    QSize getViewSize();
protected:
    AppManager(QObject *parent = 0);
private:
    static AppManager *mInstance;
    QString mConfigFileName;

    QString mAppName;
    QString mOpenFileName;

    SceneMode mSceneMode;
    QSize mSceneSize;
    QSize mViewSize;
};

#endif // APP_H
