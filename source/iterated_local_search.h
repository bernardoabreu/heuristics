#ifndef I_LOCAL_H
#define I_LOCAL_H

#include <vector>
#include "tsp.h"

std::pair<double, std::vector<int> > ils_tsp(const TSP& tsp, int max_iterations);

#endif