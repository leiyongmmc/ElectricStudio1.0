/********************************************************************************
** Form generated from reading UI file 'addparamterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPARAMTERDIALOG_H
#define UI_ADDPARAMTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AddParamterDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_name;
    QComboBox *comboBox_type;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;
    QLabel *label_3;
    QLineEdit *lineEdit_value;

    void setupUi(QDialog *AddParamterDialog)
    {
        if (AddParamterDialog->objectName().isEmpty())
            AddParamterDialog->setObjectName(QStringLiteral("AddParamterDialog"));
        AddParamterDialog->resize(268, 167);
        gridLayout = new QGridLayout(AddParamterDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(AddParamterDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(AddParamterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(85, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        lineEdit_name = new QLineEdit(AddParamterDialog);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));

        gridLayout->addWidget(lineEdit_name, 0, 1, 1, 2);

        comboBox_type = new QComboBox(AddParamterDialog);
        comboBox_type->setObjectName(QStringLiteral("comboBox_type"));

        gridLayout->addWidget(comboBox_type, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_ok = new QPushButton(AddParamterDialog);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_cancel = new QPushButton(AddParamterDialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));

        horizontalLayout->addWidget(pushButton_cancel);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 3);

        label_3 = new QLabel(AddParamterDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_value = new QLineEdit(AddParamterDialog);
        lineEdit_value->setObjectName(QStringLiteral("lineEdit_value"));

        gridLayout->addWidget(lineEdit_value, 2, 1, 1, 2);

        QWidget::setTabOrder(lineEdit_name, comboBox_type);
        QWidget::setTabOrder(comboBox_type, lineEdit_value);
        QWidget::setTabOrder(lineEdit_value, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_cancel);

        retranslateUi(AddParamterDialog);

        QMetaObject::connectSlotsByName(AddParamterDialog);
    } // setupUi

    void retranslateUi(QDialog *AddParamterDialog)
    {
        AddParamterDialog->setWindowTitle(QApplication::translate("AddParamterDialog", "Create Property ", 0));
        label->setText(QApplication::translate("AddParamterDialog", "Property Name:", 0));
        label_2->setText(QApplication::translate("AddParamterDialog", "Property Type:", 0));
        pushButton_ok->setText(QApplication::translate("AddParamterDialog", "Ok", 0));
        pushButton_cancel->setText(QApplication::translate("AddParamterDialog", "Cancel", 0));
        label_3->setText(QApplication::translate("AddParamterDialog", "Property Value:", 0));
    } // retranslateUi

};

namespace Ui {
    class AddParamterDialog: public Ui_AddParamterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPARAMTERDIALOG_H
