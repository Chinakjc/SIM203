//
// Created by kjc on 2023/4/24.
//

#include "Prim_dep.hpp"

Prim_dep::Prim_dep(int popMin) : Prim(popMin) {
    cout<<"test0"<<1<<endl;
    graph = Graph_dep(cities.number);
#pragma omp parallel for default(none) shared(cities,graph)
    for (int i = 0; i < cities.number; ++i) {
        int dep_code_i = cities.depart[i];
        int pop_i = cities.pop[i];
        Department* dep_i;
        if(mapDep.find(dep_code_i)!=mapDep.end()){
            dep_i = mapDep[i];
        }else{
            dep_i = new Department(dep_code_i);
            mapDep[dep_code_i] = dep_i;
        }
        dep_i->add(i,pop_i);
    }
    for(auto it1 = mapDep.begin(); it1 != mapDep.end(); it1++){
        Department* dep1 = it1->second;
        int cap1 = dep1->getCapital();
        for(auto it2 = next(it1); it2 != mapDep.end(); it2++){
            Department* dep2 = it2->second;
            int cap2 = dep2->getCapital();
            double lat1 = cities.lat[cap1];
            double lon1 = cities.lon[cap1];
            double lat2 = cities.lat[cap2];
            double lon2 = cities.lon[cap2];
            // Calculate the distance between two cities
            double distance = calculateDistance(lat1,lon1,lat2,lon2);
            graph[cap1].push_back(Edge_dep{cap2, cap1, distance});
        }
    }
}

pair<double, vector<pair<int, int>>> Prim_dep::prim_cap() const {
    vector<bool> visited(graph.size(), false);
    vector<pair<int,int>> edges;
    priority_queue<Edge_dep, vector<Edge_dep>, greater<Edge_dep>> pq;
    double totalWeight = 0.0;

    visited[0] = true;
    for (const Edge_dep& e : graph[0]){
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
    for(auto it = mapDep.begin(); it != mapDep.end(); it++){
        Department* department_i = it->second;
        Graph_lite graph_i= Graph_lite(cities.number);

        //graph
        int dep_size = department_i->size();
#pragma omp parallel for default(none) shared(cities,graph_i)
        for (int i = 0; i < dep_size; ++i) {
            int ct_i = department_i->operator[](i);
            for (int j = i + 1; j < dep_size; ++j) {
                int ct_j = department_i->operator[](j);
                graph_i[i].push_back(Edge_lite{ct_j, ct_i});
                graph_i[j].push_back(Edge_lite{ct_i, ct_j});
            }
        }

        //prim cf Prim_memory_saver::prim()
        vector<bool> visited(graph_i.size(), false);
        //vector<pair<int, int>> edges;
        priority_queue<Edge_lite, vector<Edge_lite>, function<bool(const Edge_lite &, const Edge_lite &)>> pq([this](const Edge_lite &a, const Edge_lite &b) {
            double lat1 = cities.lat[a.city];
            double lon1 = cities.lon[a.city];
            double lat2 = cities.lat[a.parent];
            double lon2 = cities.lon[a.parent];
            double distanceA = calculateDistance(lat1,lon1,lat2,lon2);

            lat1 = cities.lat[b.city] ;
            lon1 = cities.lon[b.city] ;
            lat2 = cities.lat[b.parent] ;
            lon2 = cities.lon[b.parent] ;
            double distanceB = calculateDistance(lat1,lon1,lat2,lon2);

            return distanceA > distanceB;
        });

        double totalWeight = 0.0;
        /*
        visited[0] = true;
        for (const Edge_lite &e : graph_i[0]) {
            pq.push(e);
        }*/
        int departmentCapital = department_i->getCapital();
        visited[departmentCapital] = true;
        for (const Edge_lite &e : graph_i[departmentCapital]) {
            pq.push(e);
        }

        while (!pq.empty()) {
            Edge_lite current = pq.top();
            pq.pop();

            if (visited[current.city]) {
                continue;
            }

            visited[current.city] = true;
            double lat1 = cities.lat[current.city];
            double lon1 = cities.lon[current.city] ;
            double lat2 = cities.lat[current.parent] ;
            double lon2 = cities.lon[current.parent] ;
            double distance = calculateDistance(lat1,lon1,lat2,lon2);

            totalWeight += distance;
            //edges.push_back({current.city, current.parent});
            treeCap.push_back({current.city, current.parent});

            for (const Edge_lite &edge : graph_i[current.city]) {
                if (!visited[edge.city]) {
                    pq.push(edge);
                }
            }
        }
        networkSize += totalWeight;
    }
    return {networkSize, treeCap};
}
