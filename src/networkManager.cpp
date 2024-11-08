//Ryan Nguyen, Yan Kochin, CS 133, Final Project:Pathway finding, Professor Obourn
//This project involves an interactable GUI that lets the user find the quickest path
//between nodes, and then allows them to manipulate the pathways and nodes by creating
//new nodes and paths
#include "networkManager.h"
#include <climits>
//This constructor creates a new network that can find the fastest path
networkManager::networkManager(ifstream* file){
    cout << "constructor"<<endl;
    genfromFile(file);
}
//This function erase a node from the map
void networkManager::removeNode(roadNode*& remove){
    for (auto value:remove->nodeList){
        value->nodeList.erase(remove);
    }
    network.erase(remove->key);
    remove = nullptr;
    delete(remove);
}
//This function creates nodes from an input file
void networkManager::createNode(istringstream& input){
    int key; input >> key;
    int x; input >> x;
    int y; input >> y; 
    //if the map does not contain the current key, it will then create a node at that key
    if (network.find(key) == network.end()){
        network[key] = new roadNode(key,x,y);
    }
    if (key>size){size = key;}
}
//This returns the map of nodes
map<int,roadNode*>* networkManager::exportNetWork(){
    return &network;
}
//This function creates a new link between two nodes
void networkManager::createCustomeLink(roadNode*& achor,roadNode*& link){
    achor->nodeList.insert(link);
    link->nodeList.insert(achor);
}
//This function creates a new node that is added to the map
roadNode* networkManager::createCustomNode(int x, int y){
    size++;
    network[size] =  new roadNode(size, x, y);
    return network[size];
}
//This function exports the map of nodes into a file in the correct format
void networkManager::exportMap(ofstream* out, ofstream* outMap){
    for (const auto& pair : network){
        string line;
        line += "n";
        line += " "; line += to_string (pair.first);
        line += " "; line += to_string (pair.second->cord_x);
        line += " "; line += to_string (pair.second->cord_y);
        line += "\n";
        *out << line;
    }
    for (const auto& pair : network){
        string line;
        line += "c";
        line += " " + to_string(pair.first);
        for(const auto value: pair.second->nodeList){
            line += " " +to_string(value->key);
        }
        line += "\n";
        *out << line;
    }
    out->close();
}
//This function takes a file as input and adds all the nodes that are connected to a node
//into a set of nodes
void networkManager::connectNode(istringstream& input){
    int key; input >> key;
    int nodeNum;
    while(input>>nodeNum){
        network[key]->nodeList.insert(network[nodeNum]);
    }
}
//This function looks through every single line in an input file and then
//either creates a connection between nodes or creates new nodes
void networkManager::genfromFile(ifstream* file){
    string line;   
    while (getline(*file, line)){
        istringstream input(line);
        char type; input >> type;
        if (type == 'n'){createNode(input);}
        else if (type == 'c') {connectNode(input);}
    }
}
//This function returns takes a node and adds it into the priority queue in the proper order
//if the node has not been visited or it has a shorter distance from the original
void networkManager::genPathHelper(roadNode* current, roadNode*& node){
    if (!node->visited){
        double tempDist = current->disOriginal + current->distanceCal(node);
        if (tempDist < node->disOriginal){
            node->disOriginal = tempDist;
            node->prev = current;
            storeQueue.insert(node);
            enqueue.push(node);
        }else if(storeQueue.count(node) == 0){ 
            storeQueue.insert(node);
            enqueue.push(node);
        }
    }
    
}
//This function looks through the priority queue if it is not empty and finds the fastest path for it
void networkManager::genPath(){
    if(!enqueue.empty()){
        //This finds the smallest node in the priority queue, and then looks through each of its connected
        //nodes in order to find the fastest path
        roadNode* current = enqueue.top();
        current->visited = true;
        enqueue.pop();
        storeQueue.erase(current);
        for (auto node : current->nodeList){
            genPathHelper(current, node);
        }
    }
}
//This function takes two nodes that are its beginning and end and initializes all information to find
//the fastest path
void networkManager::initializeFindPath(roadNode* here, roadNode* there){
    priority_queue<roadNode*, vector<roadNode*>, RouteCompare> empty;
    set<roadNode*> emptySet;
    storeQueue = emptySet;
    enqueue = empty;
     //This sets all of the nodes into having the same information so that they can be analyzed when
    //looking through to find the proper path
    for (auto& pair : network){
        pair.second->prev = nullptr;
        pair.second->visited = false;
        pair.second->disOriginal = INT_MAX;
    }
    this->here = here;
    this->there = there;
    //This adds the first node into both the priority queue and the set of nodes, and
    //sets the distance value to zero
    storeQueue.insert(here);
    enqueue.push(here);
    here->disOriginal = 0;

}
//This function returns the priority queue of nodes
priority_queue<roadNode*, vector<roadNode*>, RouteCompare> networkManager::getEnqueue(){
    return enqueue;
}
//This function finds the fastest path by looking through the each nodes previous node and making
//a vector of keys out of it, as well as returning that vector of node keys
vector<int> networkManager::findPath(){
    roadNode* prevNode = there;
    vector<int> route;
    route.push_back(prevNode->key);
    while(prevNode != here && prevNode != nullptr){
        prevNode = prevNode->prev;
        route.push_back(prevNode->key);
    }
    cout<< " distance travel: " <<there->disOriginal<<endl;
    return route;
}
