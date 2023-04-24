//
// Created by kjc on 2023/4/24.
//

#ifndef SIM203_PRIM_HPP
#define SIM203_PRIM_HPP


#include "citiesReader.hpp"


class Prim {
protected:
    ListOfCities cities;
public:
    Prim(int popMin);
    virtual pair<double, vector<pair<int,int>>> prim() const = 0;
    void prim_f(bool text) const;
};


#endif //SIM203_PRIM_HPP
