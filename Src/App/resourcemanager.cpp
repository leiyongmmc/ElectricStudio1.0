#include "resourcemanager.h"

#include <QApplication>
#include <QDirIterator>
#include <QDebug>

#include "svgitem.h"
#include "resourcelibrary.h"



ResourceManager* ResourceManager::mInstance = NULL;

ResourceManager* ResourceManager::getManager()
{
    if(!mInstance)
        mInstance = new ResourceManager();

    return mInstance;
}

SvgItem* ResourceManager::importFile(const QString &folder, const QString &filepath)
{
    for(int i = 0; i < mResLibs->count(); i++)
    {
        ResourceLibrary *lib = mResLibs->at(i);
        if(lib)
        {
            if(lib->getName() == folder)
            {
                QFileInfo info(filepath);
                QDir appDir(QApplication::applicationDirPath());
                QDir svgLibsDir(appDir.cdUp() + "/SvgLibs");
                QString newpath = svgLibsDir.absolutePath()+"/"+folder+"/"+info.fileName();
				QFile file(filepath);
				
				if (file.exists() && file.copy(newpath))
				{
					return NULL;
				}

                QPixmap objPixmap(filepath);
                SvgItem *item = new SvgItem(info.fileName().left(info.fileName().lastIndexOf("."))
                                            , newpath
                                            , QIcon(objPixmap.scaled(QSize(500,500)))
                                            );

                lib->getItems()->append(item);

                return item;
            }
        }
    }

    return NULL;
}

ResourceLibrary* ResourceManager::importFolder(const QString &folderpath)
{
    QFileInfo info(folderpath);
    ResourceLibrary *lib = NULL;
    for(int i = 0; i < mResLibs->count(); i++)
    {
        if(mResLibs->at(i)->getName() == info.fileName())
        {
            lib = mResLibs->at(i);
        }
    }

    if(lib == NULL)
    {
        lib = new ResourceLibrary(info.fileName());

        QDir appDir(QApplication::applicationDirPath());
        QDir svgLibsDir(appDir.cdUp() + "/SvgLibs/");
        QDir targetdir(svgLibsDir.absolutePath()+"/"+QObject::tr("%1").arg(info.fileName()));
        if(!targetdir.exists())
        {
            // make dir
            //qDebug()<<"*********88"<<targetdir.absolutePath();
            if(!targetdir.mkdir(targetdir.absolutePath()))
            {
                delete lib;
                lib = NULL;
                return NULL;
            }
        }

        QDir sourceDir(folderpath);

        foreach(QFileInfo info,sourceDir.entryInfoList())
        {
            if(info.isDir())
            {
                continue;
            }
            else
            {
                QString subfilepath = info.filePath();
                if(subfilepath.isEmpty() || subfilepath.isNull() || subfilepath == "")
                    continue;

                if(!QFile::copy(subfilepath,targetdir.filePath(info.fileName())))
                {
                    return NULL;
                }

                QPixmap objPixmap(subfilepath);
                SvgItem *item = new SvgItem(info.fileName().left(info.fileName().lastIndexOf("."))
                                            , targetdir.filePath(info.fileName())
                                            , QIcon(objPixmap.scaled(QSize(500,500)))
                                            );

                lib->getItems()->append(item);
            }
        }


        mResLibs->append(lib);
        return lib;
    }
	else
	{
		QList<SvgItem*>* items = lib->getItems();
		if (!items)
		{
			return NULL;
		}

		QDir sourceDir(folderpath);

		QDir appDir(QApplication::applicationDirPath());
		QDir svgLibsDir(appDir.cdUp() + "/SvgLibs/");
		QDir targetdir(svgLibsDir.absolutePath() + "/" + QObject::tr("%1").arg(info.fileName()));

		foreach(QFileInfo info, sourceDir.entryInfoList())
		{
			if (info.isDir())
			{
				continue;
			}
			else
			{
				QString subfilepath = info.filePath();
				if (subfilepath.isEmpty() || subfilepath.isNull() || subfilepath == "")
					continue;

				bool bExistedItem = false;
				for (int k = 0; k < items->count();k++)
				{
                    if (info.fileName() == items->at(k)->getName())
					{
						bExistedItem = true;
						break;
					}
				}
				if (bExistedItem)
				{
					continue;
				}

				if (!QFile::copy(subfilepath, targetdir.filePath(info.fileName())))
				{
					return NULL;
				}

				QPixmap objPixmap(subfilepath);
				SvgItem *item = new SvgItem(info.fileName().left(info.fileName().lastIndexOf("."))
					, targetdir.filePath(info.fileName())
					, QIcon(objPixmap.scaled(QSize(500, 500)))
					);

                items->append(item);
			}
		}

	}

    return lib;
}

void ResourceManager::addLib(const QString &libname)
{
    ResourceLibrary *lib = new ResourceLibrary(libname);
    mResLibs->append(lib);
}

void ResourceManager::removeLib(const QString &libname)
{
    for(int i = 0; i < mResLibs->count(); i++)
    {
        ResourceLibrary *lib = mResLibs->at(i);
        if(lib)
        {
            if(lib->getName() == libname)
            {
                mResLibs->removeOne(lib);
                delete lib;
                lib = NULL;
            }
        }
    }
}

void ResourceManager::removeItem(const QString& libname,const QString &itemname)
{
    for(int i = 0; i < mResLibs->count(); i++)
    {
        ResourceLibrary *lib = mResLibs->at(i);
        if(lib)
        {
            if(lib->getName() == libname)
            {
                QList<SvgItem*>* items = lib->getItems();
                if(items)
                {
                    for(int j = 0; j < items->count(); j++)
                    {
                        SvgItem *item = items->at(j);
                        if(item->getName() == itemname)
                        {
                            items->removeOne(item);
                            delete item;
                            item = NULL;
                        }
                    }
                }
            }
        }
    }
}

void ResourceManager::removeAll()
{
    // remove all
    for(int i = 0; i < mResLibs->count(); i++)
    {
        ResourceLibrary *lib = mResLibs->at(i);
        if(lib)
        {
            QList<SvgItem*>* items = lib->getItems();
            if(items)
            {
                for(int j = 0; j < items->count(); j++)
                {
                    SvgItem *item = items->at(j);
                    delete item;
                    item = NULL;
                }
                items->clear();
                delete items;
                items = NULL;
            }
            delete lib;
            lib = NULL;
        }
    }

    mResLibs->clear();
}

void ResourceManager::refreshAllResources()
{
    this->removeAll();
    this->initAllResources();
}

void ResourceManager::initAllResources()
{
    QDir appDir(QApplication::applicationDirPath());
    QDir svgLibsDir(appDir.cdUp() + "/SvgLibs");
    qDebug()<<"dir path"<<svgLibsDir.absolutePath();
    // get all childen dir
    foreach(QFileInfo info,svgLibsDir.entryInfoList())
    {
        if(info.isFile())
        {
            continue;
        }
        else
        {
            QString dirName = info.fileName();
            if(dirName =="." || dirName == "..")
                continue;

            ResourceLibrary *lib = NULL;
            bool addLib = false;
            for(int i = 0; i < mResLibs->count(); i++)
            {
                if(mResLibs->at(i)->getName() == dirName)
                {
                    lib = mResLibs->at(i);
                }
            }

            if(lib == NULL)
            {
                lib = new ResourceLibrary(dirName);
                addLib = true;
            }

            QDirIterator dirItr(QString(info.absoluteFilePath())
                                , QDir::Files|QDir::NoSymLinks
                                , QDirIterator::Subdirectories);

            while(dirItr.hasNext())
            {
                QString absfilePath = dirItr.next();
                QPixmap objPixmap(absfilePath);
                QString tmpFilePath(absfilePath);
                QString fileName = tmpFilePath.remove(QString(info.absoluteFilePath()+"/"), Qt::CaseSensitive);
                fileName.truncate(fileName.lastIndexOf("."));
                QIcon icon(objPixmap.scaled(QSize(500,500)));

                SvgItem *svgitem = NULL;
                bool addSvg = false;
                for(int j = 0; j < lib->getItems()->count(); j++)
                {
                    if(lib->getItems()->at(j)->getName() == fileName)
                    {
                        svgitem = lib->getItems()->at(j);
                    }
                }

                if(svgitem == NULL)
                {
                    svgitem = new SvgItem(fileName,absfilePath,icon);
                    addSvg = true;
                }

                if(addSvg)
                    lib->getItems()->append(svgitem);
            }
            if(addLib)
                mResLibs->append(lib);
        }
    }
}


QList<ResourceLibrary*>* ResourceManager::getResLibs()
{
    return mResLibs;
}

void ResourceManager::getAllResLibNames(QList<QString> &names)
{
    names.clear();
    if(mResLibs)
    {
        for(int i = 0; i < mResLibs->count(); i++)
        {
            ResourceLibrary *lib = mResLibs->at(i);
            if(lib)
            {
                names.append(lib->getName());
            }
        }
    }
}

QList<SvgItem*>* ResourceManager::getItems(QString libNames)
{
   if(mResLibs)
   {
       for(int i = 0; i < mResLibs->count(); i++)
       {
           ResourceLibrary *lib = mResLibs->at(i);
           if(lib && lib->getName() == libNames)
           {
               return lib->getItems();
           }
       }
   }

   return NULL;
}

ResourceManager::ResourceManager()
{
    mResLibs = new QList<ResourceLibrary*>();
}
