#ifndef COORDINATEFRAME_H
#define COORDINATEFRAME_H

#include <QFrame>

namespace Ui {
class CoordinateFrame;
}

class CoordinateFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CoordinateFrame(Qt::Orientation ori, QWidget *parent = 0);
    ~CoordinateFrame();

private:
    Ui::CoordinateFrame *ui;

    Qt::Orientation mOri;
};

#endif // COORDINATEFRAME_H
