#include "connection.h"
#include "svgnode.h"
#include "ilink.h"
connection::connection(ILink *line,  bool isStart)
	: m_line(line),  m_isStart(isStart)
{
}

int operator == (const connection &left, const connection &right){
	return left.m_line == right.m_line && left.m_isStart == right.m_isStart ;
}
