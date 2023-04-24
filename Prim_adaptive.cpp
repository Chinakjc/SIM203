//
// Created by kjc on 2023/4/24.
//

#include "Prim_adaptive.hpp"
#include "Prim_std.hpp"
#include "Prim_dep.hpp"

Prim_adaptive::Prim_adaptive(int popMin) {
    if(popMin>100000)
        prim = new Prim_std(popMin);
    else if(popMin> 75000)
        prim = new Prim_std(popMin);
    else
        prim = new Prim_dep(popMin);
}
