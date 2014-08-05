#include "svgcirclefloorelement.h"


SvgCircleFloorElement::SvgCircleFloorElement(SvgNode *parent)
        :SvgCircleElement(parent)
{
	this->setFlagsEnable(false);
}
void SvgCircleFloorElement::fromXmlImpl(const QDomElement &xml) {
	SvgCircleElement::fromXmlImpl(xml);

}
QDomElement SvgCircleFloorElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = SvgCircleElement::toXmlImpl(parent);
	curr.setAttribute("connectionPointType", "floor");
	return curr;
}


QList<QPointF> SvgCircleFloorElement::tiePoints() {
	QList<QPointF> list;
	return list;
}