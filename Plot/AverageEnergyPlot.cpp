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

#include <gnuplot-iostream.h>
#include "../Model/Model.hpp"

#ifndef M_PI
#	define M_PI 3.14159265358979323846
#endif

#pragma once
void plot_average_energy(std::vector<double> temp_list, std::vector<double> average_energy_list, const std::string output_file, double max_temp) {
    Gnuplot gp;

    std::vector<boost::tuple<double, double> > pts_A;

    for(int i = 0; i < temp_list.size(); i++)
        pts_A.emplace_back(boost::make_tuple(temp_list[i], average_energy_list[i]));

    gp << "set xr [0:" << std::to_string(max_temp) << "]\n";
    gp << "set yr [-4:2]\n";
    gp << "set term png size 1000, 1000\n";
    gp << "set output '" << output_file << "'\n";

    gp << "plot '-' with lines title 'Average Energy'\n";
    gp.send1d(pts_A);
}