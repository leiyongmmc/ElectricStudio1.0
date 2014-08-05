#ifndef DEVICETYPESERVICE_H
#define DEVICETYPESERVICE_H

#include "io_global.h"
#include "idevicetypeservice.h"
#include <QString>

class  IOSHARED_EXPORT FileDeviceTypeService : public IDeviceTypeService
{
public:
    FileDeviceTypeService();

	virtual QList<QSharedPointer<DeviceType>> List() const;

	virtual DeviceType *Get(QString id, QObject *parent = NULL) const;

	virtual void SaveOrUpdate(const DeviceType *obj, QString path = "") const;
};

#endif // DEVICETYPESERVICE_H
