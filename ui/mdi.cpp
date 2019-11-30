#include "mdi.h"

#include <QtWidgets>
#include <QMdiArea>
#include "controls.h"
#include <QApplication>
#include "Algorithm/MonteCarlo.hpp"
#include "Lattice/Square.hpp"
#include "Lattice/Triangular.hpp"
#include "Lattice/Lattice.hpp"
#include "Plot/MagneticStatePlot.cpp"
#include "Plot/AverageEnergyPlot.cpp"
#include "Model/Ising.hpp"
#include "Utilities/Output.hpp"

class MdiChild;

QT_BEGIN_NAMESPACE
class QAction;

class QMenu;

class QMdiArea;

class QMdiSubWindow;

QT_END_NAMESPACE

void MDI::runSimulation() {

	this->logger->append("running");

	int x = controller->ui->n_x_in_txt->text().toInt();
	int y = controller->ui->n_y_in_txt->text().toInt();
	Square a(x, y);
	this->logger->append("Lattice vector component: ", a.get_a1()[0]);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    std::unique_ptr<Model> is(new Ising(a, x * y));

    is -> create_random_initial_spin_configuration(mt, dist);
    is -> get_lattice().set_neighbors();

	this->logger->append("Generating Monte Carlo algorithm...");
    std::unique_ptr<Algorithm> alg(new MonteCarlo);

    const int n_itr(1000000);

    std::vector<double> energy_list;
    std::vector<double> temperatures_list;

	std::vector<double> accepted_list;
	std::vector<double> acceptance_list;
	double min_simulation_temperature = 0.000005;
	double max_simulation_temperature = 2.00;
	int number_of_temperature_steps = 41;

    for(int i = 0; i < number_of_temperature_steps + 1; i++)
    {
        temperatures_list.emplace_back(max_simulation_temperature - (max_simulation_temperature - min_simulation_temperature) * i / number_of_temperature_steps);
    }

    for (auto &temperature: temperatures_list) {
        alg->simulate(n_itr, is, temperature, energy_list);
    }

	this->logger->append("The average energy list is:");

    for(auto m:energy_list)
		this->logger->append(m);

    Output out(x, y, "Ising");
    out.createOutputDirectory();

	this->logger->append(out.fullDirectoryString + "/average_energy.png");

    plot_average_energy(temperatures_list, energy_list, \
    (out.fullDirectoryString + "/average_energy.png"), max_simulation_temperature);

    demo_basic(is, (out.fullDirectoryString + "/spin_state.png"));

}

MDI::MDI(QWidget *parent)
		: mdiArea(new QMdiArea) {

	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdiArea);
	setUnifiedTitleAndToolBarOnMac(true);

	QToolBar *fileToolBar = addToolBar(tr("File"));

	const QIcon newIcon = QIcon::fromTheme("document-new");
	newAct = new QAction(newIcon, tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new simulation"));
//	connect(newAct, &QAction::triggered, this, &MDI::newSimulation);
	fileToolBar->addAction(newAct);

	newControllerWindow();
	newLoggerWindow();

	this->logger->append("Phys-sym v. 0.0");
	this->logger->append("Simulation software");
	this->logger->insertSectionBreak();
}

void MDI::newControllerWindow() {
	controller = new controls(nullptr);
	controller->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(controller);

	connect(controller->ui->exec_btn, SIGNAL(clicked()),
			this, SLOT(runSimulation()));

	controller->show();
}

void MDI::newLoggerWindow() {
	logger = new logs();
	logger->setAttribute(Qt::WA_DeleteOnClose);
	mdiArea->addSubWindow(logger);

	// manual size set via this bug https://bugreports.qt.io/browse/QTBUG-70305
	logger->parentWidget()->resize(1000, 300);
	logger->parentWidget()->updateGeometry();

	logger->show();
}