#ifndef CONTROLS_H
#define CONTROLS_H

#include <QMdiSubWindow>
#include "ui_controls.h"

namespace Ui {
class controls;
}

class controls : public QWidget
{
    Q_OBJECT

public:
    explicit controls(QWidget *parent = nullptr);
    ~controls();
    Ui::controls *ui;

private slots:
    void on_exec_btn_clicked();

};

#endif // CONTROLS_H
