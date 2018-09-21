#include "local_search.h"
#include <numeric>
#include <algorithm>


#define NEIGHBORHOODS 2


double twoOptSwap(const TSP& tsp, const std::vector<int>& old_tour, const int& i, const int& j) {
    int size = old_tour.size();

    int a1 = (i) ? old_tour[i-1] : old_tour[size - 1];
    int a2 = old_tour[i];
    int b1 = old_tour[j];
    int b2 = old_tour[(j + 1) % size];

    if(a1 == b1 && a2 == b2) return 0.0;

    double old_distance = tsp.get_distance(a1, a2) + tsp.get_distance(b1, b2);
    double new_distance = tsp.get_distance(a1, b1) + tsp.get_distance(a2, b2);

    return new_distance - old_distance;
}


bool twoOptNeighborhood(const TSP& tsp, double& best_distance, std::vector<int>& best_tour){
    // Get tour size
    int size = tsp.get_dimension();


    for (int i = 0; i < size - 1; i++){
        for (int j = i + 1; j < size; j++){
            double diff_distance = twoOptSwap(tsp, best_tour, i, j);

            if(diff_distance < 0){
                best_distance += diff_distance;
                std::reverse(best_tour.begin() + i, best_tour.begin() + j + 1);
                return true;
            }
        }
    }
    return false;
}


std::pair<double, std::vector<int> > twoOpt_tsp(const TSP& tsp, const std::vector<int>& initial_solution){
    std::pair<double, std::vector<int> > solution;
    solution.second = initial_solution;
    solution.first = tsp.tourDistance(solution.second);

    while(twoOptNeighborhood(tsp, solution.first, solution.second));
    return solution;
}


std::pair<double, std::vector<int> > twoOpt_tsp(const TSP& tsp){
    std::pair<double, std::vector<int> > solution;
    solution.second = std::vector<int>(tsp.get_dimension());
    std::iota(solution.second.begin(), solution.second.end(), 1);
    solution.first = tsp.tourDistance(solution.second);

    while(twoOptNeighborhood(tsp, solution.first, solution.second));
    return solution;
}


double threeOptSwap(const TSP& tsp, std::vector<int>& tour, const int& i, const int& j, const int& k) {

    int a = tour[i];
    int b = tour[i + 1];
    int c = tour[j];
    int d = tour[j + 1];
    int e = tour[k];
    int f = tour[(k + 1) % tour.size()];

    double original_dist = tsp.get_distance(a, b) + tsp.get_distance(c, d) + tsp.get_distance(e, f);

    double d1 = tsp.get_distance(a, c) + tsp.get_distance(b, d) + tsp.get_distance(e, f);
    if(d1 < original_dist){
        std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
        return d1 - original_dist;
    }

    double d2 = tsp.get_distance(a, b) + tsp.get_distance(c, e) + tsp.get_distance(d, f);
    if(d2 < original_dist){
        std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
        return d2 - original_dist;
    }

    double d3 = tsp.get_distance(f, b) + tsp.get_distance(c, d) + tsp.get_distance(e, a);
    if(d3 < original_dist){
        std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);
        return d3 - original_dist;
    }

    double d4 = tsp.get_distance(a, c) + tsp.get_distance(b, e) + tsp.get_distance(d, f);
    if(d4 < original_dist){
        std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
        std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
        return d4 - original_dist;
    }

    double d5 = tsp.get_distance(f, b) + tsp.get_distance(c, e) + tsp.get_distance(d, a);
    if(d5 < original_dist){
        std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
        std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);
        return d5 - original_dist;
    }

    double d6 = tsp.get_distance(f, c) + tsp.get_distance(b, d) + tsp.get_distance(e, a);
    if(d6 < original_dist){
        std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
        std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);
        return d6 - original_dist;
    }

    double d7 = tsp.get_distance(a, d) + tsp.get_distance(b, e) + tsp.get_distance(c, f);
    if(d7 < original_dist){
        std::reverse(tour.begin() + i + 1, tour.begin() + j + 1);
        std::reverse(tour.begin() + j + 1, tour.begin() + k + 1);
        std::reverse(tour.begin() + i + 1, tour.begin() + k + 1);
        return d7 - original_dist;
    }

    return original_dist;
}


bool threeOptNeighborhood(const TSP& tsp, double& best_distance, std::vector<int>& best_tour){
    int size = tsp.get_dimension();

    for (int i = 0; i < size - 2; i++){
        for (int j = i + 1; j < size - 1; j++){
            for (int k = j + 1; k < size; k++){
                double new_distance = threeOptSwap(tsp, best_tour, i, j, k);

                if (new_distance < 0) {
                    best_distance += new_distance;
                    return true;
                }
            }
        }
    }
    return false;
}



std::pair<double, std::vector<int> > threeOpt_tsp(const TSP& tsp, const std::vector<int>& initial_solution){
    std::pair<double, std::vector<int> > solution;

    solution.second = initial_solution;

    solution.first = tsp.tourDistance(solution.second);

    while(threeOptNeighborhood(tsp, solution.first, solution.second));
    return solution;
}



std::pair<double, std::vector<int> > threeOpt_tsp(const TSP& tsp){
    std::pair<double, std::vector<int> > solution;

    solution.second = std::vector<int>(tsp.get_dimension());
    std::iota(solution.second.begin(), solution.second.end(), 1);

    solution.first = tsp.tourDistance(solution.second);

    while(threeOptNeighborhood(tsp, solution.first, solution.second));
    return solution;
}



bool find_best_neighbor(const TSP& tsp, int neighbor, double& best_distance, std::vector<int>& best_tour){
    if(neighbor == 0){
        return twoOptNeighborhood(tsp, best_distance, best_tour);
    }
    else if(neighbor == 1){
        return threeOptNeighborhood(tsp, best_distance, best_tour);
    }

    return false;
}


void vnd(const TSP& tsp, int neighborhood_size, double& best_cost, std::vector<int>& solution){
    std::vector<int> best_neighbor;

    best_cost = tsp.tourDistance(solution);

    int i = 0;

    while (i < neighborhood_size){
        if(find_best_neighbor(tsp, i, best_cost, solution)){
            i = 0;
        }
        else{
            i++;
        }
    }
}


std::pair<double, std::vector<int> > vnd_tsp(const TSP& tsp){
    std::pair<double, std::vector<int> > solution;

    solution.second = std::vector<int>(tsp.get_dimension());
    std::iota(solution.second.begin(), solution.second.end(), 1);

    vnd(tsp, NEIGHBORHOODS, solution.first, solution.second);

    return solution;
}


std::pair<double, std::vector<int> > vnd_tsp(const TSP& tsp, const std::vector<int>& initial_solution){
    std::pair<double, std::vector<int> > solution;

    solution.second = initial_solution;

    vnd(tsp, NEIGHBORHOODS, solution.first, solution.second);

    return solution;
}