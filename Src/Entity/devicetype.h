#ifndef DEVICETYPE_H
#define DEVICETYPE_H
#include <QObject>
#include "entity_global.h"
class ENTITYSHARED_EXPORT DeviceType : public QObject
{
public:
	DeviceType(int id,QString name,QObject *parent = 0);

	~DeviceType();
	int id(){ return m_id; }

	QString name(){ return m_name; }

private:
	int m_id;
	QString m_name;
};

#endif // DEVICETYPE_H
