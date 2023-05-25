#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "../graph.h"
#include "../airport.h"
#include "../data.h"

TEST_CASE("testing getAirports with comma in first attribute"){
    getAirports("tests/data/airports_in.csv", "tests/data/airports_out.csv");

    std::ifstream ifs{"tests/data/airports_out.csv"};
    std::string line, word;
    std::vector<std::string> row;
    if(ifs.is_open()){
        getline(ifs, line);
        std::stringstream s(line);
        while(getline(s, word, ',')){
            row.push_back(word);
        }
    }
    REQUIRE(row[0] == "Copenhagen Kastrup Airport");
    REQUIRE(row[1] == "\"Denmark\"");
    REQUIRE(row[2] == "\"CPH\"");
    REQUIRE(stod(row[3]) == 55.617900848389);
    REQUIRE(stod(row[4]) == 12.656000137329);
}

TEST_CASE("testing airportExists() basic"){
    Graph g;
    Airport a1("Goroka Airport", "Papua New Guinea", "GKA", -6.081689834590001, 145.391998291);

    g.insertAirport(a1);
    REQUIRE(g.airportExists("GKA"));
    REQUIRE(!g.airportExists("RAN"));
}

TEST_CASE("testing routeExists() basic"){
    Graph g;
    Airport a1("Goroka Airport", "Papua New Guinea", "GKA", -6.081689834590001, 145.391998291);

    g.insertAirport(a1);
    REQUIRE(!g.routeExists("RAN", "SAM"));
}

TEST_CASE("testing insertAirport basic"){
    Graph g;
    Airport a1("Goroka Airport", "Papua New Guinea", "GKA", -6.081689834590001, 145.391998291);
    Airport a2("London Airport", "Canada", "YXU", 43.035599, -81.1539);

    g.insertAirport(a1);
    //inserted exists
    REQUIRE(g.airportExists(a1.getIATA()));
    //not inserted doesnt exist
    REQUIRE(!g.airportExists(a2.getIATA()));
}

TEST_CASE("testing insertAirport duplicates"){
    Graph g;
    Airport a2("London Airport", "Canada", "YXU", 43.035599, -81.1539);
    Airport a3("Duplicate", "Canada", "YXU", 43.035599, -81.1539);

    g.insertAirport(a2);
    g.insertAirport(a3);
    //inserted exists
    REQUIRE(g.airportExists(a2.getIATA()));
    //duplicate doesnt exist
    REQUIRE(g.getAirport("YXU").getName() != "Duplicate");
}

TEST_CASE("testing insertEdge basic"){
    Graph g;
    Airport a1("Goroka Airport", "Papua New Guinea", "GKA", -6.081689834590001, 145.391998291);
    Airport a2("London Airport", "Canada", "YXU", 43.035599, -81.1539);

    g.insertAirport(a1);
    g.insertAirport(a2);
    g.insertRoute("GKA", "YXU");

    REQUIRE(g.routeExists("GKA", "YXU"));
    REQUIRE(!g.routeExists("GKA", "RAN"));
}

TEST_CASE("testing insertEdge both ways"){
    Graph g;
    Airport a1("Goroka Airport", "Papua New Guinea", "GKA", -6.081689834590001, 145.391998291);
    Airport a2("London Airport", "Canada", "YXU", 43.035599, -81.1539);

    g.insertAirport(a1);
    g.insertAirport(a2);
    g.insertRoute("GKA", "YXU");
    g.insertRoute("YXU", "GKA");

    REQUIRE(g.routeExists("YXU", "GKA"));
}

TEST_CASE("testing weight"){
    Graph g;
    Airport a1("Goroka Airport", "Papua New Guinea", "GKA", 53.32055555555556, -1.7297222222222221);
    Airport a2("London Airport", "Canada", "YXU", 53.31861111111111, -1.6997222222222223);
    g.insertAirport(a1);
    g.insertAirport(a2);
    g.insertRoute("GKA", "YXU");

    Airport a3("Mount Hagen Kagamuga Airport", "Papua New Guinea", "HGU", -5.826789855957031, 144.29600524902344);
    Airport a4("Siglufjörður Airport", "Iceland", "SIJ", 66.133301, -18.9167);
    g.insertAirport(a3);
    g.insertAirport(a4);
    g.insertRoute("HGU", "SIJ");

    REQUIRE(g.getRouteWeight("HGU", "SIJ") - 13184.19326 < 0.00001);
    REQUIRE(g.getRouteWeight("GKA", "YXU") - 2.0043678383 < 0.00001);
}


TEST_CASE("testing Graph file constructor"){
    Graph g("tests/graph/graph_airports.csv", "tests/graph/graph_routes.csv");

    REQUIRE(g.airportExists("GKA"));
    REQUIRE(g.airportExists("MAG"));
    REQUIRE(g.airportExists("HGU"));
    REQUIRE(g.airportExists("LAE"));
    REQUIRE(g.airportExists("SIJ"));
    REQUIRE(g.airportExists("THU"));

    REQUIRE(g.routeExists("GKA", "MAG"));
    REQUIRE(g.routeExists("LAE", "GKA"));
    REQUIRE(g.routeExists("MAG", "HGU"));

    REQUIRE(!g.routeExists("SIJ", "SIJ"));
}

TEST_CASE("testing BFS"){
    Graph g("tests/bfs/bfs_airports.csv", "tests/bfs/bfs_routes.csv");

    std::vector<std::string> result;
    std::vector<std::string> actual = {"GKA", "LAE", "MAG","SIJ","HGU","THU"};
    result = g.BFS("GKA");
    for(size_t i = 0; i < result.size(); i++){
        REQUIRE(result[i] == actual[i]);
    }
    std::cout << std::endl;
}


TEST_CASE("testing Dijkstra"){
    Graph g("tests/dijkstra/dijkstra_airports.csv", "tests/dijkstra/dijkstra_routes.csv");
    std::list<std::pair<std::string, double>> result = g.Dijkstra("GKA", "LAE");
    std::list<std::pair<std::string, double>> actual = {std::make_pair("GKA", 0),
                                                        std::make_pair("MAG", 106.714),
                                                        std::make_pair("HGU", 285.75),
                                                        std::make_pair("LAE", 566.787)};
    for(unsigned i =0; i < actual.size(); i++){
        auto r = result.begin();
        auto a = actual.begin();
        std::advance(r,i);
        std::advance(a,i);
        REQUIRE(r->first == a->first);
    }
    std::cout << std::endl;
}

TEST_CASE("testing Dijkstra advanced"){
    Graph g("newdata/airports.csv", "newdata/routes.csv");
    std::list<std::pair<std::string, double>> result = g.Dijkstra("CAI", "KZN");
    std::list<std::pair<std::string, double>> actual = {std::make_pair("CAI", 0),
                                                        std::make_pair("TLV", 392.487),
                                                        std::make_pair("MRV", 1926.28),
                                                        std::make_pair("ASF", 2374.45),
                                                        std::make_pair("KZN", 3414.89)};
    for(unsigned i =0; i < actual.size(); i++){
        auto r = result.begin();
        auto a = actual.begin();
        std::advance(r,i);
        std::advance(a,i);
        REQUIRE(r->first == a->first);
    }
    std::cout << std::endl;
}

TEST_CASE("testing Bellman-Ford"){
    Graph g("tests/bellman/bellman_airports.csv", "tests/bellman/bellman_routes.csv");
    std::list<std::pair<std::string, double>> result = g.BellmanFord("GKA", "LAE");
    std::list<std::pair<std::string, double>> actual = {std::make_pair("GKA", 0),
                                                        std::make_pair("MAG", 106.714),
                                                        std::make_pair("HGU", 285.75),
                                                        std::make_pair("LAE", 566.787)};
    for(unsigned i =0; i < actual.size(); i++){
        auto r = result.begin();
        auto a = actual.begin();
        std::advance(r,i);
        std::advance(a,i);
        REQUIRE(r->first == a->first);
    }
    g.BellmanFord("GKA","LAE");
}


