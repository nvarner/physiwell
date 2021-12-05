#ifndef MANIFEST_H
#define MANIFEST_H

#include <random>
#include <string>
#include <vector>

#include "scenario.h"

class Manifest {
public:
    Manifest(std::string path);

    const Scenario & random_scenario();

private:
    std::vector<Scenario> scenarios;
    std::vector<size_t> weighted_scenario_indices;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;

    void add_scenario(Scenario scenario, int weight);
};

#endif
