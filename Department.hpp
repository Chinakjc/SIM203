//
// Created by kjc on 2023/4/21.
//

#ifndef SIM203_DEPARTMENT_HPP
#define SIM203_DEPARTMENT_HPP


#include <vector>
#include "Util.hpp"

class Department {
protected:
    int departCode;
    int capital;
    std::vector<int> cities;
    int popCap;
public:
    Department(int departcode);
    void add(int city, int pop);
    int getCapital() const;
    int operator[](int) const;
    int size() const;
};


#endif //SIM203_DEPARTMENT_HPP
