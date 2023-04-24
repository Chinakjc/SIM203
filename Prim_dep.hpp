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
public:
    Prim_dep(int popMin);

};


#endif //SIM203_PRIM_DEP_HPP
