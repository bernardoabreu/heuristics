#include "io_util.h"


void read_file_to_vector(std::string input_file){
    std::string line, edge_weight_type;
    int dimension;

    // Matrix<T> v;

    std::ifstream myfile(input_file.c_str());

    if (myfile.is_open()){

        for(int i = 0; i < HEADER_SIZE; i++){
            getline(myfile, line);
            std::vector<std::string> v = split<std::vector<std::string> >(line, ':');

            if(v[0] == "DIMENSION"){
                dimension = str2num<int>(v[1]);
            }
            else if(v[0] == "EDGE_WEIGHT_TYPE"){
                edge_weight_type = v[1];
            }

            for(auto &e : v){
                std::cout << '\'' << e << '\'' << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << dimension << ' ' << edge_weight_type << std::endl;

        // while (getline(myfile, line)){
        //     v.push_back(split<std::vector<T> >(line, delim));
        // }

        myfile.close();
    }
    else{
        std::cerr << "Unable to open file"; 
    }
    // return v;
}


void build_matrix_from_csv(std::string input_file){

    read_file_to_vector(input_file);
}

