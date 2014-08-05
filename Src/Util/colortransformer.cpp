#include "colortransformer.h"

ColorTransformer::ColorTransformer()
{
}

QColor ColorTransformer::colorFromStr(QString str){
    if(str.startsWith('#')){
       return QColor(str.mid(1,2).toInt(0,16),str.mid(3,2).toInt(0,16),str.mid(5,2).toInt(0,16));
    }
    else if(str.toLower() != "none"){
        return QColor(str);
    }
	return QColor(Qt::GlobalColor::transparent);
}

QString ColorTransformer::colorToStr(const QColor &color){
	if (color == QColor(Qt::GlobalColor::transparent))
	{
		return "none";
	}
	return color.name();
}