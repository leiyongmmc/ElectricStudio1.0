#ifndef CONNECTION_H
#define CONNECTION_H
#include <QPointer>
#include <QPointF>
#include "entity_global.h"
class ILink;
class SvgNode;
class ENTITYSHARED_EXPORT connection
{
public:
	connection(ILink *line, bool isStart);

	ILink *line() const{
		return this->m_line;
	}

	bool isStart() const { return m_isStart; }

	friend ENTITYSHARED_EXPORT int operator == (const connection &left, const connection &right);
private:
	ILink *m_line;

	bool m_isStart;
};

#endif // CONNECTION_H
