#include "io_util.h"


void __read_file(std::istream& myfile, TSP& tsp_model){
    std::string line, edge_weight_type;
    int dimension, index;
    double x, y;

    for(int i = 0; i < HEADER_SIZE; i++){
        getline(myfile, line);
        std::vector<std::string> v = split<std::vector<std::string> >(line, ':');

        if(v[0] == "DIMENSION"){
            dimension = str2num<int>(v[1]);
        }
        else if(v[0] == "EDGE_WEIGHT_TYPE"){
            edge_weight_type = v[1];
        }
    }

    tsp_model = TSP(dimension, edge_weight_type);

    for(int i = 0; i < dimension; i++){
        myfile >> index >> x >> y;
        tsp_model.addCity(index, x, y);
    }

}


void read_file(std::string input_file, TSP& tsp_model){

    if(input_file == ""){
        __read_file(std::cin, tsp_model);
    }
    else{
        std::ifstream myfile(input_file.c_str());
        if (myfile.is_open()){
            __read_file(myfile, tsp_model);
            myfile.close();
        }
        else{
            std::cerr << "Unable to open file"; 
        }
    }
}
