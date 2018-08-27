#ifndef TSP_H
#define TSP_H


// #include <utility>
#include <vector>
#include <ostream>


class TSP{
private:
    int dimension;
    std::string edge_weight_type;
    std::vector<std::pair<float, float> > cities;

public:
    TSP();

    TSP(int dimension, std::string edge_weight_type);

    void addCity(int index, double  x, double y);

    double distance(int, int);

    int get_dimension();

    friend std::ostream& operator<<(std::ostream& out, const TSP& tsp);
};


#endif
