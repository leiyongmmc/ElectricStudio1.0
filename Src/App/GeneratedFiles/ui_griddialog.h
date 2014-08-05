/********************************************************************************
** Form generated from reading UI file 'griddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRIDDIALOG_H
#define UI_GRIDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GridDialog
{
public:
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *gridtab;
    QGridLayout *gridLayout_2;
    QCheckBox *checkBox_showgrid;
    QCheckBox *checkBox_snaptogrid;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox_spacings;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_line;
    QRadioButton *radioButton_intersection;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QToolButton *toolButton_color;
    QSpacerItem *horizontalSpacer_2;
    QWidget *objectsnaptab;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLabel *label_7;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QToolButton *toolButton_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *GridDialog)
    {
        if (GridDialog->objectName().isEmpty())
            GridDialog->setObjectName(QStringLiteral("GridDialog"));
        GridDialog->resize(299, 314);
        gridLayout_3 = new QGridLayout(GridDialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tabWidget = new QTabWidget(GridDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        gridtab = new QWidget();
        gridtab->setObjectName(QStringLiteral("gridtab"));
        gridLayout_2 = new QGridLayout(gridtab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        checkBox_showgrid = new QCheckBox(gridtab);
        checkBox_showgrid->setObjectName(QStringLiteral("checkBox_showgrid"));
        checkBox_showgrid->setChecked(true);

        gridLayout_2->addWidget(checkBox_showgrid, 0, 0, 1, 1);

        checkBox_snaptogrid = new QCheckBox(gridtab);
        checkBox_snaptogrid->setObjectName(QStringLiteral("checkBox_snaptogrid"));
        checkBox_snaptogrid->setChecked(true);

        gridLayout_2->addWidget(checkBox_snaptogrid, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(gridtab);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        comboBox_spacings = new QComboBox(gridtab);
        comboBox_spacings->setObjectName(QStringLiteral("comboBox_spacings"));

        horizontalLayout_2->addWidget(comboBox_spacings);

        label_2 = new QLabel(gridtab);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        groupBox = new QGroupBox(gridtab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioButton_line = new QRadioButton(groupBox);
        radioButton_line->setObjectName(QStringLiteral("radioButton_line"));

        gridLayout->addWidget(radioButton_line, 0, 0, 1, 1);

        radioButton_intersection = new QRadioButton(groupBox);
        radioButton_intersection->setObjectName(QStringLiteral("radioButton_intersection"));
        radioButton_intersection->setChecked(true);

        gridLayout->addWidget(radioButton_intersection, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        toolButton_color = new QToolButton(groupBox);
        toolButton_color->setObjectName(QStringLiteral("toolButton_color"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/LineColor.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_color->setIcon(icon);
        toolButton_color->setPopupMode(QToolButton::MenuButtonPopup);

        horizontalLayout->addWidget(toolButton_color);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 3, 0, 1, 1);

        tabWidget->addTab(gridtab, QString());
        objectsnaptab = new QWidget();
        objectsnaptab->setObjectName(QStringLiteral("objectsnaptab"));
        gridLayout_4 = new QGridLayout(objectsnaptab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        groupBox_2 = new QGroupBox(objectsnaptab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setCheckable(true);
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setCheckable(true);
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_5->addWidget(label_4, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_5->addWidget(lineEdit, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 0, 2, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_5->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 1, 2, 1, 1);


        gridLayout_6->addWidget(groupBox_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        toolButton_2 = new QToolButton(groupBox_2);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setIcon(icon);
        toolButton_2->setPopupMode(QToolButton::MenuButtonPopup);

        horizontalLayout_4->addWidget(toolButton_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout_6->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 0, 1, 1);

        tabWidget->addTab(objectsnaptab, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_ok = new QPushButton(GridDialog);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout_3->addWidget(pushButton_ok);

        pushButton_cancel = new QPushButton(GridDialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));

        horizontalLayout_3->addWidget(pushButton_cancel);


        gridLayout_3->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(GridDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GridDialog);
    } // setupUi

    void retranslateUi(QDialog *GridDialog)
    {
        GridDialog->setWindowTitle(QApplication::translate("GridDialog", "Dialog", 0));
        checkBox_showgrid->setText(QApplication::translate("GridDialog", "Show Grid", 0));
        checkBox_snaptogrid->setText(QApplication::translate("GridDialog", "Snap to Grid", 0));
        label->setText(QApplication::translate("GridDialog", "Spacing:", 0));
        label_2->setText(QApplication::translate("GridDialog", "px", 0));
        groupBox->setTitle(QApplication::translate("GridDialog", "Style", 0));
        radioButton_line->setText(QApplication::translate("GridDialog", "Line", 0));
        radioButton_intersection->setText(QApplication::translate("GridDialog", "Intersection", 0));
        label_3->setText(QApplication::translate("GridDialog", "Color:", 0));
        toolButton_color->setText(QApplication::translate("GridDialog", "...", 0));
        tabWidget->setTabText(tabWidget->indexOf(gridtab), QApplication::translate("GridDialog", "Grid", 0));
        groupBox_2->setTitle(QApplication::translate("GridDialog", "Snap to Objects", 0));
        groupBox_3->setTitle(QApplication::translate("GridDialog", "Snap to Margin", 0));
        label_4->setText(QApplication::translate("GridDialog", "Vertical", 0));
        lineEdit->setText(QApplication::translate("GridDialog", "10", 0));
        label_7->setText(QApplication::translate("GridDialog", "px", 0));
        label_6->setText(QApplication::translate("GridDialog", "Horizontal", 0));
        lineEdit_2->setText(QApplication::translate("GridDialog", "10", 0));
        label_8->setText(QApplication::translate("GridDialog", "px", 0));
        label_5->setText(QApplication::translate("GridDialog", "Snap Guide Color:", 0));
        toolButton_2->setText(QApplication::translate("GridDialog", "...", 0));
        tabWidget->setTabText(tabWidget->indexOf(objectsnaptab), QApplication::translate("GridDialog", "Object Snap", 0));
        pushButton_ok->setText(QApplication::translate("GridDialog", "Ok", 0));
        pushButton_cancel->setText(QApplication::translate("GridDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class GridDialog: public Ui_GridDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRIDDIALOG_H
