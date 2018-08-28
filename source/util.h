#ifndef UTIL_H
#define UTIL_H

#include <sstream>


template<typename T>
T str2num(std::string str){
    T n;
    std::istringstream(str) >> n;
    return n;
}


/*
    Obtained from https://stackoverflow.com/questions/236129/most-elegant-way-to-split-a-string
    Author: Evan Teran
 */
template<typename T>
void split(const std::string &s, char delim, T result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;

    typename T::container_type::value_type item_type;
    while (std::getline(ss, item, delim)) {
        std::istringstream(item) >> item_type;
        *(result++) = item_type;
    }
}

template<typename T>
T split(const std::string &s, char delim) {
    T elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

#endif