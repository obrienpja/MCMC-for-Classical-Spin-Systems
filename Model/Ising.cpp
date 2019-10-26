//
// Created by solidangle on 10/25/18.
//

#include <random>
#include "Ising.hpp"
#include "../Lattice/Square.hpp"

double Ising::energy(){
    double tot_eng(0.0);
    double J(1.0);

    for(auto &m: get_lattice().get_lattice()) {
        tot_eng += -J * ((m.get_spin()).dot((m.get_neighbors()[0])->get_spin()));
        tot_eng += -J * ((m.get_spin()).dot((m.get_neighbors()[1])->get_spin()));
    }

    return tot_eng;
}

double Ising::energy_change(int ind, Site & lattice_s, Spin & old_s, Spin & new_s){
    double tot_eng = 0.0;
    double J = 1.0;

    Spin spin_difference(new_s - old_s);

    for(auto &m: lattice_s.get_neighbors())
        tot_eng += -J * spin_difference.dot(m->get_spin());

    return tot_eng;
}

Spin Ising::new_spin(std::mt19937 & a, std::uniform_int_distribution<int> & b){
    return {0.0, 0.0, 2.0*b(a) - 1.0};
}

void Ising::update_spin_configuration(int ind, Spin & n_spin) {
    get_lattice().get_lattice()[ind].set_spin(n_spin);
}

std::stringstream Ising::save_spin_configuration(int spin_config_number){
    std::stringstream output;

//    output << "{\"step\": " << spin_config_number << ", \"data\": [";
//
//    for (int i = 0; i < (getSystemSize()) - 1; i++) {
//        output << "{\"spin_number\": " << i << "," << "\"x\": " << (spin_config)(i, 0) << "," << "\"y\": "
//               << (spin_config)(i, 1) << "," << "\"z\": " << (spin_config)(i, 2) << "}, ";
//    }
//
//    output << "{\"spin_number\": " << (system_size) - 1 << "," << "\"x\": "
//           << (spin_config)((system_size) - 1, 0) << "," << "\"y\": "
//           << (spin_config)((system_size) - 1, 1) << "," << "\"z\": "
//           << (spin_config)((system_size) - 1, 2) << "}]}";

    return output;
}

void Ising::create_ferromagnetic_spin_configuration() {
    for (auto &m: get_lattice().get_lattice()) {
        m.set_spin(Spin(0.0, 0.0, 1.0));
    }
}