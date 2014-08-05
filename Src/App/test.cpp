
#include "svgnodecontainer.h"

#include "appglobal.h"
#include "idevicetypeservice.h"
#include "isvgservice.h"
void test(){
	QList<QPointF> list1;
	list1.append(QPointF(1,1));

	QList<QPointF> list2 = list1;

	list2.replace(0, QPointF(3,3));

	const IDeviceTypeService &ser = AppGlobal::instance().serviceFactory().createDeviceTypeService();
	
	QList<QSharedPointer<DeviceType>> list = ser.List();

	const ISvgService &svgService = AppGlobal::instance().serviceFactory().createSvgService();
	svgService.create(SvgType::SVG_POLYLINE, NULL);
}
