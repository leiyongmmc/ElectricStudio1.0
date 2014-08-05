#include "fileservice.h"

#include <QMessageBox>

#include "../appmanager.h"
#include "../graphicsscene.h"

FileService *FileService::s_SharedFileService = NULL;

FileService *FileService::sharedFileService()
{
    if(!s_SharedFileService)
        s_SharedFileService = new FileService();

    return s_SharedFileService;
}

FileService::FileService(QObject *parent) :
    QObject(parent)
{

}

bool FileService::vaildFile(QString filepath)
{
    if(filepath.isNull() || filepath== "" || filepath.isEmpty())
        return false;

    return true;
}

int FileService::saveInfo(GraphicsScene *scene,QWidget *parent)
{
    if(!scene)
        return -1;

    int cnt = scene->getDropIntoSceneItemCnt();
    bool isOnlySceneNode = scene->isOnlySceneNode();
    // 是否只有一个父节点
    if(isOnlySceneNode)
    {
        return -1;
    }
    // 存在子节点
    // 1. 打开的文件
    // 2. 拖入或创建的polygonline
    else
    {
        // 判断是否拖入或创建了polygonline
        if(cnt > 0)
        {
            int ret = QMessageBox::warning(parent
                                           , AppManager::getAppManager()->getAppName()
                                           , QObject::tr("Would you like to save the current scene?")
                                           , QMessageBox::Yes | QMessageBox::No| QMessageBox::Cancel);
            if(ret == QMessageBox::Yes)
            {
                if(this->vaildFile(scene->getOpenedFileName()))
                {
                    scene->saveSceneNode();
                }
                else
                {
                    scene->saveSceneNode(AppManager::getAppManager()->getSaveFile(0));
                }
            }
        }
        // 打开的文件
        else
        {
            // 直接保存- to do 判断打开的文件是否改变
            if(this->vaildFile(scene->getOpenedFileName()))
            {
                scene->saveSceneNode();
            }
        }
    }

    return -1;
}

void FileService::saveInfoWithoutQues(GraphicsScene *scene)
{
    if(!scene)
        return;

    // 是否为空
    if(scene->isOnlySceneNode())
    {
        QMessageBox::warning(0
                             , AppManager::getAppManager()->getAppName()
                             , QObject::tr("Current scene is null"));
    }
    // 只要场景不为空就可以保存
    else
    {
        // 有打开的文件直接覆盖以前的文件
        if(this->vaildFile(scene->getOpenedFileName()))
        {
            scene->saveSceneNode();
        }
        // 没有则打开选择存储路径
        else
        {
            QFile *file = AppManager::getAppManager()->getSaveFile(0);
            if(file)
            {
                scene->setOpenedFileName(file->fileName());
                scene->saveSceneNode(file);
            }
        }
    }
}

void FileService::saveAsInfo(GraphicsScene *scene)
{
    if(!scene)
        return;

    // 只要场景不为空就可以另存为
    bool isOnlySceneNode = scene->isOnlySceneNode();
    if(isOnlySceneNode)
    {
        QMessageBox::warning(0
                             , AppManager::getAppManager()->getAppName()
                             , QObject::tr("Current scene is null"));
    }
    else
    {
        scene->saveSceneNode(AppManager::getAppManager()->getSaveFile(0));
    }
}

