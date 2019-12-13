#include "chart.h"
#include "ui_chart.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QtCharts>

chart::chart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chart)
{
    ui->setupUi(this);

	auto series = new QtCharts::QLineSeries();
	series->append(0, 6);
	series->append(2, 4);
	
    auto chart_viewport = new QtCharts::QChart(nullptr);
	chart_viewport->addSeries(series);
    ui->graphicsView->setChart(chart_viewport);
    
}

chart::~chart()
{
    delete ui;
}
