#include "svgtextelement.h"
#include <QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QStyle>

#include "../itemcommand.h"

SvgTextElement::SvgTextElement(SvgNode *parent)
	:SvgNodeElement(parent),
	m_lineEditBorderWidth(0),m_x(0), m_y(0),
	m_width(0), m_height(0),
	m_bold(0), m_italic(0), m_underline(0),
	m_fontFamily("Arial"), m_fontSize(24),
	m_fontstyle(QFont::StyleNormal),
	m_color(Qt::black),
	m_textAlignFlag(Qt::AlignLeft)
{
	m_lineEditWidget = NULL;
	m_lineEdit = new QLineEdit();
	m_lineEdit->setPlaceholderText("enter..");
	connect(m_lineEdit, SIGNAL(returnPressed()), this, SLOT(onLineEditKeyPressEvent()));
	
}

SvgTextElement::~SvgTextElement(){
	delete m_lineEdit;
}

void SvgTextElement::paint(QPainter *painter,
	const QStyleOptionGraphicsItem *option,
	QWidget *widget){
	SvgNodeElement::paint(painter, option, widget);

	if (isSelected())
	{
		//painter->drawRect(m_frame);
	}
	else{
		
		
		painter->setBrush(m_fill);

		painter->setFont(font());
		QPen pen = painter->pen();
		pen.setColor(m_color);
		painter->setPen(pen);
		painter->drawText(m_x, m_y - m_height, m_width, m_height, m_textAlignFlag | Qt::AlignVCenter, m_text);

	}
	
	

}

void SvgTextElement::cloneImpl(SvgNode *node){
	SvgNodeElement::cloneImpl(node);
	SvgTextElement *p = qobject_cast<SvgTextElement*>(node);
	if (p)
	{
		p->m_x = m_x;
		p->m_y = m_y;
		p->m_width = m_width;
		p->m_height = m_height;
		p->m_text = m_text;
		p->m_fontFamily = m_fontFamily;
		p->m_fontSize = m_fontSize;
		p->m_bold = m_bold;
		p->m_italic = m_italic;
		p->m_underline = m_underline;
		p->m_textAlignFlag = m_textAlignFlag;
		p->m_color = m_color;
	}

}

QFont SvgTextElement::font() const{
	QFont font;
	font.setPixelSize(m_fontSize);
	font.setFamily(m_fontFamily);
	font.setBold(m_bold);
	font.setItalic(m_italic);
	font.setUnderline(m_underline);

	return font;
}
void SvgTextElement::fromXmlImpl(const QDomElement &xml) {

	m_color = m_fill;

	if (xml.hasAttribute("x"))
		m_x = xml.attribute("x").toDouble();

	if (xml.hasAttribute("y"))
		m_y = xml.attribute("y").toDouble();
	if (xml.hasAttribute("width"))
		m_width = xml.attribute("width").toDouble();

	if (xml.hasAttribute("height"))
		m_height = xml.attribute("height").toDouble();
	
	if (xml.hasAttribute("font-size"))
		m_fontSize = xml.attribute("font-size").toDouble();

	if (xml.hasAttribute("font-family"))
		m_fontFamily = xml.attribute("font-family");

	if (xml.attribute("font-weight") == "bold")
		m_bold = true;
	if (xml.attribute("font-style") == "italic")
		m_italic = true;
	if (xml.attribute("text-decoration") == "underline")
		m_underline = true;

	m_text = xml.text();



}
QDomElement SvgTextElement::toXmlImpl(QDomElement &parent) const{
	QDomElement curr = parent.ownerDocument().createElement("text");

	QPointF origin = fixedOriginPoint();
	QPointF pos = this->pos();

	curr.setAttribute("x", QString("%1").arg(pos.x() + origin.x()));
	curr.setAttribute("y", QString("%1").arg(pos.y() + origin.y() + m_height ));

	curr.setAttribute("width", QString("%1").arg(m_width));
	curr.setAttribute("height", QString("%1").arg(m_height));


	QDomText t = parent.ownerDocument().createTextNode(m_text);
	curr.appendChild(t);

	curr.setAttribute("font-family", m_fontFamily);
	curr.setAttribute("font-size", m_fontSize);

	if (m_bold)
		curr.setAttribute("font-weight", "bold");
	if (m_italic)
		curr.setAttribute("font-style", "italic");
	if (m_underline)
		curr.setAttribute("text-decoration", "underline");

	return curr;
}

void SvgTextElement::toXmlComplete(QDomElement &current) const{
	current.setAttribute("stroke", "#none");
}

void SvgTextElement::updateFrame(){
	//reset frame	
	
	m_frame = QRectF(m_x - m_strokeWidth / 2.f, m_y - m_height - m_strokeWidth / 2.f, m_width + m_strokeWidth, m_height + m_strokeWidth);
	frameSizeCheck();

	this->update(m_frame);
}



void SvgTextElement::onResize(QRectF r){
    QRectF rect = r;

	//fix
	rect = QRectF(rect.x() + m_strokeWidth / 2.f, rect.y() + m_strokeWidth / 2.f, rect.width() - m_strokeWidth, rect.height() - m_strokeWidth);

	m_lineEditWidget->setPos(rect.topLeft());

	m_width = rect.width();
	m_height = rect.height();

	m_x = rect.left();
	m_y = rect.top() + m_height;

	
	
	m_frame = QRectF(rect.x() , rect.y() , rect.width(), rect.height());
	updateLineEditStyle();
	updateFrame();
	updateShape();
    SvgNode::onResize(rect);
}

QVariant SvgTextElement::itemChange(GraphicsItemChange change, const QVariant &value)
{
	
	if (change == ItemPositionChange && scene()) {
		return SvgNodeElement::itemChange(change, value);
	}
	else if (change == ItemPositionHasChanged) {
		
	}
	else if (change == ItemTransformHasChanged){
		
	}
	else if (change == ItemSelectedHasChanged ) {
		bool state = value.toBool();
		if ( state)
		{
		
			if (!m_lineEditWidget)
			{
				QGraphicsScene *scene = this->scene();
				m_lineEditWidget = scene->addWidget(m_lineEdit);
				m_lineEditWidget->setParentItem(this);
				m_lineEditWidget->setPos(m_x + m_lineEditBorderWidth, m_y - m_height + m_lineEditBorderWidth);
			}
			this->updateLineEditStyle();
			m_lineEdit->setText(m_text);
			m_lineEdit->setFocus();
			m_lineEditWidget->show();
		}
		else{
			if (m_lineEditWidget)
				m_lineEditWidget->hide();
			m_text = m_lineEdit->text();
		}
	}
	return QGraphicsItem::itemChange(change, value);
}

void SvgTextElement::updateTextFormattingSetting(TextFormattingSetting setting)
{
    // use command replace the following code
//    m_fontFamily = setting.mFamily;
//	m_fontSize = setting.mPointSize;
//	m_fontstyle = setting.mStyle;

//	m_bold = setting.mBold;
//	m_italic = setting.mItalic;
//	m_underline = setting.mUnderline;
//    m_textAlignFlag = setting.mTextAlignFlag;
//    m_color = setting.mTextColor;
    TextFormattingSetting preSetting;
    preSetting.mFamily = m_fontFamily;
    preSetting.mPointSize = m_fontSize;
    preSetting.mStyle = m_fontstyle;
    preSetting.mBold = m_bold;
    preSetting.mItalic = m_italic;
    preSetting.mUnderline = m_underline;
    preSetting.mTextAlignFlag = m_textAlignFlag;
    preSetting.mTextColor = m_color;
    ItemCommand::getItemCommand()->getUndoStack()->push(new TextFormattingCommand(this,setting,preSetting));


	updateLineEditStyle();
}

void SvgTextElement::updateLineEditStyle(){
	if (isSelected()){
		QFont font = this->font();
		QFontMetrics fm(font);
		m_lineEdit->setFont(font);

		

		m_lineEdit->setFixedHeight(m_height - 2 * m_lineEditBorderWidth);
		m_lineEdit->setFixedWidth(m_width - 2 * m_lineEditBorderWidth);
		m_lineEdit->setAlignment(m_textAlignFlag);
		QPalette palette = m_lineEdit->palette();
		palette.setColor(QPalette::Text, m_color);
		m_lineEdit->setPalette(palette);
	}
}
void SvgTextElement::onLineEditKeyPressEvent(){
	if (m_lineEditWidget)
		m_lineEditWidget->hide();
	m_text = m_lineEdit->text();

	this->setSelected(false);
}

TextFormattingSetting SvgTextElement::textFormattingSetting()
{
	TextFormattingSetting setting;
	setting.mFamily = m_fontFamily;
	setting.mPointSize = m_fontSize;
	setting.mStyle = m_fontstyle;
	setting.mBold = m_bold;
	setting.mItalic = m_italic;
	setting.mUnderline = m_underline;
	setting.mTextAlignFlag = m_textAlignFlag;
	setting.mTextColor = m_color;

	return setting;
}
