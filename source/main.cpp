#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include "io_util.h"
#include "tsp.h"
#include "greedy.h"


int main (int argc, char **argv){
    char *cvalue = NULL;
    std::string input_file, output_file;
    int c;
    opterr = 0;

    input_file = "";
    output_file = "out";

    while ((c = getopt(argc, argv, "f:o:")) != -1){
        switch (c)
        {
            case 'f':
                cvalue = optarg;
                input_file = std::string(cvalue);
                break;
            case 'o':
                cvalue = optarg;
                output_file = std::string(cvalue);
                break;
            case '?':
                if (optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }


    TSP tsp_model;
    std::pair<double, std::vector<int> > result;

    read_file(input_file, tsp_model);

    tsp_model.calculateDistances();

    result = greedy_tsp(tsp_model);

    double total_distance = result.first;
    std::vector<int> cities = result.second;

    for(auto &e : cities){
        std::cout << e << ' ';
    }
    std::cout << std::endl;

    std::cout << "Total distance: " << total_distance << std::endl;


    return 0;
}