#ifndef GRAPHPRIMITIVEPROP_H
#define GRAPHPRIMITIVEPROP_H
#include <QObject>
#include <QStringList>
#include <qvariant.h>
#include "entity_global.h"

class ENTITYSHARED_EXPORT GraphPrimitiveProp
{
public:
    typedef enum
	{
        STRING,
        INT,
        FLOAT,
		DEVICETYPE= 99
    } PropType;

    static void getPropNames(QStringList &names);

    GraphPrimitiveProp();

    GraphPrimitiveProp(const QString& name, PropType type, QVariant defaultValue);

    GraphPrimitiveProp(const QString& name, PropType type, QVariant defaultValue, QVariant value);

    void setName(const QString& name)
    {
        m_name = name;
    }
	QString name() const{
		return m_name;
	}

    void setType(PropType type)
    {
        m_type = type;
    }

	PropType type() const{
		return m_type;
	}

	QVariant defaultValue() const{
		return m_defaultValue;
	}
    void setValue(QVariant value)
    {
        m_value = value;
    }
	QVariant value() const{
		return m_value;
	}
    friend ENTITYSHARED_EXPORT int operator == (const GraphPrimitiveProp &left, const GraphPrimitiveProp &right);

private:

    QString  m_name;
    PropType m_type;
    const QVariant m_defaultValue;
    QVariant m_value;
};

#endif // GRAPHPRIMITIVEPROP_H
