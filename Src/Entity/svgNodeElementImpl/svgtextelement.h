#ifndef SVGTEXTELEMENT_H
#define SVGTEXTELEMENT_H

#include "../svgnodeelement.h"
#include <QString>
#include "../textformattingsetting.h"

class QLineEdit;
class QGraphicsProxyWidget;
class ENTITYSHARED_EXPORT SvgTextElement : public SvgNodeElement
{

	Q_OBJECT
public:
	SvgTextElement(SvgNode *parent = 0);

	~SvgTextElement();

	virtual void paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option,
		QWidget *widget = 0);

    virtual void onResize(QRectF r);

    virtual void updateTextFormattingSetting(TextFormattingSetting setting);
	TextFormattingSetting textFormattingSetting();

	virtual SvgType svgType() const {
		return SVG_TEXT;
	}

	QString text() const{
		return m_text;
	}
	void setText(QString text){
		m_text = text;
		updateFrame();
	}

	void setFontSize(int pixelSize){
		m_fontSize = pixelSize;
		updateFrame();
	}

	void setFontFamily(QString family){
		m_fontFamily = family;
		updateFrame();
	}

    void setFontStyle(QFont::Style style)
    {
        m_fontstyle = style;
        updateFrame();
    }

	void setBold(bool value){
		m_bold = value;
	}

	void setItalic(bool value){
		m_italic = value;
	}

	void setUnderline(bool value){
		m_underline = value;
	}

    void setAlignFlag(Qt::AlignmentFlag flag){
        m_textAlignFlag = flag;
    }

    void setTextColor(const QColor & color)
    {
        m_color = color;
    }


	QFont font() const;

protected:
	virtual QVariant	itemChange(GraphicsItemChange change, const QVariant & value);
	virtual void cloneImpl(SvgNode *node);
	virtual SvgNode* createThis(){ return new SvgTextElement; }
	virtual void fromXmlImpl(const QDomElement &xml);
	virtual QDomElement toXmlImpl(QDomElement &parent) const;
	void toXmlComplete(QDomElement &current) const;
	virtual void updateFrame();

	void updateLineEditStyle();
	
	
private slots :
	void onLineEditKeyPressEvent();

	
private:

	qreal m_lineEditBorderWidth;

	QGraphicsProxyWidget *m_lineEditWidget;
	QLineEdit *m_lineEdit;
	qreal m_width;
	qreal m_height;



	qreal m_x;
	qreal m_y;
	
	QString m_text;

	qreal m_fontSize;
	QString m_fontFamily;
    QFont::Style m_fontstyle;
	bool m_bold;
	bool m_italic;
    bool m_underline;
    Qt::AlignmentFlag   m_textAlignFlag;
    QColor      m_color;
};

#endif // SVGTEXTELEMENT_H
