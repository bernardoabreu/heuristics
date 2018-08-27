#ifndef TSP_H
#define TSP_H

#include <vector>
#include <ostream>


class TSP{
private:
    std::string edge_weight_type;
    std::vector<std::pair<double, double> > cities;
    std::vector<std::vector<double> > distances;

public:
    TSP();

    TSP(int dimension, std::string edge_weight_type);

    void addCity(int index, double  x, double y);

    void calculateDistances();

    inline double get_distance(int city1, int city2) const { return this->distances[city1 - 1][city2 - 1]; }

    inline int get_dimension() const { return this->cities.size(); }

    friend std::ostream& operator<<(std::ostream& out, const TSP& tsp);
};


#endif
