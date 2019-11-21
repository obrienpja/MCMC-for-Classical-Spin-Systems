cmake_minimum_required(VERSION 3.10)
project(MCSM)

set(CMAKE_CXX_STANDARD 14)

find_library(MCSM libarmadillo)

include_directories(/gnuplot-iostream)

add_executable(
        MCSM
        main.cpp
#        Model/Heisenberg.cpp
        Algorithm/MonteCarlo.cpp
        Lattice/Square.cpp
        Lattice/Site.hpp
        Lattice/Site.cpp
        Lattice/Triangular.hpp
        Lattice/Triangular.cpp
        Spin/Spin.hpp
        Model/Model.hpp
        Model/Ising.hpp
        Model/Ising.cpp
        Utilities/Output.hpp
#        Plot/MagneticStatePlot.cpp
#        Plot/AverageEnergyPlot.cpp
)

target_link_libraries(MCSM armadillo util boost_iostreams boost_system boost_filesystem)