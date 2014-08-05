#include "gridsetting.h"
#include <QApplication>
#include <QColor>
#include <QImage>
#include <QPixmap>

GridSetting* GridSetting::mInstance = NULL;

GridSetting* GridSetting::getGridSetting()
{
    if(!mInstance)
        mInstance = new GridSetting();

    return mInstance;
}


void GridSetting::setShowGrid(bool visible)
{
    mShowGrid = visible;
}

bool GridSetting::getShowGrid() const
{
    return mShowGrid;
}

void GridSetting::setSnaptoGrid(bool snap)
{
    mSnaptoGrid = snap;
}

bool GridSetting::getSnaptoGrid() const
{
    return mSnaptoGrid;
}

void GridSetting::setGridStyle(GridStyle style)
{
    if(style < 0 || style >= GridStyle_Cnt)
        return;

    mGridStyle = style;
}

int GridSetting::getGridStyle() const
{
    return mGridStyle;
}

void GridSetting::setColor(GridStyle style, QColor color)
{
    if(style < 0 || style >= GridStyle_Cnt)
        return;

    mStyleColors.insert(style,color);
}

QColor GridSetting::getColor(GridStyle style)
{
    if(style <0|| style >= GridStyle_Cnt)
        return QColor();

    return mStyleColors.value(style);
}

void GridSetting::setSpacing(int spacing)
{
    mSpacing = spacing;
}

int GridSetting::getSpacing() const
{
    return mSpacing;
}

void GridSetting::getDefaultSpacings(QStringList &spacings)
{
    spacings.clear();
    spacings = QStringList(mDefaultSpacings);
}


GridSetting::GridSetting(QObject *parent) :
    QObject(parent)
{
    mShowGrid = true;
    mSnaptoGrid = true;
    mSpacing = 10;
    mDefaultSpacings << "10" << "20" << "30" << "40" << "50" << "100";
    mGridStyle = GridStyle_Intersection;
    mStyleColors.clear();
    mStyleColors.insert(GridStyle_Line,QColor(219,240,219,255));
    mStyleColors.insert(GridStyle_Intersection,QColor(0,0,255,255));
    mBgColor = Qt::white;
}

QImage* GridSetting::createIntersectionPixmap(QColor fillColor,int width,int height)
{
    // to do
    return new QImage();
}

void GridSetting::drawCoordinate(Qt::Orientation ori,QPainter *painter,const QRectF &rect)
{
    painter->save();
    painter->setPen(QPen(Qt::gray,1,Qt::SolidLine));

    const double size = (ori == Qt::Horizontal ? rect.width() :  rect.height());

    int stickLength = 5;

    for(int i = mSpacing; i < size; i += mSpacing)
    {
        if(i % 10 == 0)
            stickLength = 10;
        if(i % 50 == 0 && i > 0)
        {
            painter->save();
            painter->setPen(QPen(Qt::black));
            //painter->setFont(QFont("Arial",7,QFont::Bold));

            if(ori == Qt::Horizontal)
            {
                painter->drawText( i, 20, 28, 15, Qt::AlignLeft, QString::number(i));
            }
            else
            {
                painter->drawText( 20, i, 28, 15, Qt::AlignLeft, QString::number(i));
            }

            stickLength = 15;
            painter->restore();
        }

        if(ori == Qt::Horizontal)
        {
            painter->drawLine(QPoint(i,0),QPoint(i,stickLength));
        }
        else
        {
            painter->drawLine(QPoint(0,i),QPoint(stickLength,i));
        }
    }

    painter->restore();
}

void GridSetting::drawGridWithIntersection(QPainter *painter,const QRectF &rect)
{
    painter->save();
    painter->setPen(this->getColor(GridStyle_Intersection));
    const double w = rect.width();
    const double h = rect.height();

    for(int i = mSpacing; i < w; i += mSpacing)
    {
        for(int j = mSpacing; j < h; j += mSpacing)
        {
            painter->drawPoint(i,j);
        }
    }

    painter->restore();
}

void GridSetting::drawGridWithLine(QPainter *painter,const QRectF &rect)
{
    painter->save();
    painter->setPen(QPen(this->getColor(GridStyle_Line),1,Qt::SolidLine));

    const double w = rect.width();
    const double h = rect.height();

    for(int i = mSpacing; i < w; i += mSpacing)
    {
        painter->drawLine(QPoint(i,0),QPoint(i,h));
        for(int j = mSpacing; j < h; j += mSpacing)
        {
            painter->drawLine(QPoint(0,i),QPoint(w,i));
        }
    }

    painter->restore();
}




