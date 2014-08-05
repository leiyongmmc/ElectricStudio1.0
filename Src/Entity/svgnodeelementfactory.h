#ifndef SVGNODEELEMENTFACTORY_H
#define SVGNODEELEMENTFACTORY_H
#include "entity_global.h"
#include "svgnode.h"
class ENTITYSHARED_EXPORT SvgNodeElementFactory
{
public:
	static SvgNode* createNode(const QDomElement& dom, SvgNode *parent = 0);

private:
    SvgNodeElementFactory();
};

#endif // SVGNODEELEMENTFACTORY_H
