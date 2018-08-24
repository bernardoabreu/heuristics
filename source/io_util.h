#ifndef IOUTIL_H
#define IOUTIL_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "util.h"

#define HEADER_SIZE 6

// template<typename T>
// using Matrix = std::vector<std::vector<T> >;


void read_file_to_vector(std::string input_file);

void build_matrix_from_csv(std::string input_file);

void build_matrix_from_csv(std::string input_file);

#endif