//
// Created by Patrick O'Brien on 9/18/18.
//

#include <armadillo>
#include <fstream>
#include <bits/shared_ptr.h>
#include "../Lattice/Square.hpp"
#include "../Lattice/Triangular.hpp"

using namespace arma;

#pragma once

class Model {
private:
    int system_size{};
    std::shared_ptr<Lattice> lat;
public:
    virtual double energy() = 0;

    virtual double energy_change(int ind, Site & lattice_s, Spin & old_s, Spin & new_s) = 0;

    virtual Spin new_spin(std::mt19937 & a, std::uniform_int_distribution<int> & b) = 0;

    std::shared_ptr<Lattice> get_lattice(){return lat;};

    void create_random_initial_spin_configuration(std::mt19937 & a, std::uniform_int_distribution<int> & b){
        for (auto &m: lat->get_lattice()) {
            Spin s(new_spin(a, b));
            m.set_spin(s);
        }
    };

    void print_spin_configuration(){for(auto &m: lat->get_lattice()){m.get_spin().print_spin();}
    std::cout << std::endl;};

    void set_system_size(int sys){system_size = sys;};

    int get_system_size(){return system_size;};

    void set_lattice(std::shared_ptr<Lattice> sq){lat = std::move(sq);};

    virtual void update_spin_configuration(int ind, Spin & n_spin) = 0;

    virtual std::stringstream save_spin_configuration(int spin_config_number) = 0;

    virtual void create_ferromagnetic_spin_configuration() = 0;

    Model(std::shared_ptr<Lattice> l, int sys){set_lattice(l); set_system_size(sys);};

//    void set_spin_configuration()
};