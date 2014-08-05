#include "svgrectelement.h"
#include "colortransformer.h"

SvgRectElement::SvgRectElement(SvgNode *parent)
    :SvgNodeElement(parent),
	m_x(0), m_y(0), m_width(0), m_height(0)
{
}

void SvgRectElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){

    SvgNodeElement::paint(painter,option,widget);

	painter->setBrush(m_fill);

	QRectF rect(m_x, m_y, m_width, m_height);
	painter->drawRect(rect);

}

void SvgRectElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgRectElement *p = qobject_cast<SvgRectElement*>(node);
	if (p)
	{
		p->m_x = m_x;
		p->m_y = m_y;
		p->m_width = m_width;
		p->m_height = m_height;
	}

}


void SvgRectElement::fromXmlImpl(const QDomElement &xml) {

    if(xml.hasAttribute("x"))
		m_x = xml.attribute("x").toDouble();

    if(xml.hasAttribute("y"))
		m_y = xml.attribute("y").toDouble();

    if(xml.hasAttribute("width"))
		m_width = xml.attribute("width").toDouble();

    if(xml.hasAttribute("height"))
		m_height = xml.attribute("height").toDouble();

}
QDomElement SvgRectElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("rect");
	
	QPointF origin = fixedOriginPoint();

	curr.setAttribute("x", QString("%1").arg(pos().x() + origin.x()));
	curr.setAttribute("y", QString("%1").arg(pos().y() + origin.y()));
	curr.setAttribute("width", QString("%1").arg(m_width));
	curr.setAttribute("height", QString("%1").arg(m_height));
	
	return curr;
}

void SvgRectElement::updateFrame(){
	//reset frame	
	m_frame = QRectF(m_x - m_strokeWidth / 2.f, m_y - m_strokeWidth / 2.f, m_width + m_strokeWidth, m_height + m_strokeWidth);
	frameSizeCheck();
}


void SvgRectElement::onResize(QRectF r){

    QRectF rect = r;

	//fix
	rect = QRectF(rect.x() + m_strokeWidth / 2.f, rect.y() + m_strokeWidth / 2.f, rect.width() - m_strokeWidth, rect.height() -  m_strokeWidth);


	m_width = rect.width();
	m_height = rect.height() ;
	m_x = rect.left();
	m_y = rect.top();
	updateFrame();
	updateShape();
    SvgNode::onResize(rect);
}


QList<QPointF> SvgRectElement::tiePoints() {
	QList<QPointF> list;

	list.append(QPointF(m_x+m_width/2, m_y));
	list.append(QPointF(m_x+m_width, m_y + m_height / 2));
	list.append(QPointF(m_x + m_width / 2, m_y+m_height));
	list.append(QPointF(m_x , m_y + m_height / 2));
	return list;
}
