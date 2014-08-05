#ifndef PROPERTIESANDSTYLEWIDGET_H
#define PROPERTIESANDSTYLEWIDGET_H

#include <QDialog>
#include "../appmanager.h"

class QGridLayout;
class QLabel;
class QLineEdit;
class PropertiesAndStyleToolBar;
class ElectricPropertyTableWidget;

class SvgNode;


class PropertiesAndStyleWidget : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesAndStyleWidget(QWidget *parent = 0);
    ~PropertiesAndStyleWidget();
    void clearProp();
    void initProp(SvgNode*);
    void saveProps();
private:
    void createLayout();
    void createConnect();
private:
    QGridLayout                         *mGridLayout;
    QLabel                              *mTitle;
    PropertiesAndStyleToolBar           *mToolBar;
    ElectricPropertyTableWidget         *mPropTableWidget;
};

#endif // PROPERTIESANDSTYLEWIDGET_H
