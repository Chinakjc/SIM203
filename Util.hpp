//
// Created by kjc on 2023/4/24.
//

#ifndef SIM203_UTIL_HPP
#define SIM203_UTIL_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <queue>
#include <math.h>
#include <omp.h>
#include <map>
#include <functional>
#include <cfloat>

using namespace std;

const string input_file_name = "citiesList.csv";
const string output_file_name = "resuCities.dat";
typedef struct ListOfCities ListOfCities;
struct ListOfCities
{
    int number;
    vector<string> name;
    vector<int> pop;
    vector<float> lon, lat;
    vector<int> depart;
};


const int R = 6378; // radius of the earth in km


struct Edge_lite {
    int city;
    int parent;
};

typedef vector<vector<Edge_lite>> Graph_lite;

struct Edge_std {
    int city;
    int parent;
    double weight;
    bool operator>(const Edge_std& other) const {
        return weight > other.weight;
    };
};

typedef vector<vector<Edge_std>> Graph_std;

struct Edge_dep {
    int capital;
    int parent;
    double weight;
    bool operator>(const Edge_dep& other) const {
        return weight > other.weight;
    };
};

typedef vector<vector<Edge_dep>> Graph_dep;

inline double calculateDistance(double lat1d,double lon1d, double lat2d, double lon2d){
    double lat1 = lat1d * M_PI / 180.0;
    double lon1 = lon1d * M_PI / 180.0;
    double lat2 = lat2d * M_PI / 180.0;
    double lon2 = lon2d * M_PI / 180.0;

// Calculate the distance between two cities
    return acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2)) * R;
}

inline int get_index_visited(int number, int parent, int city){
    return number*parent + city;
}

enum prim_mode{
    naive = 0,
    mem_saver = 1,
    dep = 2,
};

#endif //SIM203_UTIL_HPP
