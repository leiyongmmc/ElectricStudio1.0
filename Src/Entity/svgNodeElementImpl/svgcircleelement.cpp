#include "svgcircleelement.h"
#include "colortransformer.h"

SvgCircleElement::SvgCircleElement(SvgNode *parent)
    :SvgNodeElement(parent)
{
}

void SvgCircleElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){

    SvgNodeElement::paint(painter,option,widget);

	painter->setBrush(m_fill);
    painter->drawEllipse(QPointF(m_cx,m_cy), m_r, m_r);
	
	/*QPointF center;
	QList<QPointF> list = this->alignPoints(center);
	for each (const QPointF& p in list)
	{
		painter->drawEllipse(p, 2, 2);
	}
	painter->drawEllipse(center, 2, 2);*/
	//for debug
	//painter->drawRect(m_frame);

}

void SvgCircleElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgCircleElement *p = qobject_cast<SvgCircleElement*>(node);
	if (p)
	{
		p->m_cx = m_cx;
		p->m_cy = m_cy;
		p->m_r = m_r;
	}
	
}

void SvgCircleElement::updateShape() {
	m_shape = QPainterPath();
	m_shape.addEllipse(QPointF(m_cx, m_cy), m_r, m_r);
}

void SvgCircleElement::fromXmlImpl(const QDomElement &xml) {

    if(xml.hasAttribute("cx"))
        m_cx = xml.attribute("cx").toDouble();

    if(xml.hasAttribute("cy"))
		m_cy = xml.attribute("cy").toDouble();

    if(xml.hasAttribute("r"))
		m_r = xml.attribute("r").toDouble();


}
QDomElement SvgCircleElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("circle");

	QPointF origin = fixedOriginPoint();

	origin += QPointF(m_r, m_r);

	curr.setAttribute("cx", QString("%1").arg(origin.x() + this->pos().x()));
	curr.setAttribute("cy", QString("%1").arg(origin.y() + this->pos().y()));
	curr.setAttribute("r", QString("%1").arg(m_r));

	return curr;
}

void SvgCircleElement::updateFrame(){
	//reset frame	
	m_frame = QRectF(m_cx - m_r - m_strokeWidth / 2.f, m_cy - m_r - m_strokeWidth / 2.f, 2 * m_r + m_strokeWidth, 2 * m_r + m_strokeWidth);
	frameSizeCheck();
}


void SvgCircleElement::onResize(QRectF rect){

    QRectF rectNew = rect;
	//fix
	rectNew = QRectF(rectNew.x() + m_strokeWidth / 2.f, rectNew.y() + m_strokeWidth / 2.f, rectNew.width() - m_strokeWidth, rectNew.height() - m_strokeWidth);
	QRectF rectOld = QRectF(m_frame.x() + m_strokeWidth / 2.f, m_frame.y() + m_strokeWidth / 2.f, m_frame.width() - m_strokeWidth, m_frame.height() - m_strokeWidth);

	QPointF fixPoint;
	bool isInvalid = false;
	if (rectOld.x() == rectNew.x() && rectOld.y() == rectNew.y())
	{
		fixPoint = QPointF(rectOld.x(), rectOld.y());
	}
	else if (rectOld.x() + rectOld.width() == rectNew.x() + rectNew.width() && rectOld.y() == rectNew.y())
	{
		fixPoint = QPointF(rectOld.x() + rectOld.width(), rectOld.y());
	}
	else if (rectOld.x() + rectOld.width() == rectNew.x() + rectNew.width() && rectOld.y() + rectOld.height() == rectNew.y() + rectNew.height())
	{
		fixPoint = QPointF(rectOld.x() + rectOld.width(), rectOld.y() + rectOld.height());
	}
	else if (rectOld.x() == rectNew.x() && rectOld.y() + rectOld.height() == rectNew.y() + rectNew.height())
	{
		fixPoint = QPointF(rectOld.x(), rectOld.y() + rectOld.height());
	}
	else{
		isInvalid = true;
	}
	if (!isInvalid)
    {
		qreal maxmin = 0;
		if (rectNew.width()*rectNew.height() > rectOld.width()*rectOld.height())
		{
			maxmin = rectNew.width() >  rectNew.height() ? rectNew.width() : rectNew.height();
		}
		else
		{
			maxmin = rectNew.width() <  rectNew.height() ? rectNew.width() : rectNew.height();
		}
		maxmin /= 2;

		qreal scale = maxmin / m_r;

		QPointF center = QPointF(fixPoint.x() + (m_cx - fixPoint.x())*scale, fixPoint.y() + (m_cy - fixPoint.y()) *scale);
		m_cx = center.x();
		m_cy = center.y();

		m_r = maxmin;
		updateFrame();
		updateShape();
	}
    SvgNode::onResize(rect);
}

QList<QPointF> SvgCircleElement::tiePoints() {
	QList<QPointF> list;
	for (int i = 0; i < 8;i++)
	{
		qreal angle = i * 45 / 180. * 3.1415926;
		list.append(QPointF(m_cx + m_r*cos(angle), m_cy + m_r*sin(angle)));
	}
	return list;
}

QList<QPointF> SvgCircleElement::alignPoints(QPointF &center){
	QList<QPointF> list;
	QPointF offset = fixedOriginPoint() - QPointF(m_cx - m_r, m_cy - m_r);
	for (int i = 0; i < 4; i++)
	{
		qreal angle = (i * 90 - this->m_rotationAngle) / 180. * 3.1415926;
		list.append(QPointF(m_cx + m_r*cos(angle), m_cy + m_r*sin(angle)) + offset);
	}
	center = QPointF(m_cx, m_cy) + offset;
	return list;
}