//
// Created by solidangle on 12/28/18.
//

#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <cstdio>
#include <boost/tuple/tuple.hpp>
#include <boost/foreach.hpp>

#include <gnuplot-iostream/gnuplot-iostream.h>
#include "../Model/Model.hpp"

#ifndef M_PI
#	define M_PI 3.14159265358979323846
#endif

#pragma once
void demo_basic(std::unique_ptr<Model> & model_ptr, const std::string output_file) {
    Gnuplot gp;

    int nx = model_ptr->get_lattice().get_nx();
    int ny = model_ptr->get_lattice().get_ny();
    vec3 a1 = model_ptr->get_lattice().get_a1();
    vec3 a2 = model_ptr->get_lattice().get_a2();

    for(int i = 0; i < ny; i++) {
        vec3 left_point, right_point;
        left_point = i*a2;
        right_point = (nx-1)*a1 + i*a2;
        gp << std::string("set arrow ") + std::to_string(i + 1) + " from " \
        + std::to_string(left_point[0]) + "," + std::to_string(left_point[1]) \
        + " to " + std::to_string(right_point[0]) + "," \
        + std::to_string(right_point[1]) + " nohead ls 1\n";
    }

    for(int i = 0; i < nx; i++) {
        vec3 bottom_point, top_point;
        bottom_point = i * a1;
        top_point =  i * a1 + (ny - 1) * a2;
        gp << std::string("set arrow ") + std::to_string(i + ny + 1) + " from " \
        + std::to_string(bottom_point[0]) + "," + std::to_string(bottom_point[1]) \
        + " to " + std::to_string(top_point[0]) + "," + std::to_string(top_point[1]) + " nohead ls 1\n";
    }

    std::string col;
    for (int i = 0; i < nx*ny; i++) {
        if(model_ptr->get_lattice().get_lattice()[i].get_spin().get_z() < 0.0)
            col = "\"navy\"";
        else
            col = "\"red\"";

        int x_coord(model_ptr->get_lattice().get_lattice()[i].get_x());
        int y_coord(model_ptr->get_lattice().get_lattice()[i].get_y());

        gp << "set object " + std::to_string(i+1) + " circle at " +
        std::to_string(x_coord) + "," + std::to_string(y_coord) +
        " size first 0.40 fc rgb " + col + " front fill solid\n";
    }

    gp << "set xr [" + std::to_string((ny)*a2[0] - 0.5) + ":" + std::to_string((nx)*a1[0] - 0.5) + "]\n";
    gp << "set yr [-0.5:" + std::to_string((ny)*a2[1] - 0.5) + "]\n";
    gp << "unset tics\n";
    gp << "unset border\n";
    gp << "set size sq\n";
    gp << "set term png size 1000, 1000\n";
    gp << "set output '" << output_file << "'\n";
    gp << "set style line 1 lt 1 lc rgb \"black\" lw 2\n";

    gp << "set title \"Ising Model: " << nx << " x " << ny << " Unit Cells\"\n";

    gp << "set sample 5000\n";
    gp << "p -4 ls 1 notitle\n";
}