// Compilation:
//   icpc -O3 -qopenmp main.cpp citiesReader.cpp
// Execution:
//   ./a.out

#include "citiesReader.hpp"
#include "Department.hpp"
#include <vector>
#include <time.h>
#include <queue>
#include <math.h>
#include <omp.h>
#include <map>

const int R = 6378; // radius of the earth in km

struct Edge {
    int city;
    int parent;
    // double weight;

    //bool operator>(const Edge& other) const {
    //    return weight > other.weight;
    //};
};

typedef vector<vector<Edge>> Graph;

/*
Graph buildGraph(const ListOfCities& cities) {
    Graph graph(cities.number);
#pragma omp parallel for default(none) shared(cities,graph)
    for (int i = 0; i < cities.number; ++i) {
        for (int j = 0; j < cities.number; ++j) {
            if (i != j) {
                // Convert degrees to radians
                double lat1 = cities.lat[i] * M_PI / 180.0;
                double lon1 = cities.lon[i] * M_PI / 180.0;
                double lat2 = cities.lat[j] * M_PI / 180.0;
                double lon2 = cities.lon[j] * M_PI / 180.0;

                // Calculate the distance between two cities
                double distance = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2)) * R;
                graph[i].push_back(Edge{j, i, distance});
            }
        }
    }

    return graph;
}*/

double calculateDistance(const ListOfCities& cities, int city1, int city2) {
    double lat1 = cities.lat[city1] * M_PI / 180.0;
    double lon1 = cities.lon[city1] * M_PI / 180.0;
    double lat2 = cities.lat[city2] * M_PI / 180.0;
    double lon2 = cities.lon[city2] * M_PI / 180.0;

    // Calculate the distance between two cities
    return acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2)) * R;
}

Graph buildGraph(const ListOfCities& cities) {
    Graph graph(cities.number);

#pragma omp parallel for default(none) shared(cities,graph)
    for (int i = 0; i < cities.number; ++i) {
        for (int j = 0; j < cities.number; ++j) {
            if (i != j) {
                graph[i].push_back(Edge{j, i});
            }
        }
    }

    return graph;
}


Graph buildGraph_cap(const ListOfCities& cities, map<int,Department*> map_dep) {
    Graph graph(map_dep.size());
#pragma omp parallel for default(none) shared(cities,graph)
    int i = 0;
    for (auto it1 = map_dep.begin(); it1!= map_dep.end(); it1++) {
        int j = 0;
        //Graph for cap
        int cap_i = it1->second->getCapital(); //it1->second Departement*
        for (auto it2 = map_dep.begin(); it2 != map_dep.end(); it2++) {
            if (i != j) {
                graph[i].push_back(Edge{j, i});
                /*
                int cap_j = it2->second->getCapital();
                // Convert degrees to radians
                
                double lat1 = cities.lat[cap_i] * M_PI / 180.0;
                double lon1 = cities.lon[cap_i] * M_PI / 180.0;
                double lat2 = cities.lat[cap_j] * M_PI / 180.0;
                double lon2 = cities.lon[cap_j] * M_PI / 180.0;

                // Calculate the distance between two cities
                double distance = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(lon1 - lon2)) * R;
                graph[i].push_back(Edge{cap_j, cap_i, distance});
                */
            }
        }
        return graph;
    }

    return graph;
}

// prim algorithm
/*
pair<double, vector<pair<int,int>>> prim(const Graph& graph){
    vector<bool> visited(graph.size(), false);
    vector<pair<int,int>> edges;
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    double totalWeight = 0.0;

    visited[0] = true;
    for (const Edge& e : graph[0]){
        pq.push(e);
    }

    while (!pq.empty()){
        Edge current = pq.top();
        pq.pop();

        if (visited[current.city]){
            continue;
        }

        visited[current.city] = true;
        totalWeight += current.weight;
        edges.push_back({current.city, current.parent});

        for (const Edge& edge : graph[current.city]){
            if (!visited[edge.city]) {
                pq.push(edge);
            }
        }
    }
    return {totalWeight, edges};
}*/

pair<double, vector<pair<int,int>>> prim(const ListOfCities& cities, const Graph& graph){
    vector<bool> visited(cities.number, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    visited[0] = true;
    for (const Edge& e : graph[0]){
        pq.push(e);
    }

    double totalWeight = 0.0;
    vector<pair<int,int>> treeEdges;

    while (!pq.empty()){
        Edge current = pq.top();
        pq.pop();
        int city = current.city;
        int parent = current.parent;

        if (visited[city]){
            continue;
        } else {
            visited[city] = true;
            totalWeight += calculateDistance(cities, city, parent);
            treeEdges.push_back(make_pair(parent, city));

            for (const Edge& edge : graph[city]){
                if (!visited[edge.city]) {
                    pq.push(edge);
                }
            }
        }
    }
    return {totalWeight, treeEdges};
}


// prim algorithm
pair<double, vector<pair<int,int>>> prim_bloc(const ListOfCities& cities){
    map<int,Department*> map_dep;
    for(int i = 0; i< cities.number; i++){
        int dep_i = cities.depart[i];
        int pop_i = cities.pop[i];
        if(map_dep.find(dep_i) == map_dep.end()){
            Department * newDep = new Department(dep_i);
            newDep->add(i,pop_i);
            map_dep[dep_i] = newDep;
        } else{
            map_dep[dep_i]->add(i,pop_i);
        }
    }

    // calculate MST for each department
    for (auto it = map_dep.begin(); it != map_dep.end(); it++) {
        int dep_i = it->first;
        ListOfCities cities_dep = it->second->getCities();
        Graph graph = buildGraph(cities_dep);
        pair<double, vector<pair<int,int>>> result = prim(graph);
        it->second->setMST(result);
    }

    // calculate MST for department captials
    auto tree_cap = prim(buildGraph_cap(cities,map_dep));

    // combine the MSTs and return the result



}



int main() {

    //-----------------------------------------------------------------
    //--- READING cities
    //-----------------------------------------------------------------

    int popMin;
    cout << "Minimal population? ";
    cin >> popMin;

    ListOfCities cities = citiesReader(popMin);


    Graph graph = buildGraph(cities);
    clock_t t0 = clock();
    pair<double, vector<pair<int,int>>> result = prim(graph);
    clock_t t1 = clock();

    double networkSize = result.first;

    vector<pair<int,int>> connections = result.second;

    // Execution time
    cout << "Execution time: " << t1 - t0 << " ms"<< endl;

    // Output network size
    cout << "Network size: " << networkSize << " km"<< endl;

    // Print the generated tree
    cout << "Generated tree:" << endl;

    for (const pair<int, int>& connection : connections) {
        cout << "City " << cities.name[connection.first] << " connected to City " << cities.name[connection.second] << endl;
    }

    // Save the coordinates and connections in a CSV file
    ofstream outputFile("resuCities.dat");
    if (outputFile.is_open()){
        outputFile << "city_name, lattiude, longitude, parent_city_name, parent_latitude, parent_longitude, population" << endl;
        for (const pair<int, int>& connection : connections){
            outputFile << cities.name[connection.first] << "," << cities.lat[connection.first] << "," << cities.lon[connection.first] << "," << cities.name[connection.second] << "," << cities.lat[connection.second] << "," << cities.lon[connection.second] << "," << cities.pop[connection.first] << endl;

        }
        outputFile.close();

    }
    return 0;
}
