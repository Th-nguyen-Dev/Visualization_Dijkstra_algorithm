#include <iostream>
#include <queue>
#include "roadNode.h"
#include <fstream>
#include <sstream>

#ifndef _networkManager_h
#define _networkManager_h
class networkManager{
    public:
     //This constructor takes a file as a parameter and creates a map of nodes out of it
    networkManager(ifstream* file);
    //This function takes the file, reads it line by line, and creates the map
    //depending on what the file line contained
    void genfromFile(ifstream*file);
    //This function creates the vector of node keys of the fastest pathway
    vector<int> findPath();
    //This function takes two nodes, and sets all the values for the nodes so that
    //the actual pathfinder can analyze properly
    void initializeFindPath(roadNode* here, roadNode* there);
    //This function exports the map to a separate file
    void exportMap(ofstream* out, ofstream* outMap);
    //This function returns a map of nodes
    map<int,roadNode*>* exportNetWork();
    //This function looks through the priority queue and finds the fastest path by looking through the nodes
    //connected nodes
    void genPath();
    //This function takes location information and returns a new node
    roadNode* createCustomNode(int x, int y);
    //This functino creates a new link between two nodes
    void createCustomeLink(roadNode*& achor,roadNode*& link);
    priority_queue<roadNode*, vector<roadNode*>, RouteCompare> getEnqueue();
    void removeNode(roadNode*& remove);
    private:
    //This function takes a line of text and creates a node
    void createNode(istringstream& input);
    //This function connects two nodes with a line of text
    void connectNode(istringstream& input);
    //This function does the calculations for the two nodes that are to be connected
    void genPathHelper(roadNode* current, roadNode*& node);
     //This priority queue is what it uses to find the fastest path
    priority_queue<roadNode*, vector<roadNode*>, RouteCompare> enqueue;
     //This function returns the size of the map
    int size;
    //This set of nodes contains the queue of nodes in the fastest path
    set<roadNode*> storeQueue;
    //This is the map of all the nodes
    map<int, roadNode*> network;
    //This node is the first node in the connection
    roadNode* here;
     //This node is the last node in the connection
    roadNode* there;
    
};
#endif