/*
Peter Strayer
4/27/2016
Upendra/Hoenigman
Final Project
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[])
{
    Graph graphM;   //call graph class in main

    //graphM.buildGraph();

    int num, cot = 0, lineCount = 0;    //set up int counter for main menu choices
    string lineData, lineData2; //strings to read in text file info
    //bool oldgraph = true; //Boolean to choose which graph to run Floyd-Warshall on

    ifstream inFile;    //open ifstream for text file info
    inFile.open(argv[1]);
    if(inFile.good())
    {
        getline(inFile, lineData);
        graphM.readTextVERTEX(lineData, cot, lineCount);
        while(getline(inFile, lineData))
        {
            //read in city info
            //16 elements in each line 1 city and 15 adjacent verticies
            graphM.readTextEDGE(lineData, cot, lineCount);
            lineCount++;
        }
    }
    else
        num = 6;    //end program if file does not open correctly

    inFile.close();

    while(num != 6) //while user has not quit print menu
    {
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Find districts" << endl;
        cout << "3. Find shortest path between two cities using BFS" << endl;
        cout << "4. Find shortest distance between two cities using Dykstra" << endl;
        cout << "5. Find shortest distance between two cities using Floyd-Warshall" << endl;
        cout << "6. Quit" << endl;

        cin >> num;
        cin.ignore();   //NECCESSARY IF USING CIN>>  && GETLINE(CIN,STR)

        if(num == 1)    //PRINT VERTICES
            graphM.displayEdges();
        if(num == 2)    //FIND DISTRICTS
            graphM.assignDistricts();
       if(num == 3)    //FIND SHORTEST PATH BETWEEN ANY TWO CITIES USING BFS
        {
            string city, city2;
            cout << "Enter a starting city:" << endl;
            getline(cin, city);
            cout << "Enter an ending city:" << endl;
            getline(cin, city2);
            graphM.shortestPath(city,city2);
        }
        if (num == 4)  //FIND SHORTEST PATH BETWEEN ANY TWO CITIES USING DYKSTRA
        {
            string city, city2;
            cout << "Enter a starting city:" << endl;
            getline(cin, city);
            cout << "Enter an ending city:" << endl;
            getline(cin, city2);
            graphM.shortestDistanceDykstra(city,city2);
        }
        if (num == 5) //FIND SHORTEST DISTANCE BETWEEN all CITIES w/ FLOYD-WARSHALL
                             //USE SAME GRAPH AS FOR MENU ITEMS 1-4
        {
            graphM.shortestDistanceFloydWarshall();
        }
}
    cout << "Goodbye!" << endl;

    return 0;
}
