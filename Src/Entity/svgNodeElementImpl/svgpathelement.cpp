#include "svgpathelement.h"
#include "svghelper.h"
#include "colortransformer.h"
#include "util.h"

SvgPathElement::SvgPathElement(SvgNode *parent)
    :SvgNodeElement(parent)
{
}

void SvgPathElement::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){

    SvgNodeElement::paint(painter,option,widget);
	painter->setBrush(m_fill);

	QPainterPath path;
	for each (SvgPathElementItem item in m_pathList)
	{
		
		for each (SvgPathElementItemData itemData in item.data)
		{
			switch (itemData.type)
			{
			case pathDataType::M:
			case pathDataType::m:
				path.moveTo(itemData.points.first());
				break;
			case pathDataType::L:
			case pathDataType::l:
			case pathDataType::H:
			case pathDataType::h:
			case pathDataType::V:
			case pathDataType::v:
				path.lineTo(itemData.points.first());
				break;
			case pathDataType::C:
			case pathDataType::c:
			case pathDataType::S:
			case pathDataType::s:
				path.cubicTo(itemData.points[0], itemData.points[1], itemData.points[2]);
				break;
			case pathDataType::Q:
			case pathDataType::q:
			case pathDataType::T:
			case pathDataType::t:
				path.quadTo(itemData.points[0], itemData.points[1]);
				break;
			case pathDataType::A:
			case pathDataType::a:
					path.arcTo(itemData.points[0].x(), itemData.points[0].y(), itemData.points[1].x(), itemData.points[1].y(), itemData.points[2].x(), itemData.points[2].y());
				break;
			default:
				break;
			}
		}
		if (item.isClosed)
		{
			path.closeSubpath();
		}
	}

	painter->drawPath(path);

	/*QPointF center;
	QList<QPointF> list = this->alignPoints(center);
	for each (const QPointF& p in list)
	{
		painter->drawEllipse(p, 2, 2);
	}
	painter->drawEllipse(center, 2, 2);*/
}

void SvgPathElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgPathElement *p = qobject_cast<SvgPathElement*>(node);
	if (p)
	{
		p->m_pathList = m_pathList;
	}

}


void SvgPathElement::fromXmlImpl(const QDomElement &xml) {

    if(xml.hasAttribute("d")){
       
        QString strPs = xml.attribute("d");
		QStringList pathList;
		QString tmp = strPs;
		int idx1;
		int from = 0;
		while ( (idx1=tmp.indexOf(QRegExp("[Mm]"),from)) != -1){
			int idx2 = tmp.indexOf(QRegExp("[Mm]"), idx1 + 1);
			if (idx2 != -1){
				pathList.append(tmp.left(idx2).right(idx2 - idx1));
				from = idx1 + 1;
			}
			else{
				pathList.append(tmp.right(tmp.length() - idx1));
				break;
			}
		}
		
		//QStringList pathList = strPs.split(QRegExp("[Mm]"), QString::SkipEmptyParts);

		QPointF curr = QPointF(0, 0);
		for each (QString pathStr in pathList)
		{
			pathStr = pathStr.trimmed();
			SvgPathElementItem item;
			item.isClosed = pathStr.endsWith('Z') || pathStr.endsWith('z');
			if (item.isClosed)
				pathStr = pathStr.left(pathStr.length() - 1);
			QStringList coord = pathStr.split(QRegExp("[, \r\n]"), QString::SkipEmptyParts);

			while (coord.count())
			{
				QString s = coord.first();
				pathDataType type = (pathDataType)coord.first().toStdString().c_str()[0];
				if (coord.first().length()>1){
					coord.pop_front();
					coord.insert(0, s.right(s.length() - 1));
				}
				else{
					coord.pop_front();
				}
				

				if (type == pathDataType::M || type == pathDataType::m)
				{
					if (coord.count() < 2)
						break;

					QPointF moveTo = strToPoint(coord);
					if (type == pathDataType::m)
						moveTo += curr;
					curr = moveTo;
					SvgPathElementItemData itemData;
					itemData.type = (pathDataType)type;
					itemData.points.append(moveTo);
					itemData.start = itemData.end = moveTo;
					item.data.append(itemData);
					
				}
				else if (type == pathDataType::L || type == pathDataType::l)
				{
					if (coord.count() < 2)
						break;
					QPointF lineTo = strToPoint(coord);
					if (type == pathDataType::l)
						lineTo += curr;
					
					SvgPathElementItemData itemData;
					itemData.type = (pathDataType)type;
					itemData.points.append(lineTo);
					itemData.start = curr;
					itemData.end = lineTo;
					curr = lineTo;
					item.data.append(itemData);
				}
				else if (type == pathDataType::H || type == pathDataType::h)
				{
					if (coord.count() < 1)
						break;
					QPointF lineTo = strToPointH(coord, 0);
					if (type == pathDataType::h)
						lineTo += curr;
					else
						lineTo.setY(curr.y());
					
					SvgPathElementItemData itemData;
					itemData.type = (pathDataType)type;
					itemData.points.append(lineTo);
					itemData.start = curr;
					itemData.end = lineTo;
					curr = lineTo;
					item.data.append(itemData);
				}
				else if (type == pathDataType::V || type == pathDataType::v)
				{
					if (coord.count() < 1)
						break;
					QPointF lineTo = strToPointV(coord, 0);
					if (type == pathDataType::v)
						lineTo += curr;
					else
						lineTo.setX(curr.x());
					
					SvgPathElementItemData itemData;
					itemData.type = (pathDataType)type;
					itemData.points.append(lineTo);
					itemData.start = curr;
					itemData.end = lineTo;
					curr = lineTo;
					item.data.append(itemData);
				}
				else if (type == pathDataType::A || type == pathDataType::a)
				{
					if (coord.count() < 7)
						break;

					//radii (rx, ry),not a actual point
					QPointF rxy = strToPoint(coord);
					//x: x-axis-rotation,not a actual point
					QPointF angle = strToPointH(coord, 0);
					//x: large-arc-flag and y:sweep-flag,not a actual point
					QPointF flag = strToPoint(coord);
					//end point
					QPointF endPoint = strToPoint(coord);

					if (type == pathDataType::a)
						endPoint += curr;
					
					SvgPathElementItemData itemData;
					itemData.type = (pathDataType)type;

					itemData.start = curr;
					itemData.end = endPoint;

					qreal startAngle, sweepLength;
					QRectF rect;
					ellipseTransform(curr, endPoint, rxy.x(), rxy.y(), flag.x(), flag.y(), angle.x(), &startAngle, &sweepLength, &rect);
					curr = endPoint;
					itemData.points.append(QPointF(rect.x(), rect.y()));
					itemData.points.append(QPointF(rect.width(), rect.height()));
					itemData.points.append(QPointF(startAngle, sweepLength));
					//add a extra point,for bound calc
					itemData.points.append(QPointF(rect.x(), rect.y()));
					itemData.points.append(QPointF(rect.x() + rect.width(), rect.y() + rect.height()));
					item.data.append(itemData);

				}
				else if (type == pathDataType::C || type == pathDataType::c)
				{
					if (coord.count() < 6)
						break;
					QList<QPointF> ps = strToPoints(coord, 3);
					SvgPathElementItemData itemData;
					itemData.type = (pathDataType)type;
					if (type == pathDataType::c){
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i] + curr);
					}
					else{
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i]);
					}
					itemData.start = curr;
					itemData.end = itemData.points.last();
					curr = itemData.points.last();
					item.data.append(itemData);
				}
				else if (type == pathDataType::S || type == pathDataType::s)
				{
					if (coord.count() < 4)
						break;
					QPointF control = item.data.last().points.at(1);
					QPointF end = item.data.last().points.at(2);

					QPointF controlOpp = control + 2 * (end - control);
					SvgPathElementItemData itemData;
					itemData.points.append(controlOpp);

					QList<QPointF> ps = strToPoints(coord, 2);
					itemData.type = (pathDataType)type;
					if (type == pathDataType::s){
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i] + curr);
					}
					else{
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i]);
					}
					itemData.start = curr;
					itemData.end = itemData.points.last();
					curr = itemData.points.last();
					item.data.append(itemData);
				}
				else if (type == pathDataType::Q || type == pathDataType::q)
				{
					if (coord.count() < 4)
						break;
					QList<QPointF> ps = strToPoints(coord, 2);
					SvgPathElementItemData itemData;
					itemData.type = (pathDataType)type;
					if (type == pathDataType::q){
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i] + curr);
					}
					else{
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i]);
					}
					itemData.start = curr;
					itemData.end = itemData.points.last();
					curr = itemData.points.last();
					item.data.append(itemData);
				}
				else if (type == pathDataType::T || type == pathDataType::t)
				{
					if (coord.count() < 2)
						break;
					QPointF control = item.data.last().points.at(0);
					QPointF end = item.data.last().points.at(1);

					QPointF controlOpp = control + 2 * (end - control);
					SvgPathElementItemData itemData;
					itemData.points.append(controlOpp);

					QList<QPointF> ps = strToPoints(coord, 1);
					
					itemData.type = (pathDataType)type;
					if (type == pathDataType::t){
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i] + curr);
					}
					else{
						for (int i = 0; i < ps.count(); i++)
							itemData.points.append(ps[i]);
					}
					itemData.start = curr;
					itemData.end = itemData.points.last();
					curr = itemData.points.last();
					item.data.append(itemData);
				}
				else{
					break;
				}
			}
			
			m_pathList.append(item);
		} 
		
    }
}
QDomElement SvgPathElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("path");


	QStringList pathData;

	QPointF endPoint;
	qreal rx, ry;
	int largeFlag, sweepFlag, angel;

	QPointF origin = fixedOriginPoint();
	origin -= m_frame.topLeft() + QPointF(m_strokeWidth / 2.f, m_strokeWidth / 2.f);


	for each (SvgPathElementItem item in m_pathList)
	{
		for each (SvgPathElementItemData itemData in item.data)
		{
			switch (itemData.type)
			{
			case pathDataType::M:
			case pathDataType::m:
				pathData.append(QString("%1%2,%3").arg((char)pathDataType::M).arg(origin.x() + itemData.points.first().x() + this->pos().x()).arg(origin.y() + itemData.points.first().y() + this->pos().y()));
				break;
			case pathDataType::L:
			case pathDataType::l:
			case pathDataType::H:
			case pathDataType::h:
			case pathDataType::V:
			case pathDataType::v:
				pathData.append(QString("%1%2,%3").arg((char)pathDataType::L).arg(origin.x() + itemData.points.first().x() + this->pos().x()).arg(origin.y() + itemData.points.first().y() + this->pos().y()));
				break;
			case pathDataType::C:
			case pathDataType::c:
			case pathDataType::S:
			case pathDataType::s:
				pathData.append(QString("%1%2,%3 %4,%5 %6,%7").arg((char)pathDataType::C)
					 .arg(origin.x() + itemData.points.at(0).x() + this->pos().x()).arg(origin.y() + itemData.points.at(0).y() + this->pos().y())
					 .arg(origin.x() + itemData.points.at(1).x() + this->pos().x()).arg(origin.y() + itemData.points.at(1).y() + this->pos().y())
					 .arg(origin.x() + itemData.points.at(2).x() + this->pos().x()).arg(origin.y() + itemData.points.at(2).y() + this->pos().y()));
				break;
			case pathDataType::Q:
			case pathDataType::q:
			case pathDataType::T:
			case pathDataType::t:
				pathData.append(QString("%1%2,%3 %4,%5").arg((char)pathDataType::Q)
					.arg(origin.x() + itemData.points.at(0).x() + this->pos().x()).arg(origin.y() + itemData.points.at(0).y() + this->pos().y())
					.arg(origin.x() + itemData.points.at(1).x() + this->pos().x()).arg(origin.y() + itemData.points.at(1).y() + this->pos().y()));
				break;
			case pathDataType::A:
			case pathDataType::a:
				
				ellipseTransform(itemData.points.at(2).x(), itemData.points.at(2).y(), QRectF(itemData.points.at(0).x(), itemData.points.at(0).y(), itemData.points.at(1).x(), itemData.points.at(1).y()),
					&endPoint, &rx, &ry, &largeFlag, &sweepFlag, &angel);
				pathData.append(QString("%1 %2 %3 %4 %5,%6 %7,%8").arg((char)pathDataType::A).arg(rx).arg(ry).arg(angel)
					.arg(largeFlag).arg(sweepFlag).arg(origin.x() + endPoint.x() + this->pos().x()).arg(origin.y() + endPoint.y() + this->pos().y()));
				break;
			default:
				break;
			}
		}
		if (item.isClosed)
		{
			pathData.append("Z");
		}
	}


	curr.setAttribute("d", pathData.join(" "));

	return curr;
}

void SvgPathElement::updateFrame(){
	//reset frame	
	qreal minx = 999999;
	qreal miny = 999999;
	qreal maxx = -999999;
	qreal maxy = -999999;

	for each (SvgPathElementItem item in m_pathList)
	{
		for each (SvgPathElementItemData itemData in item.data)
		{
			if (itemData.type == pathDataType::A || itemData.type == pathDataType::a){
				for (int i = itemData.points.count() - 2; i < itemData.points.count();i++)
				{
					const QPointF &p = itemData.points.at(i);
					if (minx > p.x())
						minx = p.x();
					if (miny > p.y())
						miny = p.y();

					if (maxx < p.x())
						maxx = p.x();
					if (maxy < p.y())
						maxy = p.y();
				}
			}
			else if (itemData.type == pathDataType::Q || itemData.type == pathDataType::q || itemData.type == pathDataType::T || itemData.type == pathDataType::t){
				QPointF control = itemData.points[0];
				QPointF start = itemData.start;
				QPointF end = itemData.end;
				qreal t = (start.y() - control.y()) / (start.y() - 2 * control.y() + end.y());
				if (t>=0 && t<=1)
				{
					control.setY(control.y() + (itemData.start.y() - control.y())*t);
				}
				if (t>=-1 && t<0)
				{
					control.setY(control.y() + (itemData.start.y() - control.y())*t);
				}

				QList<QPointF> tmp;
				tmp.append(start);
				tmp.append(end);
				tmp.append(control);
				for each (const QPointF &p in tmp)
				{
					if (minx > p.x())
						minx = p.x();
					if (miny > p.y())
						miny = p.y();

					if (maxx < p.x())
						maxx = p.x();
					if (maxy < p.y())
						maxy = p.y();
				}
			}
			else{
				for each (const QPointF &p in itemData.points)
				{
					if (minx > p.x())
						minx = p.x();
					if (miny > p.y())
						miny = p.y();

					if (maxx < p.x())
						maxx = p.x();
					if (maxy < p.y())
						maxy = p.y();
				}
			}
			
		}
	}

	m_frame = QRectF(minx - m_strokeWidth / 2.f, miny - m_strokeWidth / 2.f, (maxx - minx) + m_strokeWidth, (maxy - miny) + m_strokeWidth);
	frameSizeCheck();
}

void SvgPathElement::onResize(QRectF rect){

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


		int iitem = 0;
		for each (SvgPathElementItem item in m_pathList)
		{
			int iitemData = 0;
			for each (SvgPathElementItemData itemData in item.data)
			{
				if (itemData.type == pathDataType::A || itemData.type == pathDataType::a){
					for (int i = itemData.points.count() - 2; i < itemData.points.count(); i++)
					{
						QPointF p = itemData.points.at(i);
						p = QPointF(fixPoint.x() + (p.x() - fixPoint.x())*xScale, fixPoint.y() + (p.y() - fixPoint.y()) *yScale);
						itemData.points.replace(i, p);
					}
				}
				else{
					int i = 0;
					for each (QPointF p in itemData.points)
					{
						p = QPointF(fixPoint.x() + (p.x() - fixPoint.x())*xScale, fixPoint.y() + (p.y() - fixPoint.y()) *yScale);
						itemData.points.replace(i++, p);
					}
				}
				itemData.start = QPointF(fixPoint.x() + (itemData.start.x() - fixPoint.x())*xScale, fixPoint.y() + (itemData.start.y() - fixPoint.y()) *yScale);
				itemData.end = QPointF(fixPoint.x() + (itemData.end.x() - fixPoint.x())*xScale, fixPoint.y() + (itemData.end.y() - fixPoint.y()) *yScale);
				item.data.replace(iitemData++, itemData);
			}
			m_pathList.replace(iitem++, item);
		}

		updateFrame();
		updateShape();
	}
    SvgNode::onResize(rect);
}

uint qHash(QPointF key, uint seed = 0) {
	return uint(key.x()+key.y()) ^ seed; 
}

QList<QPointF> SvgPathElement::tiePoints() {

	QSet<QPointF> set;
	for each (SvgPathElementItem item in m_pathList)
	{
		for each (SvgPathElementItemData itemData in item.data){
			set.insert(itemData.start);
			set.insert(itemData.end);
		}
	}

	
	return set.toList();
}


QList<QPointF> SvgPathElement::alignPoints(QPointF &center){
	QPointF offset = fixedOriginPoint() - m_frame.topLeft() - QPointF(m_strokeWidth / 2., m_strokeWidth / 2.);

	QList<QPointF> list;
	QPointF control;
	qreal t;
	QPointF minx, miny, maxx, maxy;
	bool isInit = false;
	for each (SvgPathElementItem item in m_pathList)
	{
		for each (SvgPathElementItemData itemData in item.data){
			
			switch (itemData.type)
			{

			case pathDataType::C:
			case pathDataType::c:
			case pathDataType::S:
			case pathDataType::s:
				//暂时没用到，没有实现
				break;
			case pathDataType::Q:
			case pathDataType::q:
			case pathDataType::T:
			case pathDataType::t:
				control = itemData.points[0];
				for (int i = 0; i < 100; i++)
				{
					qreal t = i / 100.;
					QPointF p = (1 - t)*(1 - t)*itemData.start + 2 * t*(1 - t)*control + t*t*itemData.end;
					p = Util::rotateWithCenter(p, m_frame.center(), -this->m_rotationAngle);
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
				break;
			case pathDataType::A:
			case pathDataType::a:


				break;
			default:
				break;
			}
		}
	}
	list.append(Util::rotateWithCenter(minx, m_frame.center(), this->m_rotationAngle) + offset);
	list.append(Util::rotateWithCenter(miny, m_frame.center(), this->m_rotationAngle) + offset);
	list.append(Util::rotateWithCenter(maxx, m_frame.center(), this->m_rotationAngle) + offset);
	list.append(Util::rotateWithCenter(maxy, m_frame.center(), this->m_rotationAngle) + offset);

	center = m_frame.center() + offset;
	return list;
}