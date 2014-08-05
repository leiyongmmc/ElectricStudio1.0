#include "svgitem.h"


#include <QDebug>

SvgItem::SvgItem(const QString &name, const QString& filePath,const QIcon &icon)
{
    this->mName = name;
    this->mAbsFilePath = filePath;
    this->mIcon = icon;
}

SvgItem::SvgItem(const QString &name,const QString& filePath,const QString &iconfileName)
{
    this->mName = name;
    this->mAbsFilePath = filePath;
    this->mIcon = QIcon(iconfileName);
}

void SvgItem::setName(const QString &name)
{
    this->mName = name;
}

QString SvgItem::getName() const
{
    return mName;
}

void SvgItem::setIcon(const QString &fileName)
{
    mIcon = QIcon(fileName);
}

QIcon& SvgItem::getIcon()
{
    return mIcon;
}

void SvgItem::setAbsolutePath(const QString &filePath)
{
    mAbsFilePath = filePath;
}

QString SvgItem::getAbsolutePath() const
{
    qDebug()<<"mFilePath" <<mAbsFilePath;
    return mAbsFilePath;
}
