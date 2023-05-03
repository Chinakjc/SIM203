//
// Created by kjc on 2023/4/24.
//


#include "Prim_memory_saver.hpp"

Prim_memory_saver::Prim_memory_saver(int popMin) :Prim(popMin){

}


pair<double, vector<pair<int, int>>> Prim_memory_saver::prim() const {
    vector<bool> visited(cities->number, false);
    vector<pair<int, int>> edges;
    priority_queue<Edge_lite, vector<Edge_lite>, function<bool(const Edge_lite &, const Edge_lite &)>> pq([this](const Edge_lite &a, const Edge_lite &b) {
        double distanceA = calculateDistance(cities->lat[a.city], cities->lon[a.city], cities->lat[a.parent], cities->lon[a.parent]);
        double distanceB = calculateDistance(cities->lat[b.city], cities->lon[b.city], cities->lat[b.parent], cities->lon[b.parent]);
        return distanceA > distanceB;
    });

    double totalWeight = 0.0;
    int current_node = 0;
    visited[current_node] = true;

    for (int i = 1; i < cities->number; ++i) {
        for (int j = 0; j < cities->number; ++j) {
            if (!visited[j]) {
                pq.push(Edge_lite{j, current_node});
            }
        }

        Edge_lite current;
        do {
            current = pq.top();
            pq.pop();
        } while (visited[current.city]);

        visited[current.city] = true;
        double distance = calculateDistance(cities->lat[current.city], cities->lon[current.city], cities->lat[current.parent], cities->lon[current.parent]);

        totalWeight += distance;
        edges.push_back({current.city, current.parent});
        current_node = current.city;
    }

    return {totalWeight, edges};
}
