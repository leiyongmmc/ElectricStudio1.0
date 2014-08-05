#include "graphprimitiveprop.h"

void GraphPrimitiveProp::getPropNames(QStringList &names)
{
    names.clear();
    names << "String" << "Int" << "Float";
}

GraphPrimitiveProp::GraphPrimitiveProp()
{}


GraphPrimitiveProp::GraphPrimitiveProp(const QString& name, PropType type, QVariant defaultValue) :
    m_name(name),
    m_type(type),
    m_defaultValue(defaultValue),
    m_value(defaultValue)
{
}

GraphPrimitiveProp::GraphPrimitiveProp(const QString& name, PropType type, QVariant defaultValue, QVariant value) :
    m_name(name),
	m_type(type),
	m_defaultValue(defaultValue),
	m_value(value)
{

}
int operator == (const GraphPrimitiveProp &left, const GraphPrimitiveProp &right){
    return left.m_name == right.m_name;
}
