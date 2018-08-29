#include "greedy.h"
#include <numeric>


std::pair<double, std::vector<int> > greedy_tsp(const TSP& tsp){
    int dimension = tsp.get_dimension();
    int next_city;
    double cur_distance, min_distance;
    double total_distance = 0;

    std::vector<int> path(dimension);
    std::iota(path.begin(), path.end(), 1);

    for(int i = 0; i < (dimension - 1); i++){
        next_city = i + 1;
        min_distance = tsp.get_distance(path[i], path[next_city]);

        for(int j = next_city + 1; j < dimension; j++){
            cur_distance = tsp.get_distance(path[i], path[j]);
            if(cur_distance < min_distance){
                next_city = j;
                min_distance = cur_distance;
            }
        }
        total_distance += min_distance;
        std::swap(path[i + 1], path[next_city]);
    }
    total_distance += tsp.get_distance(path[dimension - 1], path[0]);

    return std::pair<double, std::vector<int> >(total_distance, path);
}
