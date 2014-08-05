#ifndef GRIDDIALOG_H
#define GRIDDIALOG_H

#include <QDialog>

namespace Ui {
class GridDialog;
}

class GridDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GridDialog(QWidget *parent = 0);
    ~GridDialog();
    void setCurrentTab(int index);
private:
    void init();
    void initGridPage();
private:
    Ui::GridDialog *ui;
};

#endif // GRIDDIALOG_H
