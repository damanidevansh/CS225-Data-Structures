#include "data.h"
#include "graph.h"
#include <string>
#include <iostream>
int main(){
    //only run once
    // getAirports("olddata/oldairports.csv", "newdata/airports.csv");
    // getRoutes("olddata/oldroutes.csv", "newdata/routes.csv");
    
    Graph g("newdata/airports.csv", "newdata/routes.csv");
    std::vector<std::string> result = g.BFS("CAI");
    std::cout << "Number of airports traversed in BFS: " << result.size() << std::endl;
    g.Dijkstra("CAI", "KZN");
    g.BellmanFord("CAI","KZN");
}