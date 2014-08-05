#include "fileservicefactory.h"
#include "filesvgservice.h"
#include "filedevicetypeservice.h"


const ISvgService & FileServiceFactory::createSvgService() const{
	static FileSvgService ins;
	return ins;
}

const IDeviceTypeService & FileServiceFactory::createDeviceTypeService() const{
	static FileDeviceTypeService ins;
    return ins;
}
