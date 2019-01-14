//
// Created by solidangle on 1/14/19.
//

#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <cstdio>
#include <boost/tuple/tuple.hpp>
#include <boost/foreach.hpp>

#include "gnuplot-iostream.h"
#include "../Model/Model.hpp"

#ifndef M_PI
#	define M_PI 3.14159265358979323846
#endif

#pragma once
void plot_average_energy(std::vector<double> temp_list, std::vector<double> average_energy_list) {
    Gnuplot gp;

    std::vector<boost::tuple<double, double> > pts_A;

    for(int i = 0; i < temp_list.size(); i++)
        pts_A.emplace_back(boost::make_tuple(temp_list[i], average_energy_list[i]));

    gp << "set xr [0:8001]\n";
    gp << "set yr [-2:2]\n";
//    gp << "unset tics\n";
//    gp << "unset border\n";
//    gp << "set size sq\n";
    gp << "set output 'average_energy.png'\n";
//    gp << "set term x11\n";
//    gp << "set style line 1 lt 1 lc rgb \"black\" lw 2\n";
//    gp << "set style fill solid 2.0 noborder\n";
//    gp << "set title \"Ising Model: " << nx << " x " << ny << " Unit Cells\"\n";

//    for(int i = 0; i < ny; i++)
//        gp << std::string("set arrow ") + std::to_string(i + 1) + " from " + "0," + std::to_string(i) + " to " + std::to_string(nx - 1) + "," + std::to_string(i) + " nohead ls 1\n";
//
//    for(int i = 0; i < nx; i++)
//        gp << std::string("set arrow ") + std::to_string(i + ny + 1) + " from " + std::to_string(i) + ",0 to " + std::to_string(i) + "," + std::to_string(ny - 1) + " nohead ls 1\n";

//    std::string col;

//    for (int i = 0; i < nx*ny; i++) {
//        if(model_ptr->get_lattice().get_lattice()[i].get_spin().get_z() < 0.0)
//            col = "\"navy\"";
//        else
//            col = "\"red\"";
//
//        int x_coord(model_ptr->get_lattice().get_lattice()[i].get_x());
//        int y_coord(model_ptr->get_lattice().get_lattice()[i].get_y());
//
//        gp << "set object " + std::to_string(i+1) + " circle at " +
//              std::to_string(x_coord) + "," + std::to_string(y_coord) +
//              " size first 0.40 fc rgb " + col + " front\n";
//    }

    gp << "plot '-' with lines title 'pts_A'\n";
    gp.send1d(pts_A);

//    gp << "set sample 5000\n";
//    gp << "p -4 ls 1 notitle\n";

//    gp << "replot\n";
}