#include "svgnodecontainer.h"
#include "svgnodeelementfactory.h"
#include "graphprimitiveprop.h"
#include "colortransformer.h"

SvgNodeContainer::SvgNodeContainer(SvgNode *parent)
        :SvgNode(parent)
{
}


void SvgNodeContainer::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){

	if (0)
		foreach(SvgNode* element, m_childern) {
		element->paint(painter, option, widget);

	}
}

void SvgNodeContainer::fromXmlImpl(const QDomElement &xml) {
    QDomNodeList subs = xml.childNodes();

    for (int i= 0 ; i < subs.count() ;i++){

         QDomNode xmlNode = subs.item(i);

		 if (xmlNode.nodeName() == "props")
		 {
			 //read prop
			 for (int j = 0; j < xmlNode.childNodes().count(); j++){
				 QDomElement prop = xmlNode.childNodes().item(j).toElement();
				 QString  name = prop.attribute("name");
				 GraphPrimitiveProp::PropType type = (GraphPrimitiveProp::PropType)prop.attribute("type").toInt();
				 QString tmpDefault = prop.attribute("defaultValue");
				 QString tmpCurrent = prop.attribute("value");
				 QVariant defaultValue;
				 switch (type)
				 {
				 case GraphPrimitiveProp::FLOAT:
					 defaultValue = prop.attribute("defaultValue").toDouble();
					 if (prop.hasAttribute("value"))
						 this->m_props.append(GraphPrimitiveProp(name, type, defaultValue, prop.attribute("value").toDouble()));
					 else
						 this->m_props.append(GraphPrimitiveProp(name, type, defaultValue));
					 break;
				 case GraphPrimitiveProp::INT:
					 defaultValue = prop.attribute("defaultValue").toInt();
					 if (prop.hasAttribute("value"))
						 this->m_props.append(GraphPrimitiveProp(name, type, defaultValue, prop.attribute("value").toInt()));
					 else
						 this->m_props.append(GraphPrimitiveProp(name, type, defaultValue));
					 break;
				 case GraphPrimitiveProp::STRING:
					 defaultValue = prop.attribute("defaultValue");
					 if (prop.hasAttribute("value"))
						 this->m_props.append(GraphPrimitiveProp(name, type, defaultValue, prop.attribute("value")));
					 else
						 this->m_props.append(GraphPrimitiveProp(name, type, defaultValue));
					 break;
				 default:
					 break;
				 }
			 }
		 }
		 else{
			 SvgNode *node = SvgNodeElementFactory::createNode(xmlNode.toElement(), this);
			 if (!node)
				 continue;
			 node->fromXml(xmlNode.toElement());
			 this->add(node);
			 node->setParentNode(this);
		 }
        
    }

	updateFrame();
	updateShape();
}

void SvgNodeContainer::toXml(QDomElement &parent) const{
	QDomElement curr = toXmlImpl(parent);
	foreach(SvgNode* element, m_childern) {
		element->toXml(curr);
	}

	curr.setAttribute("class", m_className);
	curr.setAttribute("stroke-width", QString("%1").arg(m_strokeWidth));
	curr.setAttribute("stroke", ColorTransformer::colorToStr(m_stroke));
	curr.setAttribute("fill", ColorTransformer::colorToStr(m_fill));

	parent.appendChild(curr);
}

QDomElement SvgNodeContainer::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("g");
	//write prop
	if (!this->m_props.empty())
	{
		QDomElement props = parent.ownerDocument().createElement("props");

		for each (const GraphPrimitiveProp & p in this->m_props)
		{
			QDomElement prop = parent.ownerDocument().createElement("prop");
			prop.setAttribute("name", p.name());
			prop.setAttribute("type", p.type());
			prop.setAttribute("defaultValue", p.defaultValue().toString());
			prop.setAttribute("value", p.value().toString());
			props.appendChild(prop);
		}
		curr.appendChild(props);
	}
	
	return curr;
}

void SvgNodeContainer::createRelations(SvgNode *top){
	foreach(SvgNode* element, m_childern) {
		element->createRelations(top);
	}

}

void SvgNodeContainer::updateFrame(){


	//reset frame	
	qreal minx = 999999;
	qreal miny = 999999;
	qreal maxx = -999999;
	qreal maxy = -999999;
	for each (SvgNode* node in m_childern)
	{
		if (minx > node->frame().x())
			minx = node->frame().x();
		if (miny > node->frame().y())
			miny = node->frame().y();

		if (maxx < node->frame().x() + node->frame().width())
			maxx = node->frame().x() + node->frame().width();
		if (maxy < node->frame().y() + node->frame().height())
			maxy = node->frame().y() + node->frame().height();
	}
	m_frame = QRectF(minx - m_strokeWidth / 2.f, miny - m_strokeWidth / 2.f, (maxx - minx) + m_strokeWidth, (maxy - miny) + m_strokeWidth);
}