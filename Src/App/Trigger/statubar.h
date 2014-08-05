#ifndef STATUBAR_H
#define STATUBAR_H

#include <QStatusBar>

class StatuBar : public QStatusBar
{
    Q_OBJECT
public:
    StatuBar(QWidget* parent=0);
public slots:
    void slotUpdateMousePos(QPointF pos);
private:
    void init();
};

#endif // STATUBAR_H
