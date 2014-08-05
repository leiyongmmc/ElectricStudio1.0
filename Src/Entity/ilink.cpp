#include "ilink.h"
#include "svgnode.h"
#include <QtXml/QtXml>

void ILink::endPointPosFix(){
	if (!m_fromEnd.isNull())
	{
		QPointF p = m_fromEnd.node->tiePoints().at(m_fromEnd.tiePointIdx);
		p = m_fromEnd.node->mapToScene(p);
		this->replaceWithScenePoint(true, p);
	}
	if (!m_toEnd.isNull())
	{
		QPointF p = m_toEnd.node->tiePoints().at(m_toEnd.tiePointIdx);
		p = m_toEnd.node->mapToScene(p);
		this->replaceWithScenePoint(false, p);
	}
}

void ILink::fromXml(const QDomElement &xml){
	QDomNodeList subs = xml.childNodes();
	for (int i = 0; i < subs.count(); i++){
		QDomNode xmlNode = subs.item(i);
		if (xmlNode.nodeName() == "from")
		{
			m_fromDom = xmlNode.cloneNode(true);
		}
		if (xmlNode.nodeName() == "to")
		{
			m_toDom = xmlNode.cloneNode(true);
		}
	}
}

void ILink::toXml(QDomElement &parent) const{
	if (!m_fromEnd.isNull())
	{
		QDomElement from = parent.ownerDocument().createElement("from");
		from.setAttribute("node", m_fromEnd.node->id().toString());
		from.setAttribute("pointIdx", m_fromEnd.tiePointIdx);
		parent.appendChild(from);
	}
	if (!m_toEnd.isNull())
	{
		QDomElement to = parent.ownerDocument().createElement("to");
		to.setAttribute("node", m_toEnd.node->id().toString());
		to.setAttribute("pointIdx", m_toEnd.tiePointIdx);
		parent.appendChild(to);
	}
}


void ILink::createRelations(SvgNode *top){
	if (m_fromDom.hasAttributes())
	{
		QDomElement e = m_fromDom.toElement();
		QUuid nodeId = e.attribute("node");
		SvgNode *node = top->search(nodeId);
		if (node)
		{
			m_fromEnd.node = node;
			m_fromEnd.tiePointIdx = e.attribute("pointIdx").toInt();
		}
	}
	if (m_toDom.hasAttributes())
	{
		QDomElement e = m_toDom.toElement();
		QUuid nodeId = e.attribute("node");
		SvgNode *node = top->search(nodeId);
		if (node)
		{
			m_toEnd.node = node;
			m_toEnd.tiePointIdx = e.attribute("pointIdx").toInt();
		}
	}
}

void  ILink::tryConnecte(SvgNode* top,const QPointF & p, bool isStart)
{
	QList<SvgNode*> queue;
	queue.append(top);
	while (!queue.isEmpty())
	{
		SvgNode* curr = queue.first();
		queue.pop_front();
		for each (SvgNode* node in curr->childNodes())
		{
			queue.append(node);
		}
		int idx = 0;
		for each (const QPointF &pt in curr->tiePoints())
		{
			if (curr->mapFromScene(p) == pt)
			{
				LineEnd &end = isStart ? m_fromEnd : m_toEnd;
				end.node = curr;
				end.tiePointIdx = idx;
				connection conn(this, isStart);
				curr->appendConnection(conn);

				curr->setShowTiePoints(false);
				queue.clear();
				break;
			}
			idx++;
		}
	}
}

void ILink::onEndMove(bool isStart){
	this->endPointChanged(isStart);
}

void ILink::onEndResize(bool isStart){
	this->endPointChanged(isStart);
}

void ILink::onEndRotate(bool isStart){
	this->endPointChanged(isStart);
}

void ILink::endPointChanged(bool isStart){
	return;
	LineEnd &end = isStart ? m_fromEnd : m_toEnd;
	QPointF newTiePoint = end.node->mapToScene(end.node->tiePoints().at(end.tiePointIdx));
	this->replaceWithScenePoint(isStart, newTiePoint);
}