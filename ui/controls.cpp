#include "controls.h"

controls::controls(QWidget *parent) :
		QWidget(parent),
    ui(new Ui::controls)
{
    ui->setupUi(this);
}

controls::~controls()
{
    delete ui;
}

void controls::on_exec_btn_clicked()
{

}
