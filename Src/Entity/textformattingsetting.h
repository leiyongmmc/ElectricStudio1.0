#ifndef TEXTFORMATTINGSETTING_H
#define TEXTFORMATTINGSETTING_H

#include <QObject>
#include <QFont>
#include <QColor>

#include "entity_global.h"

class ENTITYSHARED_EXPORT TextFormattingSetting
{
public:
    TextFormattingSetting();
    TextFormattingSetting(const TextFormattingSetting &other);

    // 字体 字号 风格 斜体 加粗 下划线
    QString mFamily;
	int mPointSize;
	QFont::Style mStyle;
	bool mItalic;
	bool mBold;
	bool mUnderline;
    // 对齐方式
    Qt::AlignmentFlag   mTextAlignFlag;
    // 字体颜色
    QColor      mTextColor;
};

#endif // TEXTFORMATTINGSETTING_H
