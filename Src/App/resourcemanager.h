#ifndef TOOLBOXRESOURCEMANAGER_H
#define TOOLBOXRESOURCEMANAGER_H

#include <QObject>

class SvgItem;
class ResourceLibrary;

class ResourceManager
{
public:
    static ResourceManager* getManager();

    SvgItem *importFile(const QString &folder,const QString& filepath);
    ResourceLibrary* importFolder(const QString &folderpath);


    void addLib(const QString& lib);
    void removeLib(const QString &lib);
    void removeItem(const QString& libname,const QString &item);
    void removeAll();
    void initAllResources();
    void refreshAllResources();

    QList<ResourceLibrary*>* getResLibs();
    QList<SvgItem*>*getItems(QString libNames);
    void getAllResLibNames(QList<QString>&names);
protected:
    ResourceManager();

private:
    static ResourceManager *mInstance;
    QList<ResourceLibrary*>* mResLibs;
};

#endif // TOOLBOXRESOURCEMANAGER_H
