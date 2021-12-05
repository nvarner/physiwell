#include "manifest.h"

#include <iostream>
#include <sstream>
#include <utility>

Manifest::Manifest(std::string path) : scenarios(), weighted_scenario_indices() {
    std::ifstream manifest(path);

    std::string _;
    std::getline(manifest, _); // Ignore "Standard:" line

    for (std::string line; std::getline(manifest, line);) {
        size_t after_feequency_index;
        int frequency = std::stoi(line, &after_feequency_index);
        std::string scenario_path = "data/scenarios/" + line.substr(after_feequency_index + 1) + ".txt";
        Scenario scenario(scenario_path);

        add_scenario(std::move(scenario), frequency);
    }

    std::random_device dev;
    rng = std::mt19937(dev());
    dist = std::uniform_int_distribution<std::mt19937::result_type>(0, weighted_scenario_indices.size() - 1);
}

void Manifest::add_scenario(Scenario scenario, int weight) {
    for (int i = 0; i < weight; i++) {
        weighted_scenario_indices.push_back(scenarios.size());
    }
    scenarios.push_back(std::move(scenario));
}

const Scenario & Manifest::random_scenario() {
    size_t index = weighted_scenario_indices[dist(rng)];
    return scenarios[index];
}
