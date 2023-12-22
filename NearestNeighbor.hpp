#include <iostream>
#include <list>
#include <cmath>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

class Node{
    public:
    double distance(Node a) const;
    Node();
    Node(const std::string &x_coord,const std::string &y_coord,const std::string &i);
    bool operator==(const Node& a){return id == a.id;}

    std::list<Node*> neighbors;
    double x_coordinate;
    double y_coordinate;
    int id;
};

/**
 * @brief Parameterized Constructor for node
 * 
 * @param x_cooord : x coordinate of node
 * @param y_coord :y coordinate of node
 * @param i :id of node
 */
Node::Node(const std::string &x_coord,const std::string &y_coord,const std::string &i):x_coordinate{std::stod(x_coord)},y_coordinate{std::stod(y_coord)},id{std::stoi(i)}{
}
/**
 * @param: A node calculate the distance to
 * @return a double that has the distance between the 2 nodes
 */
double Node::distance(Node a) const{
    double x = x_coordinate - a.x_coordinate;
    double y = y_coordinate - a.y_coordinate;
    return std::sqrt(std::pow(x,2) + std::pow(y,2));
}

/**
 * @brief NearestNeighbor implementation
 * 
 * @param A string of the filename that stores the coordinates of the cities
 */
void nearestNeighbor(std::string filename){
    std::ifstream file(filename);
    std::string junk,id,x_c,y_c;
    for(int i = 0; i < 7;i++){
        std::getline(file,junk);    //removes first seven lines
    }
    std::list<Node> cities;
    while(file >> id >> x_c >> y_c){
        Node x(x_c,y_c,id);
        cities.push_back(x);
    }

    std::queue<Node> result;
    Node first = cities.front();    //copy of first node to go back to at the end
    Node temp = cities.front(); 
    double total_dist = 0;   
    auto start = high_resolution_clock::now();
   
    while(!cities.empty()){
        result.push(temp);
        cities.remove(temp);
        double length = 99999999999999999;
        if(cities.empty()){
            break;
        }
        for(auto const& i : cities){
            if(length > temp.distance(i)){      //if distance is less than current distance
                length = temp.distance(i);          //current distance is new distance
                temp = i;                           //new node is previous closest node
            }
        }
        total_dist += length;
    }
    result.push(first);
    total_dist += temp.distance(first);
    
    auto stop = high_resolution_clock::now();
    auto l = duration_cast<milliseconds>(stop-start);
    double len = l.count();
    while(!result.empty()){
        std::cout << result.front().id << " ";
        result.pop();
    }
    std::cout << std::endl << "Total Distance: "<< total_dist << std::endl;
    std::cout << "Time in ms: " << len;
}