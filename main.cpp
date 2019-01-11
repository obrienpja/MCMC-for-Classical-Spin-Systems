#include <iostream>
#include <cmath>
#include <memory>
#include <random>
#include <bits/unique_ptr.h>
#include <armadillo>

//#include "Model/Heisenberg.hpp"
#include "Algorithm/MonteCarlo.hpp"
#include "Lattice/Square.hpp"
#include "Lattice/Lattice.hpp"
#include "Model/Ising.hpp"
#include "Plot/MagneticStatePlot.cpp"

using namespace arma;

int main(int argc, char **argv) {
    std::cout << "Phys-sym v. 0.0" << std::endl;
    std::cout << "Simulation software" << std::endl << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl << std::endl;

    int n_x_in = 60;
    int n_y_in = 60;

//    std::cout << "Enter number of unit cells in the x-direction: " <<std::endl;
//    std::cin >> n_x_in;

    Square a(n_x_in, n_y_in);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    std::unique_ptr<Model> is(new Ising(a, n_x_in * n_y_in));

    is->create_random_initial_spin_configuration(mt, dist);
    is->get_lattice().set_neighbors();

    std::cout << "Generating Monte Carlo algorithm..." << std::endl;
    std::unique_ptr<Algorithm> alg(new MonteCarlo);

    const int n_itr(10000000);

    demo_basic(is);

    for (int i = 0; i < 1; i++) {
        alg->simulate(n_itr, is, 8000.25 - 1000.0 * i);
        demo_basic(is);
    }

    return 0;
}