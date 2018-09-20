#include "local_search.h"
#include <numeric>
#include <algorithm>
#include <iostream>


#define NEIGHBORHOODS 2

void twoOptSwap(const std::vector<int>& old_tour, std::vector<int>& new_tour, const int& i, const int& j) {
    int size = old_tour.size();

    // 1. take route[0] to route[i-1] and add them in order to new_route
    for (int c = 0; c <= i - 1; ++c){
        new_tour[c] = old_tour[c];
    }
 
    // 2. take route[i] to route[k] and add them in reverse order to new_route
    int dec = 0;
    for (int c = i; c <= j; ++c, dec++){
        new_tour[c] = old_tour[j - dec];
    }

    // 3. take route[k+1] to end and add them in order to new_route
    for (int c = j + 1; c < size; ++c ){
        new_tour[c] = old_tour[c];
    }
}


bool twoOptNeighborhood(const TSP& tsp, const std::vector<int>& old_tour, double& best_distance, std::vector<int>& best_tour){
    // Get tour size
    int size = tsp.get_dimension();

    std::vector<int> new_tour(size);
 
    best_distance = tsp.tourDistance(old_tour);

    for (int i = 0; i < size - 1; i++){
        for (int j = i + 1; j < size; j++){
            twoOptSwap(old_tour, new_tour, i, j);

            double new_distance = tsp.tourDistance(new_tour);

            if (new_distance < best_distance) {
                best_distance = new_distance;
                best_tour = new_tour;
                return true;
            }
        }
    }
    return false;
}



std::pair<double, std::vector<int> > twoOpt_tsp(const TSP& tsp, const std::vector<int>& initial_solution){
    std::pair<double, std::vector<int> > solution;
    solution.second = initial_solution;

    while(twoOptNeighborhood(tsp, solution.second, solution.first, solution.second));
    return solution;
}



std::pair<double, std::vector<int> > twoOpt_tsp(const TSP& tsp){
    std::pair<double, std::vector<int> > solution;
    solution.second = std::vector<int>(tsp.get_dimension());
    std::iota(solution.second.begin(), solution.second.end(), 1);

    while(twoOptNeighborhood(tsp, solution.second, solution.first, solution.second));
    return solution;
}


void threeOptSwap(const TSP& tsp, const std::vector<int>& old_tour, std::vector<int>& new_tour, const int& i, const int& j, const int& k) {
    new_tour = std::vector<int>(old_tour);

    int a = old_tour[i];
    int b = old_tour[i + 1];
    int c = old_tour[j];
    int d = old_tour[j + 1];
    int e = old_tour[k];
    int f = old_tour[(k + 1) % old_tour.size()];

    int original_dist = tsp.get_distance(a, b) + tsp.get_distance(c, d) + tsp.get_distance(e, f);

    int d1 = tsp.get_distance(a, c) + tsp.get_distance(b, d) + tsp.get_distance(e, f);
    if(d1 < original_dist){
        std::reverse(new_tour.begin() + i, new_tour.begin() + j);
        return;
    }

    int d2 = tsp.get_distance(a, b) + tsp.get_distance(c, e) + tsp.get_distance(d, f);
    if(d2 < original_dist){
        std::reverse(new_tour.begin() + j, new_tour.begin() + k);
        return;
    }

    int d3 = tsp.get_distance(f, b) + tsp.get_distance(c, d) + tsp.get_distance(e, a);
    if(d3 < original_dist){
        std::reverse(new_tour.begin() + i, new_tour.begin() + k);
        std::reverse(new_tour.begin(), new_tour.end());
        return;
    }

    int d4 = tsp.get_distance(a, c) + tsp.get_distance(b, e) + tsp.get_distance(d, f);
    if(d4 < original_dist){
        std::reverse(new_tour.begin() + i, new_tour.begin() + j);
        std::reverse(new_tour.begin() + j, new_tour.begin() + k);
        return;
    }

    int d5 = tsp.get_distance(f, b) + tsp.get_distance(c, e) + tsp.get_distance(d, a);
    if(d5 < original_dist){
        std::reverse(new_tour.begin() + j, new_tour.begin() + k);
        std::reverse(new_tour.begin() + i, new_tour.begin() + k);
        std::reverse(new_tour.begin(), new_tour.end());
        return;
    }

    int d6 = tsp.get_distance(f, c) + tsp.get_distance(b, d) + tsp.get_distance(e, a);
    if(d6 < original_dist){
        std::reverse(new_tour.begin() + i, new_tour.begin() + j);
        std::reverse(new_tour.begin() + i, new_tour.begin() + k);
        std::reverse(new_tour.begin(), new_tour.end());
        return;
    }

    int d7 = tsp.get_distance(a, d) + tsp.get_distance(b, e) + tsp.get_distance(c, f);
    if(d7 < original_dist){
        std::reverse(new_tour.begin() + i, new_tour.begin() + j);
        std::reverse(new_tour.begin() + j, new_tour.begin() + k);
        std::reverse(new_tour.begin() + i, new_tour.begin() + k);
        std::reverse(new_tour.begin(), new_tour.end());
        return;
    }

    return;
}


bool threeOptNeighborhood(const TSP& tsp, const std::vector<int>& old_tour, double& best_distance, std::vector<int>& best_tour){
    // Get tour size
    int size = tsp.get_dimension();

    std::vector<int> new_tour(old_tour);
 
    best_distance = tsp.tourDistance(old_tour);

    for (int i = 0; i < size - 2; i++){
        for (int j = i + 1; j < size - 1; j++){
            for (int k = j + 1; k < size; k++){
                threeOptSwap(tsp, old_tour, new_tour, i, j, k);

                double new_distance = tsp.tourDistance(new_tour);

                if (new_distance < best_distance) {
                    best_distance = new_distance;
                    best_tour = new_tour;
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

    while(threeOptNeighborhood(tsp, solution.second, solution.first, solution.second));
    return solution;
}



std::pair<double, std::vector<int> > threeOpt_tsp(const TSP& tsp){
    std::pair<double, std::vector<int> > solution;
    solution.second = std::vector<int>(tsp.get_dimension());
    std::iota(solution.second.begin(), solution.second.end(), 1);

    while(threeOptNeighborhood(tsp, solution.second, solution.first, solution.second));
    return solution;
}



bool find_best_neighbor(const TSP& tsp, int neighbor, const std::vector<int>& old_tour, double& best_distance, std::vector<int>& best_tour){
    if(neighbor == 0){
        return twoOptNeighborhood(tsp, old_tour, best_distance, best_tour);
    }
    else if(neighbor == 1){
        return threeOptNeighborhood(tsp, old_tour, best_distance, best_tour);
    }

    return false;
}


void vnd(const TSP& tsp, const std::vector<int>& neighborhood, double& best_cost, std::vector<int>& solution){
    std::vector<int> best_neighbor;

    best_cost = tsp.tourDistance(solution);

    int i = 0;
    int neighborhood_size = neighborhood.size();

    while (i < neighborhood_size){
        if(find_best_neighbor(tsp, neighborhood[i], solution, best_cost, solution)){
            i = 0;
        }
        else{
            i++;
        }
    }
}


std::pair<double, std::vector<int> > vnd_tsp(const TSP& tsp){
    int tour_size = tsp.get_dimension();
    std::pair<double, std::vector<int> > solution;

    std::cout << tour_size << std::endl;
    solution.second = std::vector<int>(tour_size);
    std::iota(solution.second.begin(), solution.second.end(), 1);

    std::vector<int> neighborhood(NEIGHBORHOODS);
    std::iota(neighborhood.begin(), neighborhood.end(), 0);

    vnd(tsp, neighborhood, solution.first, solution.second);

    return solution;
}


std::pair<double, std::vector<int> > vnd_tsp(const TSP& tsp, const std::vector<int>& initial_solution){
    std::pair<double, std::vector<int> > solution;

    solution.second = initial_solution;

    std::vector<int> neighborhood(NEIGHBORHOODS);
    std::iota(neighborhood.begin(), neighborhood.end(), 0);

    vnd(tsp, neighborhood, solution.first, solution.second);

    return solution;
}