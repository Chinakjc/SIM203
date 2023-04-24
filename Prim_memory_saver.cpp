//
// Created by kjc on 2023/4/24.
//


#include "Prim_memory_saver.hpp"

Prim_memory_saver::Prim_memory_saver(int popMin) :Prim(popMin){
    graph = Graph_lite(cities.number);
#pragma omp parallel for default(none) shared(cities,graph)
    for (int i = 0; i < cities.number; ++i) {
        for (int j = 0; j < cities.number; ++j) {
            if (i != j) {
                graph[i].push_back(Edge_lite{j, i});
            }
        }
    }
}

pair<double, vector<pair<int, int>>> Prim_memory_saver::prim() const {
    vector<bool> visited(graph.size(), false);
    vector<pair<int, int>> edges;
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

    visited[0] = true;
    for (const Edge_lite &e : graph[0]) {
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
        edges.push_back({current.city, current.parent});

        for (const Edge_lite &edge : graph[current.city]) {
            if (!visited[edge.city]) {
                pq.push(edge);
            }
        }
    }
    return {totalWeight, edges};


}
