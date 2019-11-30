#ifndef LOGS_H
#define LOGS_H

#include <QTextEdit>
#include <QString>
#include <QMdiSubWindow>
#include "ui_logs.h"
#include <vector>
#include <sstream>

class logs : public QWidget {
Q_OBJECT

public:
	explicit logs(QWidget *parent = nullptr);

	~logs();

	template<typename P>
	void append(P argA) {
		std::stringstream ss;
		ss << argA;
		auto result = ss.str();
		this->ui->logs_te->append(QString::fromStdString(result));
	}

	template<typename P, typename ...T>
	void append(P argA, T... args) {
		append(argA);
		append(args...);
	}

	void insertSectionBreak();

private slots:
	void on_clear_btn_clicked();

private:
	Ui::logs *ui;

};

#endif
