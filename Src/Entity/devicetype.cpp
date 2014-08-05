#include "devicetype.h"

DeviceType::DeviceType(int id, QString name, QObject *parent)
	:m_id(id),m_name(name),  QObject(parent)
{
}

DeviceType::~DeviceType()
{
}