#include <iostream>
#include <cmath>
#include <memory>
#include <random>
#include <memory.h>
#include <armadillo>

//#include "Model/Heisenberg.hpp"
#include "Algorithm/MonteCarlo.hpp"
#include "Lattice/Square.hpp"
#include "Lattice/Triangular.hpp"
#include "Lattice/Lattice.hpp"
#include "Model/Ising.hpp"
#include "Plot/MagneticStatePlot.cpp"
#include "Plot/AverageEnergyPlot.cpp"
#include "Utilities/Output.hpp"

using namespace arma;

int main(int argc, char **argv) {
    std::cout << "Phys-sym v. 0.0" << std::endl;
    std::cout << "Simulation software" << std::endl << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl << std::endl;

    int n_x_in = 20;
    int n_y_in = 20;

//    std::cout << "Enter number of unit cells in the x-direction: " <<std::endl;
//    std::cin >> n_x_in;

    Square a(n_x_in, n_y_in);
    std::cout << "Lattice vector component: " << a.get_a1()[0] << std::endl;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    std::unique_ptr<Model> is(new Ising(a, n_x_in * n_y_in));

    is -> create_random_initial_spin_configuration(mt, dist);
    is -> get_lattice().set_neighbors();

    std::cout << "Generating Monte Carlo algorithm..." << std::endl;
    std::unique_ptr<Algorithm> alg(new MonteCarlo);

    const int n_itr(1000000);

    std::vector<double> energy_list;
    std::vector<double> temperatures_list;

    std::vector<double> accepted_list;
    std::vector<double> acceptance_list;
    double min_simulation_temperature = 0.05;
    double max_simulation_temperature = 1.00;
    int number_of_temperature_steps = 1;

    for(int i = 0; i < number_of_temperature_steps + 1; i++)
    {
        temperatures_list.emplace_back(max_simulation_temperature - (max_simulation_temperature - min_simulation_temperature) * i / number_of_temperature_steps);
    }

    for (auto &temperature: temperatures_list) {
        alg->simulate(n_itr, is, temperature, energy_list);
    }

    std::cout << "The average energy list is: " << std::endl;

    for(auto m:energy_list)
        std::cout << m << std::endl;

    Output out(n_x_in, n_y_in, "Ising");
    out.createOutputDirectory();

    std::cout << (out.fullDirectoryString + "/average_energy.png") << std::endl;

    plot_average_energy(temperatures_list, energy_list, \
    (out.fullDirectoryString + "/average_energy.png"), max_simulation_temperature);

    demo_basic(is, (out.fullDirectoryString + "/spin_state.png"));



    return 0;
}