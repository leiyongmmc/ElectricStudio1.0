#include "svgpolygonelement.h"
#include "colortransformer.h"
#include "svghelper.h"

SvgPolygonElement::SvgPolygonElement(SvgNode *parent)
    :SvgNodeElement(parent)
{
}

void SvgPolygonElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){



    SvgNodeElement::paint(painter,option,widget);

	painter->setBrush(m_fill);
    painter->drawPolygon(QPolygonF(m_points.toVector()));


}

void SvgPolygonElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgPolygonElement *p = qobject_cast<SvgPolygonElement*>(node);
	if (p)
	{
		p->m_points = m_points;
	}

}

void SvgPolygonElement::updateShape() {
	m_shape = QPainterPath();
	m_shape.addPolygon(QPolygonF(m_points.toVector()));

}

void SvgPolygonElement::fromXmlImpl(const QDomElement &xml) {


    if(xml.hasAttribute("points")){
		

        QString strPs = xml.attribute("points");
		QStringList coord = strPs.split(QRegExp("[, \r\n]"), QString::SkipEmptyParts);

		int count = coord.length() / 2;
		QList<QPointF> ps = strToPoints(coord, count);
		foreach(QPointF p, ps) {
			m_points.append(p);
		}
		
    }
}
QDomElement SvgPolygonElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("polygon");

	QPointF origin = fixedOriginPoint();
	origin -= m_frame.topLeft() + QPointF(m_strokeWidth / 2.f, m_strokeWidth / 2.f);

	QStringList points;
	for each (QPointF p in m_points)
	{
		points.append(QString("%1,%2").arg(origin.x() + p.x() + this->pos().x()).arg(origin.y() + p.y() + this->pos().y()));
	}

	curr.setAttribute("points",points.join(" "));
	
	return curr;
}

void SvgPolygonElement::updateFrame(){
	//reset frame	
	qreal minx = 999999;
	qreal miny = 999999;
	qreal maxx = -999999;
	qreal maxy = -999999;

	foreach(const QPointF &p, m_points) {

		if (minx > p.x())
			minx = p.x();
		if (miny > p.y())
			miny = p.y();

		if (maxx < p.x())
			maxx = p.x();
		if (maxy < p.y())
			maxy = p.y();

	}

	m_frame = QRectF(minx - m_strokeWidth / 2.f, miny - m_strokeWidth / 2.f, (maxx - minx) + m_strokeWidth, (maxy - miny) + m_strokeWidth);
	frameSizeCheck();
}

void SvgPolygonElement::onResize(QRectF rect){
	QRectF rectNew = dashRect->rect();
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
		qreal yScale = rectNew.height() / rectOld.height();


		int i = 0;
		for each (QPointF p in m_points)
		{
			p = QPointF(fixPoint.x() + (p.x() - fixPoint.x())*xScale, fixPoint.y() + (p.y() - fixPoint.y()) *yScale);
			m_points.replace(i++, p);
		}

		updateFrame();
		updateShape();
	}

    SvgNode::onResize(rect);
}

QList<QPointF> SvgPolygonElement::tiePoints() {
	return m_points;
}

QList<QPointF> SvgPolygonElement::alignPoints(QPointF &center){
	QList<QPointF> list;
	QPointF fixLeftTop = fixedOriginPoint();
	QPointF offset = fixLeftTop - m_frame.topLeft() - QPointF(m_strokeWidth / 2.f, m_strokeWidth / 2.f);
	for each (const QPointF & p in m_points)
	{
		list.append(p + offset);
	}
	
	center = m_frame.center() + offset;
	return list;
}