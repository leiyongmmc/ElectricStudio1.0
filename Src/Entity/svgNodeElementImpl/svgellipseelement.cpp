#include "svgellipseelement.h"
#include "colortransformer.h"
#include "util.h"

SvgEllipseElement::SvgEllipseElement(SvgNode *parent)
    :SvgNodeElement(parent)
{
}

void SvgEllipseElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){

    SvgNodeElement::paint(painter,option,widget);

	painter->setBrush(m_fill);
	painter->drawEllipse(QPointF(m_cx, m_cy), m_rx, m_ry);

	/*QPointF center;
	QList<QPointF> list = this->alignPoints(center);
	for each (const QPointF& p in list)
	{
		painter->drawEllipse(p, 2, 2);
	}
	painter->drawEllipse(center, 2, 2);*/
}

void SvgEllipseElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgEllipseElement *p = qobject_cast<SvgEllipseElement*>(node);
	if (p)
	{
		p->m_cx = m_cx;
		p->m_cy = m_cy;
		p->m_rx = m_rx;
		p->m_ry = m_ry;
	}

}

void SvgEllipseElement::updateShape() {
	m_shape = QPainterPath();
	m_shape.addEllipse(QPointF(m_cx, m_cy), m_rx, m_ry);
}

void SvgEllipseElement::fromXmlImpl(const QDomElement &xml) {



    if(xml.hasAttribute("cx"))
		m_cx = xml.attribute("cx").toDouble();

    if(xml.hasAttribute("cy"))
		m_cy = xml.attribute("cy").toDouble();

    if(xml.hasAttribute("rx"))
		m_rx = xml.attribute("rx").toDouble();

    if(xml.hasAttribute("ry"))
		m_ry = xml.attribute("ry").toDouble();

}
QDomElement SvgEllipseElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("ellipse");

	QPointF origin = fixedOriginPoint();
	origin += QPointF(m_rx, m_ry);
	curr.setAttribute("cx", QString("%1").arg(origin.x() + this->pos().x()));
	curr.setAttribute("cy", QString("%1").arg(origin.y() + this->pos().y()));
	curr.setAttribute("rx", QString("%1").arg(m_rx));
	curr.setAttribute("ry", QString("%1").arg(m_ry));

	return curr;

}
void SvgEllipseElement::updateFrame(){
	//reset frame	
	m_frame = QRectF(m_cx - m_rx - m_strokeWidth / 2.f, m_cy - m_ry - m_strokeWidth / 2.f, 2 * m_rx + m_strokeWidth, 2 * m_ry + m_strokeWidth);
	frameSizeCheck();
}

void SvgEllipseElement::onResize(QRectF rect){
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
		qreal w = rectNew.width()/2.;
		qreal h = rectNew.height()/2.;


		qreal xScale = w / m_rx;
		qreal yScale = h / m_ry;

		QPointF center = QPointF(fixPoint.x() + (m_cx - fixPoint.x())*xScale, fixPoint.y() + (m_cy - fixPoint.y()) *yScale);
		m_cx = center.x();
		m_cy = center.y();

		m_rx = w;
		m_ry = h;
		updateFrame();
		updateShape();
	}
    SvgNode::onResize(rect);
}


QList<QPointF> SvgEllipseElement::tiePoints() {
	QList<QPointF> list;
	for (int i = 0; i < 8; i++)
	{
		qreal angle = i * 45 / 180. * 3.1415926;
		list.append(QPointF(m_cx + m_rx*cos(angle), m_cy + m_ry*sin(angle)));
	}
	return list;
}

QList<QPointF> SvgEllipseElement::alignPoints(QPointF &center){
	/*x = x0 + a * cos(t)
	y = y0 + b * sin(t)*/
	QList<QPointF> list;
	QPointF offset = fixedOriginPoint() - m_frame.topLeft() - QPointF(m_strokeWidth / 2., m_strokeWidth / 2.);
	/*for (int i = 0; i < 4; i++)
	{
		qreal angle = (i * 90 - this->m_rotationAngle) / 180. * 3.1415926;
		list.append(QPointF(m_cx + m_rx*cos(angle), m_cy + m_ry*sin(angle)) + offset);
	}
	center = QPointF(m_cx, m_cy) + offset;*/

	QPointF minx, miny, maxx, maxy;
	bool isInit = false;
	for (int i = 0; i < 360;i++)
	{
		qreal angle = i / 180. * 3.1415926;
		QPointF p = QPointF(m_cx + m_rx*cos(angle), m_cy + m_ry*sin(angle));
		p = Util::rotateWithCenter(p , QPointF(m_cx, m_cy), -this->m_rotationAngle);

		if (!isInit)
		{
			minx = miny = maxx = maxy = p;
			isInit = true;
		}
		else{
			if (minx.x() > p.x())
				minx = p;
			if (miny.y() > p.y())
				miny = p;
			if (maxx.x() < p.x())
				maxx = p;
			if (maxy.y() < p.y())
				maxy = p;
		}
	}
	list.append(Util::rotateWithCenter(minx, QPointF(m_cx, m_cy), this->m_rotationAngle) + offset);
	list.append(Util::rotateWithCenter(miny, QPointF(m_cx, m_cy), this->m_rotationAngle) + offset);
	list.append(Util::rotateWithCenter(maxx, QPointF(m_cx, m_cy), this->m_rotationAngle) + offset);
	list.append(Util::rotateWithCenter(maxy, QPointF(m_cx, m_cy), this->m_rotationAngle) + offset);
	center = QPointF(m_cx, m_cy) + offset;
	return list;
}