#include "svglineelement.h"
#include "colortransformer.h"
#include <QRegion >
#include "svghelper.h"

SvgLineElement::SvgLineElement(SvgNode *parent)
    :SvgNodeElement(parent),
	m_p1(QPointF(0,0)),
	m_p2(QPointF(0, 0))
{
}

void SvgLineElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){

    SvgNodeElement::paint(painter,option,widget);

    painter->drawLine(m_p1,m_p2);


	/*QPointF center;
	QList<QPointF> list = this->alignPoints(center);
	for each (QPointF p in list)
	{
		painter->drawEllipse(p, 2, 2);
	}
	painter->drawEllipse(center, 2, 2);*/

}
void SvgLineElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgLineElement *p = qobject_cast<SvgLineElement*>(node);
	if (p)
	{
		p->m_p1 = m_p1;
		p->m_p2 = m_p2;
	}

}
void SvgLineElement::updateShape() {
	m_shape = QPainterPath();
	
	m_shape.addRegion(regionFrom2Points(m_p1, m_p2));
}


void SvgLineElement::fromXmlImpl(const QDomElement &xml) {

	qreal x1, y1, x2, y2;
	x1 = y1 = x2 = y2 = 0;
	if (xml.hasAttribute("x1"))
		x1 = xml.attribute("x1").toDouble();

	if (xml.hasAttribute("y1"))
		y1 = xml.attribute("y1").toDouble();

	if (xml.hasAttribute("x2"))
		x2 = xml.attribute("x2").toDouble();

	if (xml.hasAttribute("y2"))
		y2 = xml.attribute("y2").toDouble();

	m_p1 = QPointF(x1, y1);
	m_p2 = QPointF(x2, y2);

}
QDomElement SvgLineElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("line");

	QPointF offset = fixedOriginPoint() - m_frame.topLeft() - QPointF(m_strokeWidth / 2., m_strokeWidth / 2.);
	curr.setAttribute("x1", QString("%1").arg(m_p1.x() + this->pos().x() + offset.x()));
	curr.setAttribute("y1", QString("%1").arg(m_p1.y() + this->pos().y() + offset.y()));
	curr.setAttribute("x2", QString("%1").arg(m_p2.x() + this->pos().x() + offset.x()));
	curr.setAttribute("y2", QString("%1").arg(m_p2.y() + this->pos().y() + offset.y()));

	return curr;
}
void SvgLineElement::updateFrame(){
	//reset frame	
	qreal minx = m_p1.x() < m_p2.x() ? m_p1.x() : m_p2.x();
	qreal miny = m_p1.y() < m_p2.y() ? m_p1.y() : m_p2.y();
	m_frame = QRectF(minx - m_strokeWidth / 2.f , miny - m_strokeWidth / 2.f -0 , abs(m_p1.x() - m_p2.x()) + m_strokeWidth , abs(m_p1.y() - m_p2.y()) + m_strokeWidth + 0);
	frameSizeCheck();
}

void SvgLineElement::onResize(QRectF rect){

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
		qreal xScale = rectNew.width() / rectOld.width();
		qreal yScale = 1;// rectNew.height() / rectOld.height();

		m_p1 = QPointF(fixPoint.x() + (m_p1.x() - fixPoint.x())*xScale, fixPoint.y() + (m_p1.y() - fixPoint.y()) *yScale);
		m_p2 = QPointF(fixPoint.x() + (m_p2.x() - fixPoint.x())*xScale, fixPoint.y() + (m_p2.y() - fixPoint.y()) *yScale);
		updateFrame();
		updateShape();
	}
    SvgNode::onResize(rect);
}
QList<QPointF> SvgLineElement::alignPoints(QPointF &center){
	QList<QPointF> list;
	QPointF offset = fixedOriginPoint() - m_frame.topLeft() - QPointF(m_strokeWidth / 2., m_strokeWidth / 2.);
	list.append(m_p1 + offset);
	list.append(m_p2 + offset);
	
	center = (m_p1 + m_p2) / 2. + offset;
	return list;
}