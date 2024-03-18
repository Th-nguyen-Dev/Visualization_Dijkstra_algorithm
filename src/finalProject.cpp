//Ryan Nguyen, Yan Kochin, CS 133, Final Project:Pathway finding, Professor Obourn
//This project involves an interactable GUI that lets the user find the quickest path
//between nodes, and then allows them to manipulate the pathways and nodes by creating
//new nodes and paths
#include "PathSimulationGui.h"
#include "networkManager.h"
#include <iostream>

using namespace std;
using namespace sgl;

//This function calls on the GUI, which then allows for a map of nodes to be manipulated
int main() {
    new PathSimulationGui();
    return 0;
}