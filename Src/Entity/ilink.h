
#ifndef ILINK_H
#define ILINK_H

#include "entity_global.h"
#include <QPointF>
#include <QPointer>
#include <QtXml/QtXml>
class SvgNode;

typedef struct 
{
	QPointer<SvgNode> node;
	int tiePointIdx;
	bool isNull()const{
		return node.isNull();
	}
} LineEnd;

class ENTITYSHARED_EXPORT ILink
{
public:
	void endPointPosFix();

	void fromXml(const QDomElement &xml);
	void toXml(QDomElement &parent) const;

	void createRelations(SvgNode *top);

	void tryConnecte(SvgNode* top,const QPointF & p, bool isStart);
	void onEndMove(bool isStart);
	void onEndResize(bool isStart);
	void onEndRotate(bool isStart);
	virtual void replaceWithScenePoint(bool isStart, QPointF newPoint) = 0;
	virtual QUuid getId() const = 0;
	virtual bool twoEndpointsLinked() = 0;
protected:
	void endPointChanged(bool isStart);

	QDomNode m_fromDom;
	QDomNode m_toDom;
	LineEnd m_fromEnd;
	LineEnd m_toEnd;
};

#endif // ILINK_H
