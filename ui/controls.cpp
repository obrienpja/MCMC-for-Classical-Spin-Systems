#include <QIntValidator>
#include "controls.h"

controls::controls(QWidget *parent) :
		QWidget(parent),
    ui(new Ui::controls)
{
    ui->setupUi(this);
	ui->n_x_in_txt->setValidator( new QIntValidator(0, 100, this) );
	ui->n_y_in_txt->setValidator( new QIntValidator(0, 100, this) );
}

controls::~controls()
{
    delete ui;
}

void controls::on_exec_btn_clicked()
{

}
