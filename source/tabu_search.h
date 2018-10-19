#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include <vector>
#include "tsp.h"
#include "tabu_list.h"

void tabu_search(const TSP& tsp, int neighborhood_size, double& best_cost, std::vector<int>& solution,
                 int max_list_size, int max_iterations);

std::pair<double, std::vector<int> > tabu_tsp(const TSP& tsp,
                                              unsigned int max_list_size, int max_iterations);

std::pair<double, std::vector<int> > tabu_tsp(const TSP& tsp, const std::vector<int>& initial_solution,
                                              unsigned int max_list_size, int max_iterations);

#endif