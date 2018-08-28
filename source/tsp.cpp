#include "tsp.h"
#include <cmath>


TSP::TSP(){
}


TSP::TSP(int dimension, std::string edge_weight_type){
    this->edge_weight_type = edge_weight_type;
    this->cities = std::vector<std::pair<double, double> >(dimension);
    this->distances = std::vector<std::vector<double> >(dimension, std::vector<double>(dimension));
}


void TSP::addCity(int index, double x, double y){
    this->cities[index - 1] = std::pair<double, double>(x,y);
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

void TSP::calculateDistances(){
    int dimension = this->get_dimension();
    for(int i = 0; i < (dimension - 1); i++){
        this->distances[i][i] = 0.0;
        for(int j = (i + 1); j < dimension; j++){
            double distance = (this->edge_weight_type == "EUC_2D") ?
                                euc_2d(this->cities[i], this->cities[j]) :
                                att(this->cities[i], this->cities[j]);
            this->distances[i][j] = distance;
            this->distances[j][i] = distance;
        }
    }
    this->distances[dimension - 1][dimension - 1] = 0.0;
}


std::ostream& operator<<(std::ostream& out, const TSP& tsp){
    int i = 1;

    for(auto &e : tsp.cities){
        out << i++ << ' ' << e.first << ' ' << e.second << std::endl;
    }
    return out;
}
