#ifndef LOCAL_H
#define LOCAL_H

#include <vector>
#include "tsp.h"

double twoOptSwap(const TSP& tsp, const std::vector<int>& old_tour, const int& i, const int& j);

std::pair<double, std::vector<int> > twoOpt_tsp(const TSP&);
std::pair<double, std::vector<int> > twoOpt_tsp(const TSP&, const std::vector<int>& initial_solution);

std::pair<double, std::vector<int> > threeOpt_tsp(const TSP&);
std::pair<double, std::vector<int> > threeOpt_tsp(const TSP&, const std::vector<int>& initial_solution);

std::pair<double, std::vector<int> > vnd_tsp(const TSP&);
std::pair<double, std::vector<int> > vnd_tsp(const TSP&, const std::vector<int>& initial_solution);

#endif