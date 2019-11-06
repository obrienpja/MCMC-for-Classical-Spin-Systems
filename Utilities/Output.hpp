//
// Created by solidangle on 10/26/19.
//

#include "../Model/Model.hpp"
#include <boost/filesystem.hpp>

class Output{
public:
    std::string directoryString;
    std::string fullDirectoryString;
    Output(int n_x, int n_y, std::string modelString) {
        directoryString = std::to_string(n_x) + "x" + std::to_string(n_y) + "_" + modelString;
    }

    void createOutputDirectory() {
        fullDirectoryString = "/home/solidangle/MCSM Output/" + directoryString;

        boost::filesystem::path dir(fullDirectoryString);
        if(boost::filesystem::create_directory(dir)) {
            std::cout << "Success" << "\n";
        }
    }
};
