#include "tsp.h"
#include <cmath>


TSP::TSP(){
}


TSP::TSP(int dimension, std::string edge_weight_type){
    this->edge_weight_type = edge_weight_type;
    this->cities = std::vector<std::pair<float, float> >(dimension);
}


void TSP::addCity(int index, double x, double y){
    this->cities[index - 1] = std::pair<float, float>(x,y);
}


double euc_2d(std::pair<double, double> coord1, std::pair<double, double> coord2){
    double xd = coord1.first - coord2.first;
    double yd = coord1.second - coord2.second;
    return round( sqrt( xd*xd + yd*yd));
}


double att(std::pair<double, double> coord1, std::pair<double, double> coord2){
    double xd = coord1.first - coord2.first;
    double yd = coord1.second - coord2.second;
    double rij = sqrt((xd*xd + yd*yd) / 10.0);
    double tij = round(rij);

    return (tij < rij) ? (tij + 1) : tij;
}


double TSP::distance(int city1, int city2){
    if(this->edge_weight_type == "EUC_2D"){
        return euc_2d(this->cities[city1], this->cities[city2]);
    }
    else{
        return att(this->cities[city1], this->cities[city2]);
    }
}


int TSP::get_dimension(){
    return this->cities.size();
}


std::ostream& operator<<(std::ostream& out, const TSP& tsp){
    int i = 1;

    for(auto &e : tsp.cities){
        out << i++ << ' ' << e.first << ' ' << e.second << std::endl;
    }
    return out;
}