#ifndef SVGITEM_H
#define SVGITEM_H

#include <QObject>
#include <QIcon>

class SvgItem
{
public:
    SvgItem(const QString &name, const QString& filePath,const QIcon &icon);
    SvgItem(const QString &name,const QString& filePath,const QString &iconfileName="");
    void setName(const QString& name);
    QString getName() const;
    void setIcon(const QString& fileName);
    QIcon& getIcon();
    void setAbsolutePath(const QString&filePath);
    QString getAbsolutePath()const;
private:
    // 节点名
    QString mName;
    QString mAbsFilePath;
    // 节点图标
    QIcon   mIcon;
};

#endif // SVGITEM_H
