#ifndef ISERVICEFACTORY_H
#define ISERVICEFACTORY_H
#include "io_global.h"
class ISvgService;
class IDeviceTypeService;
class IOSHARED_EXPORT IServiceFactory
{
public:
	virtual const ISvgService & createSvgService() const = 0;

	virtual const IDeviceTypeService & createDeviceTypeService() const  = 0;
};

#endif // ISERVICEFACTORY_H
