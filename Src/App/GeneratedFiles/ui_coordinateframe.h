/********************************************************************************
** Form generated from reading UI file 'coordinateframe.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COORDINATEFRAME_H
#define UI_COORDINATEFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CoordinateFrame
{
public:

    void setupUi(QFrame *CoordinateFrame)
    {
        if (CoordinateFrame->objectName().isEmpty())
            CoordinateFrame->setObjectName(QStringLiteral("CoordinateFrame"));
        CoordinateFrame->setFrameShadow(QFrame::Raised);
        CoordinateFrame->resize(400, 300);
        CoordinateFrame->setFrameShape(QFrame::StyledPanel);

        retranslateUi(CoordinateFrame);

        QMetaObject::connectSlotsByName(CoordinateFrame);
    } // setupUi

    void retranslateUi(QFrame *CoordinateFrame)
    {
        CoordinateFrame->setWindowTitle(QApplication::translate("CoordinateFrame", "Frame", 0));
    } // retranslateUi

};

namespace Ui {
    class CoordinateFrame: public Ui_CoordinateFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDINATEFRAME_H
