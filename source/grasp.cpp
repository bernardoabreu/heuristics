#include "grasp.h"
#include "local_search.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>


std::pair<double, std::vector<int> > random_greedy_tsp(const TSP& tsp, double alpha){
    std::pair<double, std::vector<int> > solution;
    solution.first = 0.0;

    int candidate_set_size = tsp.get_dimension();
    std::vector<std::pair<double, int> > candidate_set(candidate_set_size);

    double cmin = 0.0;
    double cmax = 0.0;
    for(int i = 0; i < tsp.get_dimension(); i++){
        candidate_set[i] = std::make_pair(0.0, i + 1);
    }

    std::vector<std::pair<int, double> > rcl;
    while(candidate_set_size > 0){
        rcl.clear();
        bool is_limit_set = false;

        for(int i = 0; i < candidate_set_size; i++){
            if(candidate_set[i].first <= (cmin + alpha*(cmax - cmin))){
                rcl.push_back(candidate_set[i]);
            }
        }

        int selected_index = rand() % rcl.size();
        solution.first += rcl[selected_index].first;
        solution.second.push_back(rcl[selected_index].second);

        candidate_set_size--;

        for(int i = 0; i < candidate_set_size; i++){
            if(candidate_set[i].second == solution.second.back()){
                std::swap(candidate_set[i], candidate_set[candidate_set_size]);
            }

            candidate_set[i].first = tsp.get_distance(solution.second.back(), candidate_set[i].second);
            if(is_limit_set){
                cmin = std::min(candidate_set[i].first, cmin);
                cmax = std::max(candidate_set[i].first, cmax);
            }
            else{
                cmin = cmax = candidate_set[i].first;
                is_limit_set = true;
            }
        }
    }
    return solution;
}


std::pair<double, std::vector<int> > grasp_tsp(const TSP& tsp, int max_iterations, double alpha){
    srand(time(NULL));

    std::pair<double, std::vector<int> > solution, max_solution;
    max_solution = random_greedy_tsp(tsp, alpha);

    for(int i = 0; i < max_iterations; i++){
        solution = random_greedy_tsp(tsp, alpha);
        solution = vnd_tsp(tsp, solution.second);
        if(solution.first < max_solution.first){
            max_solution = solution;
        }
    }

    return max_solution;
}
