#include "svgconnectionpointcontainer.h"
#include "svgnodeelementfactory.h"

SvgConnectionPointContainer::SvgConnectionPointContainer(SvgNode *parent)
	:SvgNodeContainer(parent)
{
}

void SvgConnectionPointContainer::fromXmlImpl(const QDomElement &xml) {

	QDomNodeList subs = xml.childNodes();

	for (int i = 0; i < subs.count(); i++){

		QDomNode xmlNode = subs.item(i);

		SvgNode *node = SvgNodeElementFactory::createNode(xmlNode.toElement(), this);
		if (!node)
			continue;
		node->fromXml(xmlNode.toElement());
		this->add(node);
		node->setParentNode(this);

	}

	updateFrame();
	updateShape();
}
QDomElement SvgConnectionPointContainer::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("g");
	curr.setAttribute("connectionPointContainer", 1);
	return curr;
}

void SvgConnectionPointContainer::updateFrame(){

}