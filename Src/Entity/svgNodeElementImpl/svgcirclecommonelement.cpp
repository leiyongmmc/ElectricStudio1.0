#include "svgcirclecommonelement.h"

SvgCircleCommonElement::SvgCircleCommonElement(SvgNode *parent)
        :SvgCircleElement(parent)
{
	this->setFlagsEnable(false);
}
void SvgCircleCommonElement::fromXmlImpl(const QDomElement &xml) {
	SvgCircleElement::fromXmlImpl(xml);

}
QDomElement SvgCircleCommonElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = SvgCircleElement::toXmlImpl(parent);
	curr.setAttribute("connectionPointType", "common");
	return curr;
}


QList<QPointF> SvgCircleCommonElement::tiePoints() {
	QList<QPointF> list;
	return list;
}