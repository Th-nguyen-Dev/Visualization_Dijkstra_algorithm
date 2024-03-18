//Ryan Nguyen, Yan Kochin, CS 133, Final Project:Pathway finding, Professor Obourn
//This project involves an interactable GUI that lets the user find the quickest path
//between nodes, and then allows them to manipulate the pathways and nodes by creating
//new nodes and paths
#include <vector> 
#include <string>
#include <cmath>
#include <set>
#include <map>
using namespace std;
#ifndef _roadNode_h
#define _roadNode_h
//This class contains information on each individual node
class roadNode{
    public:
    //This contains the x and y coordinates of the node as well as its key
    int cord_x;
    int cord_y;
    int key;
    //This is used to find the previous node in the chain of the fastest path
    roadNode* prev;
    //This contains information whether the node has been visited
    bool visited;
    //This contains the distance at this node
    double disOriginal;
    //This contains the nodes connected to this one
    set<roadNode*> nodeList;
    //This constructor creates the node
    roadNode(int key, int cord_x, int cord_y);
    //This calculates the distance between this node and the other one
    double distanceCal(roadNode* other);
    //This compares whether the two nodes are in the same spot
    bool operator== (const roadNode* other);
};
//This struct returns the smaller of the two nodes
struct RouteCompare{
    bool operator()(const roadNode* one, const roadNode* two){
        return one->disOriginal > two->disOriginal;
    }
};
#endif