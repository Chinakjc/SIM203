//
// Created by kjc on 2023/4/24.
//

#include "Prim_adaptive.hpp"
#include "Prim_std.hpp"
#include "Prim_dep.hpp"
#include "Prim_memory_saver.hpp"

Prim_adaptive::Prim_adaptive(int popMin) {
    if(popMin>POPMIN_LEVEL1)
        prim_ad = new Prim_std(popMin);
    else if(popMin> POPMIN_LEVEL2)
        prim_ad = new Prim_memory_saver(popMin);
    else
        prim_ad = new Prim_dep(popMin);
}

pair<double, vector<pair<int, int>>> Prim_adaptive::prim() const {
    return prim_ad->prim();
}

void Prim_adaptive::prim_f(bool text) const {
    prim_ad->prim_f(text);
}
