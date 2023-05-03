//
// Created by kjc on 2023/4/24.
//

#include "Prim_std.hpp"

Prim_std::Prim_std(int popMin) : Prim(popMin){
    graph = Graph_std(cities->number);
#pragma omp parallel for default(none) shared(cities,graph)
    for (int i = 0; i < cities->number; ++i) {
        for (int j = 0; j < cities->number; ++j) {
            if (i != j) {
                double lat1 = cities->lat[i];
                double lon1 = cities->lon[i];
                double lat2 = cities->lat[j];
                double lon2 = cities->lon[j];
                // Calculate the distance between two cities
                double distance = calculateDistance(lat1,lon1,lat2,lon2);
                graph[i].push_back(Edge_std{j, i, distance});
            }
        }
    }
}

pair<double, vector<pair<int, int>>> Prim_std::prim() const {
    vector<bool> visited(graph.size(), false);
    vector<pair<int,int>> edges;
    priority_queue<Edge_std, vector<Edge_std>, greater<Edge_std>> pq;
    double totalWeight = 0.0;

    visited[0] = true;
    for (const Edge_std& e : graph[0]){
        pq.push(e);
    }

    while (!pq.empty()){
        Edge_std current = pq.top();
        pq.pop();
        if (visited[current.city]){
            continue;
        }

        visited[current.city] = true;
        totalWeight += current.weight;
        edges.push_back({current.city, current.parent});

        for (const Edge_std& edge : graph[current.city]){
            if (!visited[edge.city]) {
                pq.push(edge);
            }
        }
    }
    return {totalWeight, edges};
}


