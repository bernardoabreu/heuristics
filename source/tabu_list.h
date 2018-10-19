#ifndef TABU_LIST_H
#define TABU_LIST_H

#include <list>
#include <vector>

class TabuList{
private:
    std::list<std::vector<std::pair<int,int> > > tabu_list;
public:

    bool contains_changes(const std::vector<std::pair<int, std::pair<int, int> > >& changes);
    bool contains(std::vector<int> v);

    void push(const std::vector<int>&);
    void removeFirst();

    inline unsigned int size() const { return tabu_list.size(); };

};

#endif