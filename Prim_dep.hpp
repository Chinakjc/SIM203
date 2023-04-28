//
// Created by kjc on 2023/4/24.
//

#ifndef SIM203_PRIM_DEP_HPP
#define SIM203_PRIM_DEP_HPP


#include "Prim.hpp"
#include "Department.hpp"

class Prim_dep : public Prim{
private:
    Graph_dep graph;
    map<int,Department*> mapDep;
    //vector<int> globalIndexCap;
public:
    Prim_dep(int popMin);
    pair<double, vector<pair<int, int>>> prim_cap() const;
    pair<double, vector<pair<int, int>>> prim() const override;

};


#endif //SIM203_PRIM_DEP_HPP
