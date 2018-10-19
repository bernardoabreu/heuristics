#include "tabu_search.h"
#include <algorithm>
#include "local_search.h"


bool twoOptTabu(const TSP& tsp, double& best_distance, std::vector<int>& best_tour, TabuList& tabu_list){
    // Get tour size
    int size = tsp.get_dimension();
    bool found = false;
    std::vector<std::pair<int, std::pair<int, int> > > changes(2);
    std::pair<int, int> new_pair, best_change;
    double min_distance = best_distance;

    for (int i = 0; i < size - 1; i++){
        for (int j = i + 1; j < size; j++){
            double diff_distance = twoOptSwap(tsp, best_tour, i, j);
            std::vector<int> v(best_tour);
            std::reverse(v.begin() + i, v.begin() + j + 1);
            if(!tabu_list.contains(v)){
                if(diff_distance < min_distance){
                    min_distance = diff_distance;
                    best_change = std::make_pair(i, j);
                    found = true;
                }
            }
        }
    }

    if(found){
        int i = best_change.first;
        int j = best_change.second;
        std::reverse(best_tour.begin() + i, best_tour.begin() + j + 1);
        best_distance += min_distance;
    }

    return found;
}


void tabu_search(const TSP& tsp, double& best_cost, std::vector<int>& solution,
                 unsigned int max_list_size, int max_iterations){

    std::vector<int> best_neighbor;
    best_cost = tsp.tourDistance(solution);
    TabuList tabu_list;
    tabu_list.push(solution);

    std::vector<int> new_solution;
    double new_cost;

    for(int i = 0; i < max_iterations; i++){
        new_solution = solution;
        new_cost = best_cost;
        if(twoOptTabu(tsp, new_cost, new_solution, tabu_list)){
            if(new_cost < best_cost){
                best_cost = new_cost;
                solution = new_solution;
            }

            tabu_list.push(new_solution);
            if(tabu_list.size() > max_list_size){
                tabu_list.removeFirst();
            }
        }
    }
}


std::pair<double, std::vector<int> > tabu_tsp(const TSP& tsp,
                                              unsigned int max_list_size, int max_iterations){
    std::pair<double, std::vector<int> > solution;

    solution.second = std::vector<int>(tsp.get_dimension());
    std::iota(solution.second.begin(), solution.second.end(), 1);

    tabu_search(tsp, solution.first, solution.second, max_list_size, max_iterations);

    return solution;
}


std::pair<double, std::vector<int> > tabu_tsp(const TSP& tsp, const std::vector<int>& initial_solution,
                                              unsigned int max_list_size, int max_iterations){
    std::pair<double, std::vector<int> > solution;

    solution.second = initial_solution;

    tabu_search(tsp, solution.first, solution.second, max_list_size, max_iterations);

    return solution;
}
