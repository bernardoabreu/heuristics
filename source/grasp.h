#ifndef GRASP_H
#define GRASP_H

#include <vector>
#include "tsp.h"

std::pair<double, std::vector<int> > random_greedy_tsp(const TSP& tsp, double alpha);

std::pair<double, std::vector<int> > grasp_tsp(const TSP& tsp, int max_iterations, double alpha);

#endif