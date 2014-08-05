#ifndef SVGNODECONTAINERFAKE_H
#define SVGNODECONTAINERFAKE_H

#include "SvgNodeContainer.h"

class ENTITYSHARED_EXPORT SvgNodeContainerFake : public SvgNodeContainer
{
    Q_OBJECT
public:
    SvgNodeContainerFake(SvgNode *parent = 0);
	virtual void toXml(QDomElement &parent) const;

protected:
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
};

#endif // SVGNODECONTAINERFAKE_H
