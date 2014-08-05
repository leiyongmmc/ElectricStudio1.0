#ifndef GRIDSETTING_H
#define GRIDSETTING_H

#include <QObject>
#include <QMap>
#include <QColor>
#include <QStringList>
#include <QPainter>

#include "appmanager.h"

// 对网格进行设定
class GridSetting : public QObject
{
    Q_OBJECT
public:
    static GridSetting* getGridSetting();
    // 显示网格
    void setShowGrid(bool visible);
    bool getShowGrid() const;
    // 对齐网格
    void setSnaptoGrid(bool snap);
    bool getSnaptoGrid() const;
    // 设置当前网格风格
    void setGridStyle(GridStyle style);
    int getGridStyle() const;
    // 设定指定风格的颜色
    void setColor(GridStyle style, QColor color);
    QColor getColor(GridStyle style);
    // 设置网格距离
    void setSpacing(int spacing);
    int getSpacing() const;
    // 默认的网格距离
    void getDefaultSpacings(QStringList &spacings);
    // 创建位图
    QImage* createIntersectionPixmap(QColor fillColor,int width,int height);

    // 绘制函数
    void drawCoordinate(Qt::Orientation ori, QPainter *painter, const QRectF &rect);
    void drawGridWithIntersection(QPainter *painter, const QRectF &rect);
    void drawGridWithLine(QPainter *painter, const QRectF &rect);
protected:
    explicit GridSetting(QObject *parent = 0);
private:
    // 显示网格
    bool mShowGrid;
    // 网格对齐
    bool mSnaptoGrid;
    // 网格距离单位px
    int  mSpacing;
    // 默认的网格距离
    QStringList mDefaultSpacings;
    // 网格风格
    GridStyle mGridStyle;
    // 网格风格对应的颜色设定
    QMap<GridStyle, QColor> mStyleColors;
    // 背景颜色
    QColor mBgColor;
    // instance
    static GridSetting *mInstance;
};

#endif // GRIDSETTING_H
