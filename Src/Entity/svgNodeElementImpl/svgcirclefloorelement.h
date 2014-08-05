#ifndef SVGCIRCLEFLOORELEMENT_H
#define SVGCIRCLEFLOORELEMENT_H

#include "svgcircleelement.h"

class SvgCircleFloorElement : public SvgCircleElement
{
    Q_OBJECT
public:
	SvgCircleFloorElement(SvgNode *parent = 0);
	virtual QList<QPointF> tiePoints();
protected:
	virtual void fromXmlImpl(const QDomElement &xml);
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
};

#endif // SVGCIRCLEFLOORELEMENT_H
