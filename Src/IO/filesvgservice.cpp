#include "filesvgservice.h"
#include "svgnodeelementfactory.h"
#include "svgnodecontainerfake.h"
#include "svgNodeElementImpl/svgcircleelement.h"
#include "svgNodeElementImpl/svgellipseelement.h"
#include "svgNodeElementImpl/svglineelement.h"
#include "svgNodeElementImpl/svgpolygonelement.h"
#include "svgNodeElementImpl/svgpolylineelement.h"
#include "svgNodeElementImpl/svgrectelement.h"
#include "svgNodeElementImpl/svgpathelement.h"
#include "svgNodeElementImpl/svgtextelement.h"
FileSvgService::FileSvgService()
{
}

QList<QSharedPointer<SvgNode>> FileSvgService::List()const {
	QList<QSharedPointer<SvgNode>> list;
    return list;
}


SvgNode *FileSvgService::Get(QString id, QObject *parent) const{

	QFile *xmlFile = new QFile(id);

	if (!xmlFile->open(QIODevice::ReadOnly)){
		return NULL;
	}

	QDomDocument doc;
	if (!doc.setContent(xmlFile)) {
		xmlFile->close();
		return NULL;
	}
	xmlFile->close();

	QDomElement root = doc.documentElement();
	SvgNode *svg = NULL;
	if (root.childNodes().count() == 1){
		svg = SvgNodeElementFactory::createNode(root.childNodes().item(0).toElement());
		if (svg){
			svg->fromXml(root.childNodes().item(0).toElement());
		}
	}
	else{
		svg = new SvgNodeContainerFake();
		svg->fromXml(root);
	}
	svg->createRelations(svg);

	SvgNode *parentNode = qobject_cast<SvgNode*>(parent);
	if (parentNode)
	{
		svg->setParentItem(parentNode);
		svg->setParentNode(parentNode);
		parentNode->add(svg);
	}

	
	/*SvgNode* clone = svg->clone();
	clone->setParentNode(svg);
	svg->add(clone);
	clone->setParentItem(svg);

	SvgRectElement *rect = qobject_cast<SvgRectElement*>(clone->childNode(0));
	rect->setStroke(QColor(Qt::yellow));
	rect->setStrokeWidth(5);*/

	return svg;
}

void FileSvgService::SaveOrUpdate(const SvgNode *obj, QString path) const{
	QFile file(path);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		return;
	}

	QDomDocument doc;

	//ÃèÊöxmlÍ·
	QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'UTF-8\'");
	doc.appendChild(instruction);

	QDomElement root = doc.createElement("svg");
	doc.appendChild(root);

	/*if (svg->frame().width() > 0)
	root.setAttribute("width", QString("%1").arg(svg->frame().x() + svg->frame().width()));
	if (svg->frame().height() > 0)
	root.setAttribute("height", QString("%1").arg(svg->frame().y() + svg->frame().height()));*/
	root.setAttribute("xmlns", QString("http://www.w3.org/2000/svg"));
	root.setAttribute("xmlns:xlink", QString("http://www.w3.org/1999/xlink"));

	obj->toXml(root);

	QTextStream out(&file);
	doc.save(out, 4);
	file.flush();
	file.close();
}


SvgNode* FileSvgService::create(SvgType type, SvgNode *parent) const{
	SvgNode *svg = NULL;
	switch (type)
	{
	case SvgType::SVG_G:
		svg = new SvgNodeContainer();
		break;
	case SvgType::SVG_CIRCLE:
		svg = new SvgCircleElement();
		break;
	case SvgType::SVG_ELLIPSE:
		svg = new SvgEllipseElement();
		break;

	case SvgType::SVG_LINE:
		svg = new SvgLineElement();
		break;
	case SvgType::SVG_PATH:
		svg = new SvgPathElement();
		break;
	case SvgType::SVG_POLYGON:
		svg = new SvgPolygonElement();
		break;
	case SvgType::SVG_POLYLINE:
		svg = new SvgPolylineElement();
		break;
	case SvgType::SVG_RECT:
		svg = new SvgRectElement();
		break;
	case SvgType::SVG_TEXT:
		svg = new SvgTextElement();
		break;
	default:
		break;
	}
	if (parent)
	{
		svg->setParentItem(parent);
		svg->setParentNode(parent);
		parent->add(svg);
	}
	return svg;
}
