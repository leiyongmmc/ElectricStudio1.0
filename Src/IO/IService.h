#ifndef ISERVICE_H
#define ISERVICE_H

#include "io_global.h"
#include "QObject"
#include <QSharedPointer>
template<class T>
class  IOSHARED_EXPORT IService
{
public:

	virtual QList<QSharedPointer<T>> List()const = 0;

	virtual T *Get(QString id, QObject *parent = NULL)const = 0;

	virtual void SaveOrUpdate(const T *obj, QString path = "")const = 0;

};


#endif // ISERVICE_H
