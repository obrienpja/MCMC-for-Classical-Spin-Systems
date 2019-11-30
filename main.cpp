#include <iostream>
#include <cmath>
#include <memory>
#include <random>
#include <memory.h>
#include <armadillo>
#include <QApplication>
#include "ui/mdi.h"

using namespace arma;

int main(int argc, char **argv) {
	QApplication app(argc, argv);

	app.setStyleSheet(R"V0G0N(
    QPushButton
		{
            border: 1px solid gray;
			background-color:#d4d0c8;
		}

QPushButton:hover
		{
            border: 1px solid gray;
			background-color:#B9B4A8;
		}

QPushButton:pressed
		{
            border-top: 2px solid black;
            border-left: 2px solid black;
            border-right: 1px solid gray;
            border-bottom: 1px solid gray;
			background-color:#8C887F;
		}

)V0G0N");
	
	QWidget *widget = new MDI;
	widget->show();
	return app.exec();
}
