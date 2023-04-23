#ifndef CITIES_READER
#define CITIES_READER

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

typedef struct ListOfCities ListOfCities;

struct ListOfCities
{
    int number;
    vector<string> name;
    vector<int> pop;
    vector<float> lon, lat;
    vector<int> depart;
};

ListOfCities citiesReader(int popMin);

#endif
