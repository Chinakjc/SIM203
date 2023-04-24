//
// Created by kjc on 2023/4/21.
//

#include "Department.hpp"

Department::Department(int departcode) : departCode(departcode), capital(-1), popCap(0){

}

void Department::add(int city, int pop) {
    this->cities.push_back(city);
    if(pop>this->popCap){
        this->capital = city;
        this->popCap = pop;
    }
}

int Department::getCapital() const {
    return this->capital;
}

int Department::operator[](int index) const {
    return cities[index];
}

int Department::size() const {
    return cities.size();
}




