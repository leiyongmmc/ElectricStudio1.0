#include "svgnodeelementfactory.h"
#include "svgnodecontainer.h"
#include "svgconnectionpointcontainer.h"
#include "svgNodeElementImpl/svgcircleelement.h"
#include "svgNodeElementImpl/svgellipseelement.h"
#include "svgNodeElementImpl/svglineelement.h"
#include "svgNodeElementImpl/svgpolygonelement.h"
#include "svgNodeElementImpl/svgpolylineelement.h"
#include "svgNodeElementImpl/svgrectelement.h"
#include "svgNodeElementImpl/svgpathelement.h"
#include "svgNodeElementImpl/svgcirclecommonelement.h"
#include "svgNodeElementImpl/svgcirclefloorelement.h"
#include "svgNodeElementImpl/svgtextelement.h"

SvgNodeElementFactory::SvgNodeElementFactory()
{
}

SvgNode* SvgNodeElementFactory::createNode(const QDomElement& dom, SvgNode *parent){
	QString type = dom.nodeName();
	if (type == "g"){
		if (dom.hasAttribute("connectionPointContainer") && dom.attribute("connectionPointContainer").toInt() == 1 )
			return new SvgConnectionPointContainer(parent);
		return new SvgNodeContainer(parent);
	}
	else if (type == "a"){
		return new SvgPathElement(parent);
	}
	else if (type == "path"){
		return new SvgPathElement(parent);
	}
	else if (type == "rect"){
		return new SvgRectElement(parent);
	}
	else  if (type == "circle"){
		if (dom.hasAttribute("connectionPointType")){
			QString t = dom.attribute("connectionPointType");
			if (t == "comm") 
				return new SvgCircleCommonElement(parent);
			if (t == "floor") 
				return new SvgCircleFloorElement(parent);
			return new SvgCircleElement(parent);
		}
		else{
			return new SvgCircleElement(parent);
		}
	}
	else  if (type == "ellipse"){
		return new SvgEllipseElement(parent);
	}
	else  if (type == "line"){
		return new SvgLineElement(parent);
	}
	else  if (type == "polyline"){
		return new SvgPolylineElement(parent);
	}
	else  if (type == "polygon"){
		return new SvgPolygonElement(parent);
	}
	else if (type == "text")
		return new SvgTextElement(parent);
	return	NULL;
}
