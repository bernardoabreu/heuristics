#include <iostream>
#include <vector>
#include <unistd.h>
#include <ctime>       /* clock_t, clock, CLOCKS_PER_SEC */

#include "io_util.h"
#include "tsp.h"
#include "greedy.h"
#include "local_search.h"


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

    clock_t t;
    
    t = clock();
    result = greedy_tsp(tsp_model);
    result = vnd_tsp(tsp_model, result.second);
    t = clock() - t;

    double total_distance = result.first;
    std::vector<int> cities = result.second;

    for(auto &e : cities){
        std::cout << e << ' ';
    }
    std::cout << std::endl;

    std::cout << "Total distance: " << total_distance 
        << ". Running time: " << ((float)t)/CLOCKS_PER_SEC << "s\n";

    return 0;
}