//
// Created by kjc on 2023/4/24.
//

#include "Prim_dep.hpp"

Prim_dep::Prim_dep(int popMin) : Prim(popMin){

    graph = Graph_dep(cities->number);

    for (int i = 0; i < cities->number; ++i) {
        int dep_code_i = cities->depart[i];
        int pop_i = cities->pop[i];
        Department* dep_i;
        if(mapDep.find(dep_code_i) != mapDep.end()){
            dep_i = mapDep[dep_code_i];
        } else {
            dep_i = new Department(dep_code_i);
            mapDep[dep_code_i] = dep_i;
        }
        dep_i->add(i, pop_i);
    }

    for(auto it1 = mapDep.begin(); it1 != mapDep.end(); it1++){
        Department* dep1 = it1->second;
        int cap1 = dep1->getCapital();
        for(auto it2 = next(it1); it2 != mapDep.end(); it2++){
            Department* dep2 = it2->second;
            int cap2 = dep2->getCapital();
            double lat1 = cities->lat[cap1];
            double lon1 = cities->lon[cap1];
            double lat2 = cities->lat[cap2];
            double lon2 = cities->lon[cap2];
            // Calculate the distance between two cities
            double distance = calculateDistance(lat1,lon1,lat2,lon2);
            graph[cap1].push_back(Edge_dep{cap2, cap1, distance});
            graph[cap2].push_back(Edge_dep{cap1, cap2, distance});
        }
    }
}

pair<double, vector<pair<int, int>>> Prim_dep::prim_cap() const {
    vector<bool> visited(graph.size(), false);
    vector<pair<int,int>> edges;
    priority_queue<Edge_dep, vector<Edge_dep>, greater<Edge_dep>> pq;
    double totalWeight = 0.0;
    int init_ct = mapDep.begin()->second->getCapital();
    visited[init_ct] = true;
    for (const Edge_dep& e : graph[init_ct]){
        pq.push(e);
    }

    while (!pq.empty()){
        Edge_dep current = pq.top();
        pq.pop();
        if (visited[current.capital]){
            continue;
        }

        visited[current.capital] = true;
        totalWeight += current.weight;
        edges.push_back({current.capital, current.parent});

        for (const Edge_dep& edge : graph[current.capital]){
            if (!visited[edge.capital]) {
                pq.push(edge);
            }
        }
    }
    return {totalWeight, edges};
}

pair<double, vector<pair<int, int>>> Prim_dep::prim() const {
    auto res = prim_cap();
    double networkSize = res.first;
    auto treeCap = res.second;

    // Loop for each department
#pragma omp parallel for default(none)  reduction(+:networkSize) shared(treeCap)
    for(int iteration1= 0; iteration1< mapDep.size(); iteration1++){
        auto it = mapDep.begin();
        for(int k = 0; k< iteration1 ; k++)
            it++;
        Department* department_i = it->second;
        int dep_size = department_i->size();


        vector<bool> visited(cities->number, false);
        //vector<pair<int, int>> edges;

        auto edge_compare = [this](const Edge_lite &a, const Edge_lite &b) {
            double lat1 = cities->lat[a.city];
            double lon1 = cities->lon[a.city];
            double lat2 = cities->lat[a.parent];
            double lon2 = cities->lon[a.parent];
            double distanceA = calculateDistance(lat1, lon1, lat2, lon2);
            lat1 = cities->lat[b.city];
            lon1 = cities->lon[b.city];
            lat2 = cities->lat[b.parent];
            lon2 = cities->lon[b.parent];
            double distanceB = calculateDistance(lat1, lon1, lat2, lon2);

            return distanceA > distanceB;
        };

        priority_queue<Edge_lite, vector<Edge_lite>, decltype(edge_compare)> pq(edge_compare);

        double totalWeight = 0.0;

        int departmentCapital = department_i->getCapital();
        visited[departmentCapital] = true;

        for (int i = 0; i < dep_size; ++i) {
            int ct_i = department_i->operator[](i);
            if (ct_i != departmentCapital) {
                pq.push(Edge_lite{ct_i, departmentCapital});
            }
        }

        do {
            while (!pq.empty() && visited[pq.top().city]) {
                pq.pop();
            }

            if (pq.empty()) {
                break;
            }

            Edge_lite current = pq.top();
            pq.pop();

            visited[current.city] = true;
            double lat1 = cities->lat[current.city];
            double lon1 = cities->lon[current.city];
            double lat2 = cities->lat[current.parent];
            double lon2 = cities->lon[current.parent];
            double distance = calculateDistance(lat1, lon1, lat2, lon2);

            totalWeight += distance;

#pragma omp critical
            {
                treeCap.push_back({current.city, current.parent});
            };



            for (int i = 0; i < dep_size; ++i) {
                int ct_i = department_i->operator[](i);
                if (!visited[ct_i]) {
                    pq.push(Edge_lite{ct_i, current.city});
                }
            }
        } while (!pq.empty());


        networkSize += totalWeight;
        it++;
    }
    return {networkSize, treeCap};
}
