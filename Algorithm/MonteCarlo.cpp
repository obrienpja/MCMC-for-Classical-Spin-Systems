//
// Created by Patrick O'Brien on 9/19/18.
//

#include "MonteCarlo.hpp"
#include "../Model/Model.hpp"
#include <nlohmann/json.hpp>
#include <cmath>
//#include "../Plot/MagneticStatePlot.cpp"
//#include "../Plot/AverageEnergyPlot.cpp"

using json = nlohmann::json;

double MonteCarlo::boltzmann_factor(double eng_change, double temp) {
    return std::exp(-eng_change/temp);
};

void MonteCarlo::simulate(const int nitr, std::unique_ptr<Model> & model_ptr, double temp, std::vector<double> & average_energy_list) {
    std::cout << "The system size is: " << model_ptr->get_system_size() << std::endl;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, model_ptr->get_system_size() - 1);

    std::random_device rd2;
    std::mt19937 mt2(rd2());
    std::uniform_int_distribution<int> dist2(0, 1);

//    std::ofstream output;
//    output.open("output.json");
//
//    json output_json = {
//		{"type", "common_origin"}, {"data", {} }
//	};

//    model_ptr->create_random_initial_spin_configuration(mt2, dist2);

//    demo_basic(model_ptr);

    std::cout << "The energy of the initial spin configuration is: " << std::endl;
    double initial_energy = model_ptr->energy();
    std::cout << initial_energy << std::endl << std::endl;

    int accepted_counter = 0;
//  	output_json["data"].push_back(model_ptr->save_spin_configuration(accepted_counter).str());

    std::cout << "Monte Carlo simulation is running... " << "(" << nitr << " iterations)"
    << std::endl << std::endl;

    for (int i = 0; i < nitr; i++) {
        int random_index(dist(mt));
        Site lattice_site(model_ptr->get_lattice().get_lattice()[random_index]);
        Spin old_spin_vec(lattice_site.get_spin());
        Spin new_spin_vec(0.0, 0.0, -old_spin_vec.get_z());

        double change_eng(model_ptr->energy_change(random_index, lattice_site, old_spin_vec, new_spin_vec));
        double rand_num(dist2(mt2));

        if (std::log(rand_num) < -change_eng/temp) {
//        if (0 >= change_eng) {
            model_ptr->update_spin_configuration(random_index, new_spin_vec);
            add_to_energy_list(change_eng);
            add_to_magnetization_list(model_ptr->get_lattice().calculate_magnetization());
            accepted_counter++;
//            acceptance_list.emplace_back(static_cast<double> (accepted_counter)/(i + 1));
//		  	output_json["data"].push_back(model_ptr->save_spin_configuration(accepted_counter).str());
        }
    }

//    demo_basic(model_ptr);

    std::cout << "The energy of the final spin configuration is: " << std::endl;
    std::cout << model_ptr->energy() << std::endl << std::endl;
//    output << output_json.dump();
//    output.close();

//    std::cout << "The energy list is: " << std::endl;
//    print_energy_list();

    std::vector<double> en = get_energy_list();
    double tot_energy = std::accumulate(en.begin(), en.end(), 0.0);

    average_energy_list.emplace_back((tot_energy + initial_energy*(accepted_counter+1))/(accepted_counter+1)
    /model_ptr->get_system_size());

    std::cout << "The acceptance rate is: " << static_cast<double> (accepted_counter)/nitr << std::endl;


//    plot_average_energy(accepted_list, acceptance_list, "acceptance_plot.png");
}

