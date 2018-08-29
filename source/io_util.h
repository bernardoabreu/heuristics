#ifndef IOUTIL_H
#define IOUTIL_H

#include <fstream>
#include <vector>
#include <iostream>

#include "tsp.h"
#include "util.h"


void read_file(std::string input_file, TSP& tsp_model);

#endif