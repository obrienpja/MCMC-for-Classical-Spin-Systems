#include "chart.h"
#include "ui_chart.h"

chart::chart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart)
{
    ui->setupUi(this);
}

chart::~chart()
{
    delete ui;
}
