cmake_minimum_required(VERSION 3.10)
project(MCSM)

set(CMAKE_CXX_STANDARD 14)

find_library(MCSM libarmadillo REQUIRED)
include(GoogleTest REQUIRED)
find_package(GTest REQUIRED)

project(MCSM LANGUAGES CXX)
set(UIS
        ui/mdi.ui
        ui/controls.ui
        ui/logs.ui
        )

set(RESOURCES
        resources.qrc
        )

#set(AUTOGEN_BUILD_DIR "${CMAKE_SOURCE_DIR}/ui")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system filesystem iostreams)
include_directories(${ARMADILLO_INCLUDE_DIRS})
QT5_WRAP_UI(UI_HEADERS ${UIS})
QT5_ADD_RESOURCES(RES_SOURCES ${RESOURCES})
#file(COPY "${AUTOGEN_BUILD_DIR}/ui_*.h" DESTINATION "${CMAKE_SOURCE_DIR}/ui/")


add_library(window ${UI_HEADERS})

include_directories(include ${PROJECT_SOURCE_DIR}/build)

add_executable(
        MCSM
        main.cpp
        ${UI_HEADERS}
        ${RES_SOURCES}
        ${Boost_INCLUDE_DIR}
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
        ui/mdi.h
        ui/mdi.cpp
        ui/controls.h
        ui/controls.cpp
        ui/logs.h
        ui/logs.cpp
        #        Plot/MagneticStatePlot.cpp
        #        Plot/AverageEnergyPlot.cpp
)

target_link_libraries(MCSM ${ARMADILLO_LIBRARIES} util ${Boost_LIBRARIES} Qt5::Widgets)

string(TOLOWER ${CMAKE_SYSTEM_NAME} SYSTEM_NAME)

set_target_properties(MCSM PROPERTIES OUTPUT_NAME "MCSM_${SYSTEM_NAME}")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")

add_executable(
        unit_tests test.cpp
)

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(unit_tests ${GTEST_LIBRARIES} pthread)

