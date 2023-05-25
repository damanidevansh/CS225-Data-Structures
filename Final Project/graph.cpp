#include "graph.h"
#include <cmath>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <limits.h>

Graph::Graph(){
    //nothing to do
}

Graph::Graph(std::string airportFile, std::string routeFile){
    std::ifstream a{airportFile};
    std::ifstream r{routeFile};

    std::string line, word;
    std::vector<std::string> row;
    //insert airports into graph structure
    if(a.is_open()){
        while(!a.eof()){
            row.clear();
            getline(a, line);
            std::stringstream s(line);
            if(line.empty()) continue;
            while(getline(s, word, ',')){
                row.push_back(word);
            }
            std::string name = row[0];
            //strips the quotes from string
            name.erase(std::remove(name.begin(), name.end(), '\"'), name.end() );
            std::string country = row[1];
            country.erase(std::remove(country.begin(), country.end(), '\"'), country.end() );
            std::string iata = row[2];
            iata.erase(std::remove(iata.begin(), iata.end(), '\"'), iata.end() );
            //test
            double lat = std::stod(row[3]);
            double longit = std::stod(row[4]);
            if(!airportExists(iata)){
                Airport a(name,country,iata,lat,longit);
                insertAirport(a);
            }
        }
    }else{
        std::cout << "Error opening airport file" << std::endl;
    }
    if(r.is_open()){
        while(!r.eof()){
            row.clear();
            getline(r, line);
            std::stringstream s(line);
            if(line.empty()) continue;
            while(getline(s, word, ',')){
                row.push_back(word);
            }
            auto source = adjList_.find(row[0]);
            auto dest = adjList_.find(row[1]);
            //checks if airports exist
            if(source != adjList_.end() && dest != adjList_.end() && source != dest){
                //checks if the route already exist
                if(!routeExists(row[0], row[1])){
                    double weight = calculateWeight(row[0], row[1]);
                    source->second.insert(source->second.begin(), Route(row[0], row[1], weight));
                }
            }
        }
    }else{
        std::cout << "Error opening routes file" << std::endl;
    }
    a.close();
    r.close();
}

void Graph::insertAirport(Airport& airport){
    if(!airportExists(airport.getIATA())){
        airports_.insert(std::pair<std::string, Airport>(airport.getIATA(), airport));
        adjList_.insert(std::pair<std::string, std::list<Route>>(airport.getIATA(), std::list<Route>{}));    
    }
}

void Graph::insertRoute(std::string source, std::string dest){
    //if route doesn't exist insert route to adjList
    if(!routeExists(source, dest)){
        std::unordered_map<std::string, std::list<Route>>::iterator itr = adjList_.find(source);
        double weight = calculateWeight(source, dest);
        itr->second.insert(itr->second.begin(), Route(source, dest, weight));
    }
}

bool Graph::airportExists(std::string iata){
    std::unordered_map<std::string, Airport>::iterator itr = airports_.find(iata);
    std::unordered_map<std::string, std::list<Route>>::iterator i = adjList_.find(iata);
    if(itr == airports_.end() && i == adjList_.end()){
        return false;
    }
    return true;
}

bool Graph::routeExists(std::string source, std::string dest){
    std::unordered_map<std::string, std::list<Route>>::iterator itr = adjList_.find(source);
    if(itr != adjList_.end()){
        for(std::list<Route>::iterator i = itr->second.begin(); i != itr->second.end(); i++){
            if(i->getSource() == source && i->getDest() == dest){
                return true;
            }
        }
    }
    return false;
}

double Graph::calculateWeight(std::string source, std::string dest){
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    double source_lat = toRadians(airports_.find(source)->second.getLat());
    double source_long = toRadians(airports_.find(source)->second.getLong());
    double dest_lat = toRadians(airports_.find(dest)->second.getLat());
    double dest_long = toRadians(airports_.find(dest)->second.getLong());
     
    // Haversine Formula
    double dlong = dest_long - source_long;
    double dlat = dest_lat - source_lat;
 
    double ans = pow(sin(dlat / 2), 2) + cos(source_lat) * cos(dest_lat) *pow(sin(dlong / 2), 2);
 
    ans = 2 * asin(sqrt(ans));

    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    double R = 6371;
     
    // Calculate the result
    ans = ans * R;
 
    return ans;
}

double Graph::toRadians(double degrees){
    double temp = (M_PI) / 180;
    return( temp*degrees );
}

double Graph::getRouteWeight(std::string source, std::string dest){
    std::unordered_map<std::string, std::list<Route>>::iterator itr = adjList_.find(source);
    double weight;
    for(std::list<Route>::iterator i = itr->second.begin(); i != itr->second.end(); i++){
        if(i->getDest() == dest){
            weight = i->getWeight();
        }
    }
    return weight;
}

Airport& Graph::getAirport(std::string iata){
    std::unordered_map<std::string, Airport>::iterator itr = airports_.find(iata);
    return itr->second;
}

std::vector<std::string> Graph::BFS(std::string source){
    Airport& a = getAirport(source);
    std::cout << "BFS Traversal of Graph" << std::endl;
    std::cout << "The traversal starts at " << a.getName() << " airport located in " << a.getCountry() << std::endl;
    std::cout << "*************************************" << std::endl;
    std::cout << "| Airport IATA | Name | Country |" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::queue<std::string> q;
    a.setVisited(true);
    q.push(a.getIATA());
    std::string curr;
    std::vector<std::string> traversal_order;
    while(!q.empty()){
        curr = q.front();
        Airport& node = getAirport(curr);
        //adding to traversal_order
        traversal_order.push_back(node.getIATA());
        std::cout << "| " << node.getIATA() << " | " << node.getName() << " | " << node.getCountry() << " | "  << std::endl;
        q.pop();
        //go through adjacency list
        std::list<Route> adjacent = adjList_.find(node.getIATA())->second;
        for(auto i = adjacent.begin(); i != adjacent.end(); i++){
            Airport& adj = getAirport(i->getDest());
            if(!adj.getVisited()){
                adj.setVisited(true);
                q.push(adj.getIATA());
            }
        }
    }
    reset();
    return traversal_order;
}

std::list<std::pair<std::string, double>> Graph::Dijkstra(std::string source, std::string dest){
    Airport& s = getAirport(source);
    Airport& d = getAirport(dest);
    std::cout << "Shortest Path using Dijkstra" << std::endl;
    std::cout << "The path starts at " << s.getName() << " airport located in " << s.getCountry() << std::endl;
    std::cout << "The path ends at " << d.getName() << " airport located in " << d.getCountry() << std::endl;
    std::cout << "*************************************" << std::endl;
    std::cout << "| Airport IATA | Name | Country | Distance traveled from source (km)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> prev;
    DijkstraHelper(source, distances, prev);
    std::list<std::pair<std::string, double>> result;
    auto curr = prev.find(dest);
    while(curr->second !="" && curr->second != source){
        auto dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, -1*(dist->second)));
        curr = prev.find(curr->second);
    }
    if(curr->second == source){
        auto dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, -1*dist->second));
        curr = prev.find(curr->second);
        dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, dist->second));
    }
    else if(curr->second !=""){
        auto dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, dist->second));
    }
    for(auto i = result.begin(); i != result.end(); i++){
        Airport& node = getAirport(i->first);
        std::cout << "| " << node.getIATA() << " | " << node.getName() << " | " << node.getCountry() << " | " << i->second << " km"  << std::endl;
    }
    //reset the airports to not visited
    reset();
    return result;
}

void Graph::DijkstraHelper(std::string source,
                           std::unordered_map<std::string,double>& distances,
                           std::unordered_map<std::string, std::string>& prev){
    double min  = INT_MIN;
    //initializing distances and prev
    for(auto i = airports_.begin(); i != airports_.end(); i++){
        distances.insert(std::pair<std::string, double>(i->first,min));
        prev.insert(std::pair<std::string, std::string>(i->first, ""));
    } 
    //setting source distance to zero
    auto itr = distances.find(source);
    itr->second = 0;
    //priority queue
    std::priority_queue<std::pair<double, std::string>> q;
    //building heap
    for(auto i = distances.begin(); i != distances.end(); i++){
        q.push(make_pair(i->second, i->first));
    }
    q.push(make_pair(0, source));
    //repeat for the number of airports
    for(size_t i =0; i < airports_.size(); i++){
        // print(q);
        // std::cout << std::endl;
        auto curr = q.top();
        q.pop();
        Airport& node = getAirport(curr.second);
        node.setVisited(true);
        std::list<Route> adjacent = adjList_.find(node.getIATA())->second;
        for(auto i = adjacent.begin(); i != adjacent.end(); i++){
            double weight = -1*(i->getWeight());
            Airport& adj = getAirport(i->getDest());
            if(!adj.getVisited()){
                auto prev_dis = distances.find(node.getIATA());
                auto dis = distances.find(adj.getIATA());
                if(weight + prev_dis->second > dis->second){
                    auto p = prev.find(adj.getIATA());
                    p->second = node.getIATA();
                    dis->second = weight + prev_dis->second;
                    q.push(make_pair(dis->second, adj.getIATA()));
                }
            }
        }
    }
}

std::list<std::pair<std::string, double>> Graph::BellmanFord(std::string source, std::string dest){
    Airport& s = getAirport(source);
    Airport& d = getAirport(dest);
    std::cout << "Shortest Path using Bellman-Ford" << std::endl;
    std::cout << "The path starts at " << s.getName() << " airport located in " << s.getCountry() << std::endl;
    std::cout << "The path ends at " << d.getName() << " airport located in " << d.getCountry() << std::endl;
    std::cout << "*************************************" << std::endl;
    std::cout << "| Airport IATA | Name | Country | Distance traveled from source (km)" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> prev;
    BellmanFordHelper(source, distances, prev);
    std::list<std::pair<std::string, double>> result;
    auto curr = prev.find(dest);
    while(curr->second !="" && curr->second != source){
        auto dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, dist->second));
        curr = prev.find(curr->second);
    }
    if(curr->second == source){
        auto dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, dist->second));
        curr = prev.find(curr->second);
        dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, dist->second));
    }
    else if(curr->second !=""){
        auto dist = distances.find(curr->first);
        result.push_front(make_pair(curr->first, dist->second));
    }
    for(auto i = result.begin(); i != result.end(); i++){
        Airport& node = getAirport(i->first);
        std::cout << "| " << node.getIATA() << " | " << node.getName() << " | " << node.getCountry() << " | " << i->second << " km"  << std::endl;
    }
    reset();
    return result;
}

void Graph::BellmanFordHelper(std::string source,
                           std::unordered_map<std::string,double>& distances,
                           std::unordered_map<std::string, std::string>& prev){
    double max  = INT_MAX;
    //initializing distances and prev
    for(auto i = airports_.begin(); i != airports_.end(); i++){
        distances.insert(std::pair<std::string, double>(i->first,max));
        prev.insert(std::pair<std::string, std::string>(i->first, ""));
    }
    //setting source distance to zero
    auto itr = distances.find(source);
    itr->second = 0;

    for(unsigned i =1; i <= airports_.size(); i++){
        for(auto routes = adjList_.begin(); routes != adjList_.end(); routes++){
            for(auto route = routes->second.begin(); route != routes->second.end(); route++){
                auto src = distances.find(route->getSource());
                auto dest = distances.find(route->getDest());
                auto dest_prev = prev.find(route->getDest());
                double weight = route->getWeight();
                if(src->second != INT_MAX && src->second + weight < dest->second){
                    dest->second = src->second + weight;
                    dest_prev->second = src->first;
                }
            }
            
        }
    }
}

void Graph::reset(){
    //set all airports to not visited
    for(auto i = airports_.begin(); i != airports_.end(); i++){
        Airport& temp = getAirport(i->first);
        temp.setVisited(false);
    }
}

// void Graph::print(std::priority_queue<std::pair<double, std::string>>& q){
//     std::priority_queue<std::pair<double, std::string>> temp = q;
//     while(!temp.empty()){
//         auto i = temp.top();
//         std::cout << i.second << " " << i.first << std::endl;
//         temp.pop();
//     }
// }

// void Graph::test(){
//     for(auto i = adjList_.begin(); i != adjList_.end(); i++){
//         for(auto j = i->second.begin(); j != i->second.end(); j++){
//             std::cout << " Source " << j->getSource() <<  " Dest  " << j->getDest() << " " << j->getWeight() << std::endl;
//         }
//     }
// }
