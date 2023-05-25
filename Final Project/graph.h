#pragma once

#include "airport.h"
#include "route.h"
#include <string>
#include <unordered_map>
#include <map>
#include <list>
#include <vector>
#include <queue>
class Graph {
public:
    Graph();
    Graph(std::string airportFile, std::string routeFile);
    void insertAirport(Airport& airport);
    void insertRoute(std::string source, std::string dest);
    bool airportExists(std::string iata);
    bool routeExists(std::string source, std::string dest);
    double getRouteWeight(std::string source, std::string dest);
    Airport& getAirport(std::string iata);
    std::vector<std::string> BFS(std::string source);
    std::list<std::pair<std::string, double>> Dijkstra(std::string source, std::string dest);
    std::list<std::pair<std::string, double>> BellmanFord(std::string source, std::string dest);
    //used for testing
    // void test();
    // void print(std::priority_queue<std::pair<double, std::string>>& q);
private:
    void DijkstraHelper(std::string source,
                        std::unordered_map<std::string,double>& distances,
                        std::unordered_map<std::string, std::string>& prev);
    void BellmanFordHelper(std::string source,
                           std::unordered_map<std::string,double>& distances,
                           std::unordered_map<std::string, std::string>& prev);
    double toRadians(double degrees);
    double calculateWeight(std::string source, std::string dest);
    void reset();
    std::unordered_map<std::string, std::list<Route>> adjList_;
    std::unordered_map<std::string, Airport> airports_;
};