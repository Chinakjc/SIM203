//
// Created by kjc on 2023/4/24.
//

#include "Prim_dep.hpp"

Prim_dep::Prim_dep(int popMin) : Prim(popMin) {
    graph = Graph_dep(cities.number);
#pragma omp parallel for default(none) shared(cities,graph)
    for (int i = 0; i < cities.number; ++i) {
        int dep_code_i = cities.depart[i];
        int pop_i = cities.pop[i];
        Department* dep_i;
        if(mapDep.find(dep_code_i)==mapDep.end()){
            dep_i = mapDep[i];
        }else{
            dep_i = new Department(dep_code_i);
        }
        dep_i->add(i,pop_i);
        for (int j = i+1; j < cities.number; ++j) {
            int dep_code_j = cities.depart[j];
            int pop_j = cities.pop[j];
            Department* dep_j;
            if(mapDep.find(dep_code_j)==mapDep.end()){
                dep_j = mapDep[j];
            }else{
                dep_j = new Department(dep_code_j);
            }
            dep_j->add(j,pop_j);
        }
    }

}
