#include "resourcelibrary.h"

#include "svgitem.h"


ResourceLibrary::ResourceLibrary(const QString &name)
{
    mName = name;
    mItems = new QList<SvgItem*>();
    mItems->clear();
}

QString ResourceLibrary::getName() const
{
    return mName;
}

void ResourceLibrary::setName(const QString &name)
{
    if(mName != name)
        mName = name;
}


QList<SvgItem*>* ResourceLibrary::getItems()
{
    return mItems;
}
