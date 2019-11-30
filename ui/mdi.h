#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mdi.h"
#include "logs.h"
#include "controls.h"

class MDI : public QMainWindow
{
	Q_OBJECT

public:
	explicit MDI(QWidget *parent = nullptr);
	
public slots:
	void runSimulation();	
	
private:
	void newLoggerWindow();
	void newControllerWindow();
	
	Ui::Form ui;
	QMdiArea *mdiArea;
	logs *logger;
	controls *controller;
	QAction *newAct;
};

#endif
