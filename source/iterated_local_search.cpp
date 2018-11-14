#include "iterated_local_search.h"
#include "local_search.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>


void perturbation(const TSP& tsp, std::pair<double, std::vector<int> > &solution){
    int size = tsp.get_dimension();

    int pos1 = 1 + (rand() % (size / 4));
    int pos2 = pos1 + 1 + (rand() % (size / 4));
    int pos3 = pos2 + 1 + (rand() % (size / 4));

    std::vector<int> new_solution(solution.second);
    int index = 0;

    for(int i = 0; i < pos1; i++){
        new_solution[index++] = solution.second[i];
    }

    for(int i = pos3; i < size; i++){
        new_solution[index++] = solution.second[i];
    }

    for(int i = pos2; i < pos3; i++){
        new_solution[index++] = solution.second[i];
    }

    for(int i = pos1; i < pos2; i++){
        new_solution[index++] = solution.second[i];
    }

    double old_cost = tsp.get_distance(solution.second[pos1 - 1], solution.second[pos1]) +
                      tsp.get_distance(solution.second[pos2 - 1], solution.second[pos2]) +
                      tsp.get_distance(solution.second[pos3 - 1], solution.second[pos3]) +
                      tsp.get_distance(solution.second[size - 1], solution.second[0]);

    double new_cost = tsp.get_distance(solution.second[pos1 - 1], solution.second[pos3]) +
                      tsp.get_distance(solution.second[size - 1], solution.second[pos2]) +
                      tsp.get_distance(solution.second[pos3 - 1], solution.second[pos1]) +
                      tsp.get_distance(solution.second[pos2 - 1], solution.second[0]);

    solution.first += (new_cost - old_cost);
    solution.second.swap(new_solution);
}


std::pair<double, std::vector<int> > ils_tsp(const TSP& tsp, int max_iterations){
    srand(1);

    std::pair<double, std::vector<int> > solution, best_solution;
    solution = twoOpt_tsp(tsp);
    best_solution = solution;

    for(int i = 0; i < max_iterations; i++){
        perturbation(tsp, solution);
        solution = twoOpt_tsp(tsp, solution.second);

        if(solution.first < best_solution.first){
            best_solution = solution;
        }
    }

    return best_solution;
}
