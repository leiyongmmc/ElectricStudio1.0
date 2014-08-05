#ifndef SVGCONNECTIONPOINTCONTAINER_H
#define SVGCONNECTIONPOINTCONTAINER_H

#include "svgnodecontainer.h"

class ENTITYSHARED_EXPORT SvgConnectionPointContainer : public SvgNodeContainer
{
public:
	SvgConnectionPointContainer(SvgNode *parent = 0);

protected:
	virtual void fromXmlImpl(const QDomElement &xml);
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	virtual void updateFrame();
};

#endif // SVGCONNECTIONPOINTCONTAINER_H
