#include "svgpolylineelement.h"
#include "colortransformer.h"
#include "svghelper.h"
#include "../pointitemcontainer.h"
#include <QRegion>

SvgPolylineElement::SvgPolylineElement(SvgNode *parent)
    :SvgNodeElement(parent)
{
	m_pointItemContainer = new PointItemContainer(this);
	m_pointItemContainer->setDelegate(this);

    setMouseMode(MouseMode_DRAW);
    m_pointItemContainer->setPointItemMode(PointItemMode_EDIT);
}

void SvgPolylineElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){

    if(m_pointItemContainer->getPointItemMode() == PointItemMode_EDIT)
    {
        if(option->state & QStyle::State_Selected)
        {
            m_pointItemContainer->showPointItems(true);
        }
        else
        {
            if(!m_pointItemContainer->isPointItemHaveSelected())
            {
                m_pointItemContainer->showPointItems(false);
            }
        }
    }
    SvgNodeElement::paint(painter,option,widget);

	if (!this->m_isMoving)
		ILink::endPointPosFix();
	
    painter->drawPolyline( QPolygonF(m_points.toVector()));
    
    /*QPen pen = painter->pen();
	pen.setColor(QColor(Qt::black));
	pen.setBrush(QBrush(QColor(Qt::red)));
	painter->setPen(pen);
	painter->drawPath(m_shape);*/

}

void SvgPolylineElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgPolylineElement *p = qobject_cast<SvgPolylineElement*>(node);
	if (p)
	{
		p->m_points = m_points;
	}

}

void SvgPolylineElement::updateShape() {
	m_shape = QPainterPath ();

	if (m_points.count() > 1)
	{
		QList<QVector<QPointF>> list;
		for (int i = 0; i < m_points.count() - 1; i++)
		{
			QPointF p1 = m_points.at(i);
			QPointF p2 = m_points.at(i+1);
			
			list.append(vectorFrom2Points(p1, p2));
		}
		m_shapePolygonPoints.clear();
		for (int i = 0; i < list.count(); i++)
		{
			QLineF line1(list.at(i).at(0), list.at(i).at(1));
			
			if (i==0)
				m_shapePolygonPoints.append(list.first().first());
			
			if (i < list.count() - 1)
			{
				QLineF line2(list.at(i + 1).at(0), list.at(i + 1).at(1));
				QPointF ip;
				if (line1.intersect(line2, &ip) != QLineF::NoIntersection)
					m_shapePolygonPoints.append(ip);
			}
			
			if (i == list.count() - 1)
				m_shapePolygonPoints.append(list.last().at(1));
		}
		for (int i = list.count() - 1; i >= 0; i--)
		{
			QLineF line1(list.at(i).at(3), list.at(i).at(2));

			if (i == list.count() - 1)
				m_shapePolygonPoints.append(list.last().at(2));

			if (i > 0)
			{
				QLineF line2(list.at(i - 1).at(3), list.at(i - 1).at(2));
				QPointF ip;
				if (line1.intersect(line2, &ip) != QLineF::NoIntersection)
					m_shapePolygonPoints.append(ip);
			}


			if (i == 0)
				m_shapePolygonPoints.append(list.first().at(3));
		}

		m_shape.addPolygon(QPolygonF( m_shapePolygonPoints));
		m_shape.closeSubpath();
	}
	else{
		m_shape.addRect(m_frame);
	}
}

void SvgPolylineElement::fromXmlImpl(const QDomElement &xml) {


    if(xml.hasAttribute("points")){
		

        QString strPs = xml.attribute("points");
		QStringList coord = strPs.split(QRegExp("[, \r\n]"), QString::SkipEmptyParts);

		int count = coord.length() / 2;
		QList<QPointF> ps = strToPoints(coord, count);
		foreach(QPointF p, ps) {
			m_points.append(p);
		}

    }

	ILink::fromXml(xml);
}
QDomElement SvgPolylineElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("polyline");

	QPointF origin = fixedOriginPoint();
	origin -= m_frame.topLeft() + QPointF(m_strokeWidth / 2.f, m_strokeWidth / 2.f);

	QStringList points;
	for each (QPointF p in m_points)
	{
		points.append(QString("%1,%2").arg(origin.x() + p.x() + this->pos().x()).arg(origin.y() + p.y() + this->pos().y()));
	}



	curr.setAttribute("points", points.join(" "));
	
	ILink::toXml(curr);

	return curr;
}

void SvgPolylineElement::updateFrame(){
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

void SvgPolylineElement::onResize(QRectF rect){
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

void SvgPolylineElement::onMoving(){

	if (!m_fromEnd.isNull())
		onPointPosChanged(0, this->mapToScene(m_points.first()));
	if (!m_toEnd.isNull())
		onPointPosChanged(m_points.count()-1, this->mapToScene(m_points.last()));
}


void SvgPolylineElement::onPointPosChanged(int idx, QPointF newPoint){

	m_points.replace(idx, this->mapFromScene(newPoint));

	if (idx == 0)
	{
		if (!m_fromEnd.isNull())
		{
			m_fromEnd.node->removeConnectionByLine(this, true);
			m_fromEnd.node = NULL;
		}

		tryConnecte(topParent(), newPoint,true);
	}
	if (idx == m_points.count()-1)
	{
		if (!m_toEnd.isNull())
		{
			m_toEnd.node->removeConnectionByLine(this, false);
			m_toEnd.node = NULL;
		}

		tryConnecte(topParent(), newPoint,false);
	}
	
	

	updateFrame();
    updateShape();
}

bool SvgPolylineElement::tiePointCheckDelegate(QPointF curr, QPointF *res){
	SvgNode *top = topParent();
	return top->tiePointCheck(curr, res);
}
void SvgPolylineElement::setEnableFlag(bool enable)
{
    if(enable)
    {
        setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        setMouseMode(MouseMode_DRAW);
        m_pointItemContainer->setPointItemMode(PointItemMode_EDIT);
        m_pointItemContainer->update(this->frame());
        updateFrame();
    }
    else
    {
        setFlag(QGraphicsItem::ItemIsMovable,false);
        setFlag(QGraphicsItem::ItemIsSelectable,false);
        setFlag(QGraphicsItem::ItemIsFocusable,false);
        m_pointItemContainer->setPointItemMode(PointItemMode_DRAW);
        setMouseMode(MouseMode_DRAW);
    }
}
void SvgPolylineElement::appendPoint(const QPointF &p)
{
    if(myMode == MouseMode_DRAW)
    {
        QPointF newpos = this->mapFromScene(p);
        m_points.append(newpos);
        updateFrame();
		updateShape();
		
		if (m_points.count() == 1)
			tryConnecte(topParent(), p, true);
		else
			tryConnecte(topParent(),p,false);

    }
}

void SvgPolylineElement::replaceWithScenePoint(bool isStart, QPointF newPoint) {

	if (isStart)
		m_points.replace(0, this->mapFromScene(newPoint));
	else
		m_points.replace(m_points.count() - 1, this->mapFromScene(newPoint));
	
	updateFrame();
	updateShape();

	//this->update(m_frame);
	//qApp->processEvents();
}


void SvgPolylineElement::setMouseMovePos(QPointF pos)
{
    m_pointItemContainer->mMousePos = pos;
    m_pointItemContainer->update(QRectF(0,0,0,0));
}
bool SvgPolylineElement::twoEndpointsLinked()
{
    if(m_toEnd.isNull())
    {
        return false;
    }
    return true;
}


void SvgPolylineElement::createRelations(SvgNode *top){
	SvgNode::createRelations(top);
	ILink::createRelations(top);
}

QList<QPointF> SvgPolylineElement::alignPoints(QPointF &center){
	QList<QPointF> list;
	/*QPointF fixLeftTop = fixOriginPoint();
	QPointF offset = fixLeftTop - m_frame.topLeft() - QPointF(m_strokeWidth / 2.f, m_strokeWidth / 2.f);
	for each (const QPointF & p in m_points)
	{
		list.append(p + offset);
	}

	center = m_frame.center() + offset;*/
	return list;
}