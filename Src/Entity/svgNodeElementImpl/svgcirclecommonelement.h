#ifndef SVGCIRCLECOMMONELEMENT_H
#define SVGCIRCLECOMMONELEMENT_H

#include "svgcircleelement.h"

class SvgCircleCommonElement : public SvgCircleElement
{
    Q_OBJECT
public:
	SvgCircleCommonElement(SvgNode *parent = 0);
	virtual QList<QPointF> tiePoints();
protected:
	virtual void fromXmlImpl(const QDomElement &xml);
	virtual QDomElement toXmlImpl(QDomElement &parent) const;

};

#endif // SVGCIRCLECOMMONELEMENT_H
