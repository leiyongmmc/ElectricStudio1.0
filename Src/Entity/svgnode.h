#ifndef SVGNODE_H
#define SVGNODE_H

#include <QObject>
#include "node.h"
#include "entity_global.h"
#include <QtWidgets/QGraphicsObject>
#include <QtXml/QtXml>
#include "graphprimitiveprop.h"
#include "kunititem.h"
#include "connection.h"

#include "textformattingsetting.h"
#include "shapeformattingsetting.h"


typedef enum{
	SVG_G,
	SVG_CIRCLE,
	SVG_ELLIPSE,
	SVG_LINE,
	SVG_PATH,
	SVG_POLYGON,
	SVG_POLYLINE,
	SVG_RECT,
	SVG_TEXT,
	SVG_UNKONWN,
	SVG_NUM
}SvgType;


class ENTITYSHARED_EXPORT SvgNode : public KUnitItem ,public Node<SvgNode>
{
    Q_OBJECT
public:
    explicit SvgNode(KUnitItem *parent = 0);
	~SvgNode();
	
	SvgNode* clone();

	

	virtual QPainterPath shape()const{
		return m_shape;
	}

	virtual void fromXml(const QDomElement &xml);

	virtual void toXml(QDomElement &parent) const;


	virtual void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget);

    virtual void onMoving();
	virtual void onMoved();
    virtual void onResize(QRectF rect);
	virtual void onRotate();
	virtual void updateTextFormattingSetting(TextFormattingSetting setting);
	virtual void updateShapeFormattingSetting(ShapeFormattingSetting setting);
	virtual ShapeFormattingSetting shapeFormattingSetting();
public:

	virtual SvgType svgType() const {
		return SVG_UNKONWN;
	}

	SvgNode *topParent();

	QList< SvgNode*> allNodes();

	SvgNode *search(QUuid id);

	virtual void createRelations(SvgNode *top);

	bool tiePointCheck(QPointF curr,QPointF *res) ;

	virtual QList<QPointF> tiePoints() {
		return QList<QPointF>();
	}

    void clearProps(){
        m_props.clear();
    }

	const QLinkedList<GraphPrimitiveProp> &props() const{
        return m_props;
    }

    void addProp(const GraphPrimitiveProp& prop){
        m_props.append(prop);
    }

    void movePropUp(const GraphPrimitiveProp& prop){
		Q_UNUSED(prop);
    }

    void movePropDown(const GraphPrimitiveProp& prop){
		Q_UNUSED(prop);
    }

    void removeProp(const GraphPrimitiveProp& prop){
        m_props.removeOne(prop);
    }

	QString className()const{
		return m_className;
	}
	void setClassName(const QString &name){
		this->m_className = name;
	}

	QColor stroke()const{
		return m_stroke;
	}
	void setStroke(const QColor& stroke){
		this->m_stroke = stroke;
	}

	qreal strokeWidth(){
		return m_strokeWidth;
	}
	void setStrokeWidth(qreal width){
		this->m_strokeWidth = width;
	}

	QColor fill(){
		return m_fill;
	}
	void setFill(const QColor& fill){
		this->m_fill = fill;
	}

	bool showTiePoints(){
		return m_showTiePoints;
	}
	void setShowTiePoints(bool flag){
		m_showTiePoints = flag;
	}

	void appendConnection(const connection &conn){
		m_connections.append(conn);
	}

	void removeConnection(const connection &conn){
		m_connections.removeOne(conn);
	}

	void removeConnectionByLine(const ILink *link, bool isStart);

	const QList<connection> &connections()const{
		return m_connections;
	}

	QUuid id() const { return m_id; }

	
	//************************************
	// Method:    boundaryPointsInScene
	// FullName:  SvgNode::boundaryPointsInScene
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: QPointF & left
	// Parameter: QPointF & top
	// Parameter: QPointF & right
	// Parameter: QPointF & bottom
	// ��ȡ��ǰitem�ı߽緶Χ����������ϵ��
	//************************************
	void boundaryRangeInScene(qreal &left, qreal &top, qreal &right, qreal &bottom);


protected:
	bool m_isMoving;

	virtual QVariant	itemChange(GraphicsItemChange change, const QVariant & value);

	bool alignCheck(QPointF &newPosScene, const QPointF &centerScene,  const int rangeStride, const int range, qreal &xdistance, qreal &ydistance);

	//************************************
	// Method:    fixOriginPoint
	// FullName:  SvgNode::fixOriginPoint
	// Access:    protected 
	// Returns:   QT_NAMESPACE::QPointF
	// Qualifier: const
	// ���㵱ǰ �߿����϶����δ��ת��ʵ��ֵ��item����ϵ��
	// �����ǰitem ʹ��transform��ת����resize��תԭ��仯������
	//************************************
	QPointF fixedOriginPoint() const;

	//************************************
	// Method:    alignPoints
	// FullName:  SvgNode::alignPoints
	// Access:    virtual public 
	// Returns:   QList<QPointF>
	// Qualifier:
	// Parameter: QPointF & center
	// ��ȡ��ǰitem��δ��ת�Ķ���㣨item����ϵ�����������ʱʹ����Щ�����ж��Ƿ񿿽�������
	// Ĭ�Ϸ��ص�ǰ ���α߿��4�����㣬����item��������Ӧoverride
	//************************************
	virtual QList<QPointF> alignPoints(QPointF &center);

	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis() = 0;
	void tiePointCheckImpl(QPointF curr,QList<SvgNode*> &res, qreal nNormal) ;
	virtual void fromXmlImpl(const QDomElement &xml) = 0;
	virtual QDomElement toXmlImpl(QDomElement &parent) const = 0;
	virtual void toXmlComplete(QDomElement &current) const;
	virtual void updateFrame() = 0;

	virtual void updateShape();

	void frameSizeCheck();

    QLinkedList<GraphPrimitiveProp> m_props;

    QString m_className;

	//������ɫ
    QColor m_stroke;

	//���ʿ��
	qreal m_strokeWidth;

	//�����ɫ
	QColor m_fill;

	bool m_showTiePoints;

	QPainterPath m_shape;


	QList<connection> m_connections;

	QDomNode m_connectionsDom;

	QUuid m_id;
};
#endif // SVGNODE_H
