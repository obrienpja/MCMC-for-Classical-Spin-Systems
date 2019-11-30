#include "logs.h"

logs::logs(QWidget *parent) :
		QWidget(parent),
		ui(new Ui::logs)
{
	ui->setupUi(this);
}

void logs::insertSectionBreak() {
	this->ui->logs_te->append("-----------------------------------------------------");
}

logs::~logs()
{
	delete ui;
}

void logs::on_clear_btn_clicked()
{
    this->ui->logs_te->clear();
}
