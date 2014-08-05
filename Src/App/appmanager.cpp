#include "appmanager.h"

#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>

AppManager* AppManager::mInstance = NULL;

AppManager* AppManager::getAppManager()
{
    if(!mInstance)
        mInstance = new AppManager();

    return mInstance;
}

AppManager::AppManager(QObject *parent)  :
    QObject(parent)
{
    mConfigFileName = QObject::tr("AppConfig");
    mAppName = QObject::tr("Eletric Svg 1.0.0");
    mOpenFileName = QObject::tr("Unname");

    mSceneMode = SceneMode_Select;

    //QRect rect = this->getScreenRect();
	QRect rect = QRect(0, 0, 500, 500);
	mSceneSize = QSize(rect.width(),rect.height());
    mViewSize  = QSize(rect.width(),rect.height());
}


//
void AppManager::readConfig(const QString &file)
{}

void AppManager::saveConfig(const QString &file)
{}

void AppManager::createDefaultConfig()
{

}

void AppManager::setConfigFileName(const QString &name)
{
    this->mConfigFileName = name;
}

QString AppManager::getConfigFileName() const
{
    return this->mConfigFileName;
}

void AppManager::setAppName(const QString &name)
{
    mAppName = name;
}

QString AppManager::getAppName() const
{
    return mAppName;
}

void AppManager::setOpenFileName(const QString &name)
{
    mOpenFileName = name;
}

QString AppManager::getOpenFileName() const
{
    return mOpenFileName;
}

QString AppManager::getGlobalTitle()
{
    return this->mOpenFileName + "-" + this->mAppName;
}

QFile* AppManager::getOpenFile(QWidget *parent,const QString &path)
{
    QString fileName;
    if (path.isNull())
    {
        fileName = QFileDialog::getOpenFileName(parent
                                                , QObject::tr("Open SVG File")
                                                , QApplication::applicationDirPath()
                                                , QObject::tr("SVG files (*.svg *.svgz *.svg.gz)"));
    }
    else
    {
        fileName = path;
    }

    if(!fileName.isEmpty())
    {
        QFile *file = new QFile(fileName);
        if(!file->exists())
        {
            QMessageBox::critical(parent,QObject::tr("Open SVG File"),QObject::tr("Could not open file"));
            return NULL;
        }

        // set open file name
        QFileInfo info(fileName);
        this->mOpenFileName = info.fileName();

        return file;
    }

    return NULL;
}

QFile* AppManager::getSaveFile(QWidget *parent,const QString &path)
{
    QString fileName;
    if (path.isNull())
    {
        fileName = QFileDialog::getSaveFileName(parent
                                                , QObject::tr("Save SVG File")
                                                , QApplication::applicationDirPath()
                                                , QObject::tr("SVG files (*.svg *.svgz *.svg.gz)"));
    }
    else
    {
        fileName = path;
    }

    if(!fileName.isEmpty())
    {
        QFile *file = new QFile(fileName);
        if(!file->exists())
        {
            // do nothing
        }

        return file;
    }

    return NULL;
}

QRect AppManager::getScreenRect()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取设备屏幕大小
    return  desktopWidget->screenGeometry();
}

QSize AppManager::getSceneSize()
{
    return mSceneSize;
}

QSize AppManager::getViewSize()
{
    return mViewSize;
}
