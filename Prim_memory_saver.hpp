//
// Created by kjc on 2023/4/24.
//

#ifndef SIM203_PRIM_MEMORY_SAVER_HPP
#define SIM203_PRIM_MEMORY_SAVER_HPP


#include "Prim.hpp"

class Prim_memory_saver : public Prim{
private:
    Graph_lite graph;
public:
    Prim_memory_saver(int popMin);
    pair<double, vector<pair<int, int>>> prim() const override;
};


#endif //SIM203_PRIM_MEMORY_SAVER_HPP
