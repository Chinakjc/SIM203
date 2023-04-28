//
// Created by kjc on 2023/4/24.
//

#ifndef SIM203_PRIM_ADAPTIVE_HPP
#define SIM203_PRIM_ADAPTIVE_HPP


#include "Prim.hpp"
#include "Util.hpp"

#define POPMIN_LEVEL1 75000
#define POPMIN_LEVEL2 30000

class Prim_adaptive {
private:
    Prim* prim_ad;

public:
    Prim_adaptive(int popMin);
    pair<double, vector<pair<int,int>>> prim() const;
    void prim_f(bool text) const;
};


#endif //SIM203_PRIM_ADAPTIVE_HPP
