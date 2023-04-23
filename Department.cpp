//
// Created by kjc on 2023/4/21.
//

#include "Department.hpp"

Department::Department(int departcode, const ListOfCities &cities) : departCode(departcode){
    int max_pop = 0;
    for(int i=0; i< cities.number; i++){
        int dp_i = cities.depart[i];
        if(dp_i == departcode){
            this->cities.push_back(i);
            int pop_i = cities.pop[i];
            if(pop_i> max_pop){
                this->capital = i;
                max_pop = pop_i;
            }
        }
    }
    this->popCap = max_pop;
}

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


