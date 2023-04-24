//
// Created by kjc on 2023/4/24.
//

#ifndef SIM203_PRIM_STD_HPP
#define SIM203_PRIM_STD_HPP


#include "Prim.hpp"


class Prim_std : public Prim{
private:
    Graph_std graph;
public:
    Prim_std(int popMin);
    pair<double, vector<pair<int, int>>> prim() const override;
};


#endif //SIM203_PRIM_STD_HPP
