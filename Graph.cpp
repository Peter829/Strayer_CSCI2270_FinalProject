/*
Peter Strayer
4/27/2016
Upendra/Hoenigman
This program is a continuation of Assignment 11
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "Graph.h"

using namespace std;

Graph::Graph()  //Constructor
{
    //ctor
}

Graph::~Graph() //Destructor
{
    //dtor
}

void Graph::readTextVERTEX(string lineData, int cot, int lineCount) //Read in cities from txt file & call addVertex function
{
        string cityData;
        istringstream ss(lineData);
        while(getline(ss, cityData, ',')) //FILL GRAPH WITH VALUES
        {
            if(cityData != "cities")
                addVertex(cityData);    //Calls addVertex for the city in cityData
        }
}



void Graph::readTextEDGE(string lineData, int cot, int lineCount)   //Read in cities from txt file & call addEdge function
{
        string cityData;
        int cont = 0;
        istringstream ss(lineData);
        while(getline(ss, cityData, ',') && cont != 1) //FILL GRAPH WITH EDGES
        {
            if(cityData != "-1" && cityData != "0")
            {
                if(cot != 0)
addEdge(vertices[lineCount].name, vertices[cot-1].name, atoi(cityData.c_str()));    //Calls addEdge for two vertices and the weight of the edge
            }
            else if(cityData == "0")
                cont = 1;
            cot++;
        }
}



void Graph::addVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == n)   //If vertex already exists print found
        {
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false)  //If vertex does not yet exist then assign name, initial & add to vector

    {
        vertex v;
        v.name = n;
        v.distance = 0;
        v.district = -1;
        v.parent = NULL;
        vertices.push_back(v);
    }
}


void Graph::addEdge(string v1, string v2, int weight)   //Function to traverse all vertices and add edges to the correct pairs
{
    for(int i = 0; i < vertices.size(); i++)    //For loop to traverse vertices
    {
        if(vertices[i].name == v1)              //Identify all edges from vertex v1
        {
            for(int j = 0; j < vertices.size(); j++)    //Loop to keep track of ending city
            {
                if(vertices[j].name == v2 && i != j)    //If ending city is equal to v2 and is not starting city
                {
                    adjVertex av;   //Create instance of adjVertex
                    av.v = &vertices[j];    //set ending city pointer to adjVertex pointer value
                    av.weight = weight;     //set ending city weight
                    vertices[i].adj.push_back(av);  //push ending city back on starting city's adj list

                    adjVertex av2;  //Create new instance of adjVertex for linking the cities together through the adjacent city's struct
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}


void Graph::displayEdges()  //Display all edges of the graph
{
    for(int i = 0; i < vertices.size(); i++)
    {
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout<<vertices[i].adj[j].v->name<<"***";
        }
        cout<<endl;
    }
}


void Graph::assignDistricts()   //Assign districts to all vertices
{
    int districtCounter = 1;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].district < 0)    //If districts have not been assigned
        {
            vertices[i].district = districtCounter; //Set vertex district equal to 1

            for(int j = 0; j < vertices[i].adj.size(); j++)
            {
                vertices[i].adj[j].v->district = districtCounter;   //Assign the same district value to all adj cities
                for(int k = 0; k < vertices[i].adj[j].v->adj.size(); k++)
                {
                   if(vertices[i].adj[j].v->adj[k].v->district < 0)
                      vertices[i].adj[j].v->adj[k].v->district = districtCounter;   //Assign the same district value to all adj city's adj cities
                }
            }
            districtCounter++;  //Increment district counter to move on to the next one
        }
    }
}

void Graph::shortestPath(string startingCity,string endingCity) //BFS to determine shortest path(smallest number of edges) between two vertices
{
        bool check1 = false, check2 = false, done = false;  //Various booleans to check districts and end loop
        int posCount1 = 0, posCount2 = 0,  m = 0;   //Various integers to determine the index of starting city
        queueVertex qv; //Create instance of queueVertex

        for(int i = 0; i < vertices.size(); i++)    //Loop through vertices
        {
            if(vertices[i].name == startingCity)    //Find each city in vertices vector
            {
                check1 = true;
                posCount1 = i;
            }
            if(vertices[i].name == endingCity)  //Find each city in vertices vector
            {
                check2 = true;
                posCount2 = i;
            }
        }

        if(check1 == true && check2 == true)    //Both cities exist in graph
        {
            if(vertices[posCount1].district > 0 || vertices[posCount2].district > 0)    //Either city has district assigned
            {
                if(vertices[posCount1].district == vertices[posCount2].district)        //Both cities are in same district
                {
                    vertices[posCount1].visited = true;     //Set visited value of city to true
                    vertex *vptr = &vertices[posCount1];    //Set pointer

                    qv.path.push_back(vptr);                //Push shortest path vertex back on to the path vector
                    int k = 0, target = -1, pathPosition = 0;   //Various integers to count

                    vertices[posCount1].parent = NULL;      //Set city's parent to NULL
                    while(done == false)    //Loop until done equals true
                    {
                        for(int j = 0; j < qv.path[m]->adj.size(); j++)
                        {
                            if((qv.path[m]->adj[j].v->visited == false)&&(done!=true))
                            {
                                qv.path[m]->adj[j].v->distance = qv.path[m]->distance + 1;  //Increment distance counter
                                qv.path[m]->adj[j].v->parent = qv.path[m];  //Set adjacent cities parent to the vertex city
                                vptr = qv.path[m]->adj[j].v;

                                vptr->visited = true;   //Set pointer city to visited

                                if(vptr->name == endingCity)
                                    done = true;
                                qv.path.push_back(vptr);
                             }

                            else if((qv.path[m]->adj[j].v->visited == true) && (m < qv.path.size()))
                                m++;
                        }
                    }

                    vptr = qv.path[qv.path.size() - 1];
                    while(vptr->parent != NULL) //Loop until city's parent is found
                    {
                        correctPath.push_back(vptr);
                        vptr = vptr->parent;
                        k++;
                    }

                    correctPath.push_back(vptr);
                    cout << k;
                    int p;
                    for( p = correctPath.size() -1; p >= 0; p--)
                    {
                        cout << "," << correctPath[p]->name;
                    }
                    cout << endl;
                    correctPath.clear();
                    for(int i = 0; i < vertices.size(); i++)
                    {
                        vertices[i].distance = 0;
                        vertices[i].visited = false;
                    }
                    //RESET correctPath - otherwise the previous results print as well
                }
                else
                    cout << "No safe path between cities" << endl;
            }
            else
                cout << "Please identify the districts before checking the distances" << endl;

        }
        else
            cout << "One or more cities doesn't exist" << endl;
    //}

}

void Graph::shortestDistanceDykstra(string startingCity,string endingCity)  //
{
    bool check1 = false, check2 = false, done = false;
    int posCount1 = 0, posCount2 = 0, bestDistance = 100000, m = 0;
    queueVertex qv;
    for(int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i].name == startingCity)
        {
            check1 = true;
            posCount1 = i;
        }
        if(vertices[i].name == endingCity)
        {
            check2 = true;
            posCount2 = i;
        }
    }
        if(check1 == true && check2 == true)
        {
            if(vertices[posCount1].district > 0 || vertices[posCount2].district > 0)
            {
                if(vertices[posCount1].district == vertices[posCount2].district)
                {
                    vertices[posCount1].visited = true;
                    //cout<<vertices[posCount1].name<<" was visited"<<endl;
                    vertex *vptr = &vertices[posCount1];
                    //cout<<"after vertex *vptr = line"<<endl;
                    qv.path.push_back(vptr);
                    //cout<<"after push_back line"<<endl;
                    int k = 0, target = -1, pathPosition = 0;
                    vertices[posCount1].parent = NULL;
                    //cout<<"about to enter the while loop"<<endl;
                    while(done == false)
                    {
                        //target = -1;
                        bestDistance = 100000;
                        target = -1;  //upon looping through reset this
                        //cout<<"target set to "<<target<<" and m = "<<m<<endl;
                        //cout<<"for loop will end at "<<qv.path[m]->adj.size()<<endl;
                        for(int j = 0; j < qv.path[m]->adj.size(); j++)
                        {
                            //cout<<"entered for loop with the j index"<<endl;
                            if((qv.path[m]->adj[j].v->visited == false) && ((qv.path[m]->distance + qv.path[m]->adj[j].weight) < bestDistance))
                            {
                                //cout<<"entered inner if statement with visited == false && sum < bestDistance"<<endl;
                                bestDistance = qv.path[m]->distance + qv.path[m]->adj[j].weight;
                                target = j;
                                pathPosition = m;
                            }
                            //cout<<"after if statement and target = "<<target<<" and bestDistance = "<<bestDistance<<endl;

                        }
                        if((bestDistance > 0)&& (target != -1) && (m = qv.path.size())) //changed this so best distance is measured after all
                                                                   //not visited nodes next to path nodes are checked
                        {
                           // cout<<"entered if statement if bestDistance > 0"<<endl;
                            vptr = qv.path[pathPosition]->adj[target].v;
                           // cout<<"after vptr = line"<<endl;
                            vptr->parent = qv.path[pathPosition];
                          //  cout<<"after vptr->parent = line"<<endl;
                            vptr->visited = true;
                           // cout<<"visited "<<vptr->name<<endl;
                            vptr->distance = bestDistance;
                            //cout<<"set distance to bestDistance"<<endl;
                            if(vptr->name == endingCity)
                            {
                               // cout<<"done is set to true"<<endl;
                                done = true;
                            }
                                //done = true;

                            qv.path.push_back(vptr);
                            //cout<<"after push_back at the end of the if bestDistance > 0"<<endl;
                            m = 0;
                        }
                         //if (m = qv.path.size())
                            //m = 0;
                         //else m++;
                         else if (m < qv.path.size())
                            m++;
                    }
                    //cout<<"ready to retrace the path"<<endl;
                    vptr = qv.path[qv.path.size() - 1];
                    while(vptr->parent != NULL)
                    {
                        //cout<<"entered while until parent is NULL"<<endl;
                        correctPath.push_back(vptr);
                        vptr = vptr->parent;
                        k++;
                        //cout<<"k was updated to "<<k<<endl;
                    }
                    correctPath.push_back(vptr);
                    //k++;  this was already updated before the while loop stopped

                    //cout<<"ready to print the path"<<endl;
                    cout << bestDistance;
                    int p;
                    for( p = correctPath.size() -1; p >= 0; p--)
                    {
                        cout << "," << correctPath[p]->name;
                    }
                    cout << endl;
                    correctPath.clear();
                    for(int i = 0; i < vertices.size(); i++)
                    {
                        vertices[i].distance = 0;
                        vertices[i].visited = false;
                    }
                    //RESET correctPath - otherwise the previous results print as well
                }
                else
                    cout << "No safe path between cities" << endl;
            }
            else
                cout << "Please identify the districts before checking the distances" << endl;

        }
        else
            cout << "One or more cities doesn't exist" << endl;

}


void Graph::shortestDistanceFloydWarshall()
{
    cityVectorItem tmpCity;
    for(int i = 0; i < vertices.size(); i++)
    {
        tmpCity.cityName = vertices[i].name;
        tmpCity.distance2 = 10000000; //instead, set to infinity
        tmpCity.lastEdgeIndexi = i;
        for(int j=0; j < vertices.size(); j++)
        {
            if (i==j)tmpCity.distance2 = 0;
            tmpCity.lastEdgeIndexj = j;
            vertices[j].cityVector.push_back(tmpCity); //initialize the city vectors in each graph node
        }                                               //it will store shortest distances to each other node
     }
     for(int i=0; i < vertices.size(); i++)
     {
         for(int j=0; j < vertices.size(); j++)
         {
             for(int k=0; k < vertices[i].adj.size(); k++)
             {
                 if (vertices[i].adj[k].v->name == vertices[i].cityVector[j].cityName)
                 {
                    vertices[i].cityVector[j].distance2 = vertices[i].adj[k].weight;
                 }
             }
         }
     }
     //update distance2 values with Floyd-Warshall process for cities in the same district
     for(int i=0; i < vertices.size(); i++)
     {
         for(int j = 0; j < vertices.size(); j++)
         {
            if ( i != j)
             {
             for(int m = 0; m < vertices.size(); m++)
             {
                // cout<<vertices[j].cityVector[i].distance2<<" distance through i "<<endl;
                 if ((vertices[j].cityVector[m].distance2 > (vertices[j].cityVector[i].distance2 + vertices[i].cityVector[m].distance2))&&\
                    ((vertices[j].cityVector[i].distance2 + vertices[i].cityVector[m].distance2) < 2*10000000))
                 {
                   // cout<<"distance before update = "<<vertices[j].cityVector[m].distance2<<" i,j,m = "<<i<<" , "<<j<<" , "<<m<<endl;
                   // cout<<vertices[j].cityVector[m].cityName<<" , "<<vertices[j].cityVector[m].distance2<<endl;
                   // cout<<vertices[j].cityVector[i].cityName<<" , "<<vertices[j].cityVector[i].distance2<<endl;
                   // cout<<vertices[i].cityVector[m].cityName<<" , "<<vertices[i].cityVector[m].distance2<<endl;
                    vertices[j].cityVector[m].distance2 = vertices[j].cityVector[i].distance2 + vertices[i].cityVector[m].distance2 ;
                    vertices[m].cityVector[j].distance2 = vertices[j].cityVector[m].distance2;
                    vertices[j].cityVector[m].lastEdgeIndexi = i;
                    vertices[j].cityVector[m].lastEdgeIndexj = m;
                   // cout<<"distance after update = "<<vertices[j].cityVector[m].distance2<<endl;
                 }
             }
             }
         }
     }
     //print results
     for(int i = 0; i < vertices.size(); i++)
     {

         for(int j = 0; j < vertices.size(); j++)
         {
            cout<<vertices[i].name<<" to ";
            cout<<vertices[i].cityVector[j].cityName<<": "<<vertices[i].cityVector[j].distance2<<endl;

         }
     }
}


