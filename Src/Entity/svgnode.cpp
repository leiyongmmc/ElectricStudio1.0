#include "svgnode.h"
#include "colortransformer.h"
#include "ILink.h"
#include <QGraphicsScene>
#include "util.h"

#include "itemcommand.h"

SvgNode::SvgNode(KUnitItem *parent)
    :KUnitItem(parent),
      m_stroke(QColor("black")),
      m_strokeWidth(1),
	  m_fill(QColor(Qt::GlobalColor::transparent)),
	  m_showTiePoints(false),
	  m_isMoving(false)
{
	m_parent = NULL;
	m_id = QUuid::createUuid();
	this->setFlag(ItemSendsGeometryChanges, true);
}


SvgNode::~SvgNode()
{

}

SvgNode* SvgNode::clone(){
	SvgNode *node = createThis();
	cloneImpl(node);

	node->updateFrame();
	node->updateShape();

	node->setAngle(m_rotationAngle);

	return node;
}

void SvgNode::cloneImpl(SvgNode *node){
	node->m_stroke = m_stroke;
	node->m_strokeWidth = m_strokeWidth;
	node->m_fill = m_fill;
	node->m_className = m_className;
	node->m_props = m_props;

	//tree
	for each (SvgNode* child in m_childern)
	{
		SvgNode *cloneChild = child->clone();
		
		cloneChild->setParentItem(node);
		cloneChild->m_parent = node;
		node->m_childern.append(cloneChild);
	}
}

void SvgNode::paint(QPainter *painter,
	const QStyleOptionGraphicsItem *option,
	QWidget *widget){
	KUnitItem::paint(painter, option, widget);
	
	if (m_showTiePoints)
	{
		for each (const QPointF &p in tiePoints())
		{
			painter->setBrush(QColor(Qt::black));
			painter->drawEllipse(p, 3, 3);
		}
	}
	
}

void SvgNode::onMoving(){
	this->m_isMoving = true;
	for each ( const connection &conn in m_connections)
	{
		conn.line()->onEndMove(conn.isStart());
	}
}
void SvgNode::onMoved(){
	this->m_isMoving = false;
	QGraphicsScene *scene = this->scene();
	for (int i = 0; i < scene->items().count(); i++)
	{
		QGraphicsItem *item = scene->items().at(i);
		if (dynamic_cast<QGraphicsLineItem*>(item))
		{
			scene->removeItem(item);
			delete item;
			i--;
		}
	}
}

void SvgNode::onResize(QRectF rect){
	for each (const connection &conn in m_connections)
	{
		conn.line()->onEndResize(conn.isStart());
	}
}

void SvgNode::onRotate(){
	qDebug() << "rotate pos" << this->pos() << this->scenePos();
	for each (const connection &conn in m_connections)
	{
		conn.line()->onEndRotate(conn.isStart());
	}
}

void SvgNode::updateTextFormattingSetting(TextFormattingSetting setting)
{
    // sub class implement
}

void SvgNode::updateShapeFormattingSetting(ShapeFormattingSetting setting)
{
// use command replace the following code
//    this->setStroke(setting.mLineColor);
//    this->setStrokeWidth(setting.mLineWidth);
//    this->setFill(setting.mFillColor);
    ItemCommand::getItemCommand()->getUndoStack()->push(new ShapeFormattingCommand(this,
																					setting.mLineColor,
																					setting.mLineWidth,
																					setting.mFillColor,
																					m_stroke,
																					m_strokeWidth,
																					m_fill));

}

ShapeFormattingSetting SvgNode::shapeFormattingSetting()
{
	ShapeFormattingSetting setting;
	setting.mLineColor = m_stroke;
	setting.mLineWidth = m_strokeWidth;
	setting.mFillColor = m_fill;
	return setting;
}

void SvgNode::updateShape(){
	m_shape = QPainterPath();
	m_shape.addRect(m_frame);
}

SvgNode *SvgNode::topParent(){

	SvgNode *top = this;
	while ( top->parentNode() && (top = top->parentNode()) )
		;
	return top;
}

QList< SvgNode*> SvgNode::allNodes(){
	QSet< SvgNode*> set;

	QList<SvgNode *> queue;
	queue.append(topParent());
	while (!queue.empty())
	{
		SvgNode *curr = queue.first();
		set.insert(curr);
		queue.pop_front();
		for each (SvgNode *node  in curr->m_childern)
		{
			queue.append(node);
		}
	}

	return set.toList();
}

SvgNode * SvgNode::search(QUuid id){
	QList<SvgNode *> queue;
	queue.append(this);
	while (!queue.empty())
	{
		SvgNode *curr = queue.first();
		queue.pop_front();

		if (curr->m_id == id)
		{
			return curr;
		}

		for each (SvgNode *node  in curr->m_childern)
		{
			queue.append(node);
		}
	}
	return NULL;
}

void SvgNode::createRelations(SvgNode *top){
	SvgNode *node = this;
	if (node->m_connectionsDom.hasChildNodes())
	{
		for (int i = 0; i < node->m_connectionsDom.childNodes().count(); i++)
		{
			QDomElement e = node->m_connectionsDom.childNodes().at(i).toElement();
			if (e.nodeName() != "connection")
				continue;

			QUuid lineId = e.attribute("lineId");
			//find line
			SvgNode *lineNode = top->search( lineId);
			ILink *line = dynamic_cast<ILink *>(lineNode);
			if (line)
			{
				bool isStart = e.attribute("isStart").toInt();
				connection conn(line, isStart);
				node->m_connections.append(conn);
				
			}
		}
		m_connectionsDom = QDomNode();
	}
}

bool SvgNode::tiePointCheck(QPointF curr,QPointF *res) {
	QList<SvgNode*> svgList;
	tiePointCheckImpl(curr, svgList, 15);

	qreal minDistance = 1.e10;;
	QPointF minDistancePoint;
	SvgNode *minDistanceNode = NULL;
	
	for each (SvgNode* node in svgList)
	{
		for each (const QPointF &point in node->tiePoints())
		{
			QPointF p = node->mapToScene(point);
			qreal distance = (p.x() - curr.x())*(p.x() - curr.x()) + (p.y() - curr.y())*(p.y() - curr.y());
			if (distance < minDistance)
			{
				minDistance = distance;
				minDistancePoint = p;
				minDistanceNode = node;
			}
		}
	}

	if (minDistance < 10*10)
	{
		*res = minDistancePoint;
		return true;
	}

	return false;
}

void SvgNode::tiePointCheckImpl(QPointF curr, QList<SvgNode*> &res, qreal nNormal){
	this->setShowTiePoints(false);
	QPointF currInItem = this->mapFromScene(curr);
	QVector2D v(m_frame.center() - currInItem);
	currInItem = currInItem + v.normalized().toPointF()*nNormal;
	if (this->contains(currInItem))
	{
		res.append(this);
		this->setShowTiePoints(true);
	}
	for each (SvgNode *child in this->m_childern)
	{
		child->tiePointCheckImpl(curr, res, nNormal);
	}
}


void SvgNode::fromXml(const QDomElement &xml){

	if (xml.hasAttribute("class"))
		m_className = xml.attribute("class");
	

	if (xml.hasAttribute("stroke-width"))
		m_strokeWidth = xml.attribute("stroke-width").toDouble();
	if (xml.hasAttribute("stroke")){
		m_stroke = ColorTransformer::colorFromStr(xml.attribute("stroke"));
	}
	if (xml.hasAttribute("fill")){
		m_fill = ColorTransformer::colorFromStr(xml.attribute("fill"));
	}
	if (xml.hasAttribute("id")){
		m_id = xml.attribute("id");
	}

	QDomNodeList subs = xml.childNodes();
	for (int i = 0; i < subs.count(); i++){
		QDomNode xmlNode = subs.item(i);
		if (xmlNode.nodeName() == "connections")
		{
			m_connectionsDom = xmlNode.cloneNode(true);
			break;
		}
	}

	

	fromXmlImpl(xml);

	updateFrame();
	updateShape();

	if (xml.hasAttribute("transform")){
		QString trans = xml.attribute("transform");

		int idx;
		if ((idx = trans.indexOf("scale")) != -1)
		{
			int endTrace = trans.indexOf(")", idx);
			QString scaleStr = trans.left(endTrace).right(endTrace - idx - 6);
			QStringList coord = scaleStr.split(QRegExp("[, \r\n]"), QString::SkipEmptyParts);
			qreal xScale = coord.count() > 0 ? coord[0].toDouble() : 0;
			qreal yScale = coord.count() > 1 ? coord[1].toDouble() : 0;
		}
		if ((idx = trans.indexOf("translate")) != -1)
		{
			int endTrace = trans.indexOf(")", idx);
			QString translateStr = trans.left(endTrace).right(endTrace - idx - 10);
			QStringList coord = translateStr.split(QRegExp("[, \r\n]"), QString::SkipEmptyParts);
			qreal xTrans = coord.count() > 0 ? coord[0].toDouble() : 0;
			qreal yTrans = coord.count() > 1 ? coord[1].toDouble() : 0;
		}
		if ((idx = trans.indexOf("rotate")) != -1)
		{
			int endTrace = trans.indexOf(")", idx);
			QString rotateStr = trans.left(endTrace).right(endTrace - idx - 7);
			QStringList coord = rotateStr.split(QRegExp("[, \r\n]"), QString::SkipEmptyParts);
			qreal angle = coord.count() > 0 ? coord[0].toDouble() : 0;
			qreal ox = coord.count() > 1 ? coord[1].toDouble() : m_frame.center().x();
			qreal oy = coord.count() > 2 ? coord[2].toDouble() : m_frame.center().y();

			this->setAngle(angle);
		}
	}

}

void SvgNode::toXml(QDomElement &parent) const{

	QDomElement curr = toXmlImpl(parent);

	curr.setAttribute("id", QString("%1").arg(m_id.toString()));
	curr.setAttribute("class", m_className);
	curr.setAttribute("stroke-width", QString("%1").arg(m_strokeWidth));
	curr.setAttribute("stroke", ColorTransformer::colorToStr(m_stroke));

	curr.setAttribute("fill", ColorTransformer::colorToStr(m_fill));

	QString transformStr;
	if (this->m_rotationAngle)
	{
		QPointF origin = fixedOriginPoint();
		QPointF center = origin + QPointF((m_frame.width() - m_strokeWidth) / 2.f, (m_frame.height() - m_strokeWidth) / 2.f);
		transformStr.append(QString("rotate(%1 %2 %3)").arg(this->m_rotationAngle).arg(center.x() + pos().x()).arg(center.y() + pos().y()));
	}
	curr.setAttribute("transform", transformStr);

	if (!m_connections.empty())
	{
		QDomElement connections = parent.ownerDocument().createElement("connections");
		int idx = 0;
		for each (const connection& conn in m_connections)
		{
			QDomElement connection = parent.ownerDocument().createElement("connection");
			connection.setAttribute("lineId", QString("%1").arg(conn.line()->getId().toString()));
			connection.setAttribute("isStart", QString("%1").arg(conn.isStart()));
			connections.appendChild(connection);
			idx++;
		}
		curr.appendChild(connections);
	}
	
	toXmlComplete(curr);

	parent.appendChild(curr);
}

void SvgNode::toXmlComplete(QDomElement &current) const{

}


void SvgNode::frameSizeCheck(){
	
	
}


void SvgNode::removeConnectionByLine(const ILink *link, bool isStart){

	for (int i = 0; i < m_connections.count(); i++)
	{
		const connection &conn = m_connections.at(i);
		if (conn.line() == link && conn.isStart() == isStart)
		{
			m_connections.removeAt(i);
			return;
		}
	}
}

QPointF SvgNode::fixedOriginPoint() const{
	QTransform t = this->transform();

	/*x' = m11*x + m21*y + dx
	y' = m22*y + m12*x + dy

	x1=cos(angle)*x-sin(angle)*y;

	y1=cos(angle)*y+sin(angle)*x;*/

	QPointF pTopLeft = t.map(m_frame.topLeft() + QPointF(m_strokeWidth / 2.f, m_strokeWidth / 2.f));

	QPointF pCenter = t.map(m_frame.center());

	return Util::rotateWithCenter(pTopLeft, pCenter, this->m_rotationAngle);

	/*qreal radix = this->m_rotationAngle / 180. * 3.1415926;
	qreal x1 = cos(radix)*(pTopLeft.x() - pCenter.x()) - sin(radix)*(pCenter.y() - pTopLeft.y());
	qreal y1 = cos(radix)*(pCenter.y() - pTopLeft.y()) + sin(radix)*(pTopLeft.x() - pCenter.x());
	y1 = -y1;
	x1 += pCenter.x();
	y1 += pCenter.y();

	return QPointF(x1, y1);*/
}

QVariant SvgNode::itemChange(GraphicsItemChange change, const QVariant &value){
	QGraphicsScene *scene = this->scene();

	//图元吸附的平方距离
	const int squareDistance = 64;
	//网格吸附距离
	const int range = 6;
	//网线吸附步长
	const int rangeStride = 100;
	if (change == ItemPositionChange && scene) {
		const QPointF newPos = value.toPointF();


		//首先进行图元吸附，如果不满足条件再进行网格吸附
		//*************
		//*************图元吸附
		//*************

		//找出最小距离的图元
		
		SvgNode *minNode = NULL;
		QPointF minDistancePoint;
		qreal minSquareDistance = 1.e10;
		QSet<SvgNode *> set;
		for each (const QPointF &p in this->tiePoints()){
			QPointF point = this->mapToScene(p) + newPos - this->pos();
			
			
			QList<SvgNode*> svgList;
			SvgNode *top = topParent();
			top->tiePointCheckImpl(point, svgList, 15);
			this->setShowTiePoints(false);
			for each (SvgNode* node in svgList)
			{
				if (node == this)
					continue;
				set.insert(node);
				for each (QPointF otherPoint in node->tiePoints()){
					otherPoint = node->mapToScene(otherPoint);
					qreal d = (point.x() - otherPoint.x()) * (point.x() - otherPoint.x()) + (point.y() - otherPoint.y()) * (point.y() - otherPoint.y());
					if (d <= squareDistance)
					{
						if (minSquareDistance > d)
						{
							minSquareDistance = d;
							QPointF off = otherPoint - point;
							minDistancePoint = Util::rotateWithCenter(otherPoint, this->mapToScene(m_frame.center()) + newPos - this->pos() + off, this->m_rotationAngle) - 
								Util::rotateWithCenter(point, this->mapToScene(m_frame.center()) + newPos - this->pos(), this->m_rotationAngle);
							minNode = node;
						}
					}
				}

			}
		}

		if (!set.isEmpty())
		{
			for each (SvgNode* node in set)
			{
				node->setShowTiePoints(true);
			}
			this->setShowTiePoints(true);
		}
		
		if (minNode){
			
			
			return newPos + minDistancePoint;
		}
		else{
			//*************
			//*************网格吸附
			//*************
			//step1,删除所有已有的对齐线
			for (int i = 0; i < scene->items().count(); i++)
			{
				QGraphicsItem *item = scene->items().at(i);
				if (dynamic_cast<QGraphicsLineItem*>(item))
				{
					scene->removeItem(item);
					delete item;
					i--;
				}

			}


			//step2，计算顶点到吸附线的距离，最小x和y距离所在点对应新的坐标点

			QPointF center;
			QList<QPointF> alignPoints = this->alignPoints(center);
			center += newPos;
			qreal minxDistance = 1.e10;
			qreal minyDistance = 1.e10;

			bool flag = false;
			QPointF res = newPos;

			for each (const QPointF& offset in alignPoints)
			{
				QPointF p = newPos + offset;
				qreal xdistance, ydistance;
				xdistance = ydistance = 1.e10;
				//判断当前点是否在对齐范围内
				bool flag1 = alignCheck(p, center, rangeStride, range, xdistance, ydistance);
				flag = flag || flag1;

				if (flag1)
				{
					p = p - offset;

					if (minxDistance > xdistance)
					{
						minxDistance = xdistance;
						res.setX(p.x());
					}
					if (minyDistance > ydistance)
					{
						minyDistance = ydistance;
						res.setY(p.y());
					}
				}
			}

			if (flag)
			{
				//step3,根据新坐标点重新计算出4个顶点坐标，获得x最小最大值，y最小最大值
				qreal minx = 1.e10;;
				qreal miny = 1.e10;
				qreal maxx = -1.e10;
				qreal maxy = -1.e10;

				for each (const QPointF& offset in alignPoints)
				{
					QPointF p = res + offset;
					QPointF pCenter = center + res - value.toPointF();
					/*p = this->mapFromScene(p);
					p = this->transform().map(p);
					p = this->mapToScene(p);*/
					p = Util::rotateWithCenter(p, pCenter, -this->m_rotationAngle);
					if (minx > p.x())
						minx = p.x();
					if (miny > p.y())
						miny = p.y();
					if (maxx < p.x())
						maxx = p.x();
					if (maxy < p.y())
						maxy = p.y();
				}


				//step4，当这几个值在对其线上时，绘出对齐线
				if (qRound(minx) % rangeStride == 0)
				{
					QGraphicsLineItem *line = new QGraphicsLineItem(qRound(minx), 0, qRound(minx), 2000);
					QPen pen = line->pen();
					pen.setStyle(Qt::DashLine);
					line->setPen(pen);
					scene->addItem(line);
				}
				if (qRound(miny) % rangeStride == 0)
				{
					QGraphicsLineItem *line = new QGraphicsLineItem(0, qRound(miny), 2000, qRound(miny));
					QPen pen = line->pen();
					pen.setStyle(Qt::DashLine);
					line->setPen(pen);
					scene->addItem(line);
				}
				if (qRound(maxx) % rangeStride == 0)
				{
					QGraphicsLineItem *line = new QGraphicsLineItem(qRound(maxx), 0, qRound(maxx), 2000);
					QPen pen = line->pen();
					pen.setStyle(Qt::DashLine);
					line->setPen(pen);
					scene->addItem(line);
				}
				if (qRound(maxy) % rangeStride == 0)
				{
					QGraphicsLineItem *line = new QGraphicsLineItem(0, qRound(maxy), 2000, qRound(maxy));
					QPen pen = line->pen();
					pen.setStyle(Qt::DashLine);
					line->setPen(pen);
					scene->addItem(line);
				}

				return res;
			}
		}
		
		
	}

	return QGraphicsItem::itemChange(change, value);
}

bool SvgNode::alignCheck(QPointF &newPosScene,const QPointF &centerScene, const int rangeStride, const int range, qreal &xdistance, qreal &ydistance)
{
	//step1，计算当前坐标的真实场景坐标
	QGraphicsScene *scene = this->scene();
	QPointF fixTopLeft = this->fixedOriginPoint();
	QTransform t = this->transform();
	this->resetTransform();
	QPointF tmp = this->mapFromScene(newPosScene);
	//tmp -= m_frame.topLeft() + QPointF(m_strokeWidth / 2., m_strokeWidth / 2.);
	QPointF center = this->mapFromScene(centerScene);
	//center -= m_frame.topLeft() + QPointF(m_strokeWidth / 2., m_strokeWidth / 2.);
	
	tmp = Util::rotateWithCenter(tmp, center, -this->m_rotationAngle);
	//tmp = t.map(tmp);
	//tmp += m_frame.topLeft() + QPointF(m_strokeWidth / 2., m_strokeWidth / 2.);
	tmp = this->mapToScene(tmp);
	this->setTransform(t);

	

	//step2，用真实场景坐标计算对齐线
	bool flag = false;
	QPointF offset(0, 0);
	if (qRound(tmp.x()) % rangeStride < range || qRound(tmp.x()) % rangeStride > rangeStride - range)
	{
		qreal x = int(qRound(tmp.x()) + range) / rangeStride * rangeStride;


		if (xdistance > fabs(x - tmp.x()))
			xdistance = fabs(x - tmp.x());

		//x = this->mapToScene(this->transform().inverted().map(this->mapFromScene(QPointF(x, tmp.y())))).x();

		flag = true;
		offset.setX(x - tmp.x());
		tmp.setX(x);
		

	}


	if (qRound(tmp.y()) % rangeStride < range || qRound(tmp.y()) % rangeStride > rangeStride - range)
	{
		qreal y = int(qRound(tmp.y()) + range) / rangeStride * rangeStride;

		if (ydistance > fabs(y - tmp.y()))
			ydistance = fabs(y - tmp.y());
		//y = this->mapToScene(this->transform().inverted().map(this->mapFromScene(QPointF(tmp.x(), y)))).y();

		flag = true;
		offset.setY(y - tmp.y());
		tmp.setY(y);
	}
	if (flag){
		
		//newPos = this->mapToScene(this->transform().inverted().map(this->mapFromScene(tmp)));

		QPointF p = tmp;
		center = centerScene+ offset;

		newPosScene = Util::rotateWithCenter(p, center, this->m_rotationAngle);
	}

	
	return flag;
}

QList<QPointF> SvgNode::alignPoints(QPointF &center){
	QList<QPointF> list;
	QPointF fixLeftTop = fixedOriginPoint();

	list.append(QPointF(0, 0) + fixLeftTop);
	list.append(QPointF(0, m_frame.height() - m_strokeWidth) + fixLeftTop);
	list.append(QPointF(m_frame.width() - m_strokeWidth, 0) + fixLeftTop);
	list.append(QPointF(m_frame.width() - m_strokeWidth, m_frame.height() - m_strokeWidth) + fixLeftTop);

	center = (QPointF(m_frame.width() - m_strokeWidth, m_frame.height() - m_strokeWidth)) / 2. + fixLeftTop;;

	return list;
}

void SvgNode::boundaryRangeInScene(qreal &left, qreal &top, qreal &right, qreal &bottom){
	QPointF center;
	QList<QPointF> list = this->alignPoints(center);
	QTransform t = this->transform();
	this->resetTransform();
	left = top = 1.e10;
	right = bottom = -1.e10;
	for each(const QPointF &p in list)
	{
		QPointF pScene = this->mapToScene(Util::rotateWithCenter(p, center, -this->m_rotationAngle));
		if (left > pScene.x())
			left = pScene.x();
		if (top > pScene.y())
			top = pScene.y();
		if (right < pScene.x())
			right = pScene.x();
		if (bottom < pScene.y())
			bottom = pScene.y();
	}

	this->setTransform(t);
}
