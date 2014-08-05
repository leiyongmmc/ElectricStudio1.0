#ifndef RESOURCELIBRARY_H
#define RESOURCELIBRARY_H

#include <QObject>

class SvgItem;

// 资源包
class ResourceLibrary
{
public:
    ResourceLibrary(const QString &name = "Default");
    // 包名
    void setName(const QString &name);
    QString getName() const;
    // 得到所有资源节点
    QList<SvgItem*>* getItems();
private:
    // 包名
    QString mName;
    // 所有节点
    QList<SvgItem*>* mItems;
};

#endif // RESOURCELIBRARY_H
