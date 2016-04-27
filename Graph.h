/*
Peter Strayer
4/27/2016
Upendra/Hoenigman
Final Project
*/

#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct cityVectorItem //use for Floyd-Warshall result vector of all shortest distances to all other cities in graph
{
    std::string cityName;
    int distance2;       //initialize to infinity (or some large number)
    int lastEdgeIndexi; //last distance segment added to distance 2
    int lastEdgeIndexj;
};

struct adjVertex //struct for graph edges in vector of edges connected to a vertex
{
    vertex *v;
    int weight;
};

struct vertex //struct for a graph node
{
    std::string name;
    int district;
    bool visited;
    int distance; //used with Dykstra
    std::vector<cityVectorItem> cityVector; //Floyd-Warshall length of shortest path between starting city and ending city
    vertex *parent;
    std::vector<adjVertex> adj;
};

struct queueVertex
{//vector or pointers of vertices to keep track of path
    int distance;
    std::vector<vertex *> path;
};

class Graph
{
    public:
        Graph();
        ~Graph();
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string n);
        void displayEdges();
        void assignDistricts();
        //void BFTraversalLabel(std::string startingCity, int distID);
        void shortestPath(std::string startingCity,std::string endingCity);
        void shortestDistanceDykstra(std::string startingCity,std::string endingCity);
        //void shortestDistanceBellmanFord(std::string startingCity,std::string endingCity);
        void shortestDistanceFloydWarshall();
        void readTextEDGE(std::string lineData, int cot, int lineCount);
        //void readTextEDGE2(std::string lineData2, int cot, int lineCount);
        void readTextVERTEX(std::string lineData, int cot, int lineCount);
        //void readTextVERTEX2(std::string lineData2, int cot, int lineCount);

        vertex * findVertex(std::string name);

    protected:
    private:
        std::vector<vertex> vertices;
        std::vector<vertex *> correctPath;
        std::vector<vertex> tripvertices;
       // std::vector<vertex *> correctTrip;
        //int bestDistance = 10000000000; int tripDistance = 0;
        //std::vector<std::string> tmpItinerary;
        //std::vector<std::string> itinerary;
};

#endif // GRAPH_H
