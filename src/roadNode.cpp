//Ryan Nguyen, Yan Kochin, CS 133, Final Project:Pathway finding, Professor Obourn
//This project involves an interactable GUI that lets the user find the quickest path
//between nodes, and then allows them to manipulate the pathways and nodes by creating
//new nodes and paths
#include "roadNode.h"
//This constructor initializes the values of the node
roadNode::roadNode(int key, int cord_x, int cord_y){
    this->key = key;
    this->cord_x = cord_x;
    this->cord_y = cord_y;
}
//This finds the distance between this and another node
double roadNode::distanceCal(roadNode* other){
    return sqrt(pow((cord_x-other->cord_x),2) + pow((cord_y-other->cord_y),2));
}
//This function compares the coordinates of this node and another
bool roadNode::operator== (const roadNode* other){
        return (cord_x == other->cord_x) && (cord_y == other->cord_y);
}