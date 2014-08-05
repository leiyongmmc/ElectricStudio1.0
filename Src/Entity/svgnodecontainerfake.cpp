#include "svgnodecontainerfake.h"
#include "svgnode.h"


SvgNodeContainerFake::SvgNodeContainerFake(SvgNode *parent)
        :SvgNodeContainer(parent)
{
}




void SvgNodeContainerFake::toXml(QDomElement &parent) const{

	foreach(SvgNode* element, m_childern) {
		element->toXml(parent);
	}
}

QDomElement SvgNodeContainerFake::toXmlImpl(QDomElement &parent) const{
	return QDomElement();
}