#include "filedevicetypeservice.h"
#include <QCoreApplication>
#include <QFile>
#include <QDomDocument>

FileDeviceTypeService::FileDeviceTypeService()
{
}

QList<QSharedPointer<DeviceType>> FileDeviceTypeService::List()const{
	QList<QSharedPointer<DeviceType>> list;
	QString path = QCoreApplication::applicationDirPath() + "/Data/DeviceType.xml";
	QFile *xmlFile = new QFile(path);

	if (!xmlFile->open(QIODevice::ReadOnly)){
		return list;
	}

	QDomDocument doc;
	if (!doc.setContent(xmlFile)) {
		xmlFile->close();
		return list;
	}
	xmlFile->close();

	QDomElement root = doc.documentElement();
	for (int j = 0; j < root.childNodes().count(); j++){
		QDomElement node = root.childNodes().item(j).toElement();
		int       id = node.attribute("id").toInt();
		QString name = node.attribute("name");
		QSharedPointer<DeviceType> item(new DeviceType(id, name));
		list.append(item);

	}
	
	return list;
}

DeviceType * FileDeviceTypeService::Get(QString id, QObject *parent)const{

	return NULL;
}

void FileDeviceTypeService::SaveOrUpdate(const DeviceType *obj, QString path)const{

}
