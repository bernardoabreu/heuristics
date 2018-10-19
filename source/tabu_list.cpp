#include "tabu_list.h"
#include <iostream>


bool TabuList::contains_changes(const std::vector<std::pair<int, std::pair<int, int> > >& changes){
    for(auto &solution : this->tabu_list){
        bool same = true;

        for(auto &change : changes){
            if(solution[change.first] != change.second){
                same = false;
                break;
            }
        }
        if(same){
            return true;
        }
    }
    return false;
}


bool TabuList::contains(const std::vector<int> solution){
    for(auto &tabu : this->tabu_list){
        bool same = true;
        std::pair<int, int> new_pair;

        int prev, next;
        int size = solution.size();

        prev = solution[solution.size() - 1] - 1;
        next = solution[1] - 1;
        new_pair = (prev < next) ? std::pair<int, int>(prev, next) : std::pair<int, int>(next, prev);
        if(tabu[solution[0] - 1] != new_pair){
            same = false;
            break;
        }

        for(int i = 1; i < size; i++){
            prev = solution[i - 1] - 1;
            next = solution[(i + 1) % size] - 1;
            new_pair = (prev < next) ? std::pair<int, int>(prev, next) : std::pair<int, int>(next, prev);
            if(tabu[solution[i] - 1] != new_pair){
                same = false;
                break;
            }
        }

        if(same){
            return true;
        }
    }
    return false;
}


void TabuList::push(const std::vector<int>& solution){
    this->tabu_list.push_back(std::vector<std::pair<int,int> >(solution.size()));

    std::pair<int, int> new_pair;
    int prev, next;
    int size = solution.size();

    prev = solution[solution.size() - 1] - 1;
    next = solution[1] - 1;
    new_pair = (prev < next) ? std::pair<int, int>(prev, next) : std::pair<int, int>(next, prev);
    this->tabu_list.back()[solution[0] - 1] = new_pair;

    for(int i = 1; i < size; i++){
        prev = solution[i - 1] - 1;
        next = solution[(i + 1) % size] - 1;
        new_pair = (prev < next) ? std::pair<int, int>(prev, next) : std::pair<int, int>(next, prev);
        this->tabu_list.back()[solution[i] - 1] = new_pair;
    }
}


void TabuList::removeFirst(){
    this->tabu_list.pop_front();
}
