#ifndef IFILESERVICEFACTORY_H
#define IFILESERVICEFACTORY_H
#include "iservicefactory.h"
#include "isvgservice.h"
#include "idevicetypeservice.h"
#include "io_global.h"
class IOSHARED_EXPORT FileServiceFactory : public IServiceFactory
{
public:
	static FileServiceFactory& instance()
	{
		static FileServiceFactory  ins;
		return ins;
	}
private:
	FileServiceFactory() {};
	FileServiceFactory(const FileServiceFactory&);
	void operator=(const FileServiceFactory &);
public:

	virtual const ISvgService & createSvgService() const;

	virtual const IDeviceTypeService & createDeviceTypeService() const;
};

#endif // IFILESERVICEFACTORY_H
