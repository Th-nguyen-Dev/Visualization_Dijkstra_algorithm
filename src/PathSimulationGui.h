//Ryan Nguyen, Yan Kochin, CS 133, Final Project:Pathway finding, Professor Obourn
//This project involves an interactable GUI that lets the user find the quickest path
//between nodes, and then allows them to manipulate the pathways and nodes by creating
//new nodes and paths
#ifndef PATH_SIMULATION_GUI
#define PATH_SIMULATION_GUI

#include <iostream>
#include "console.h"
#include "gwindow.h"
#include "glabel.h"
#include "gtextarea.h"
#include "gtextfield.h"
#include "gbutton.h"
#include "gcheckbox.h"
#include "gtypes.h"
#include "ginteractor.h"
#include "gfont.h"
#include "gcolor.h"
#include "gthread.h"
#include "gsound.h"
#include "goptionpane.h"
#include "gobjects.h"
#include "gcontainer.h"
#include "networkManager.h"
using namespace std;
using namespace sgl;
//This node is an image that pairs the specific image with a specific node
struct ImageNode{
    roadNode* node;
    GImage* image;
    ImageNode(roadNode* node, GImage* image){
        this->node = node;
        this->image = image;
    }
};
//This class is the entire interactable GUI that the user can use to find the quickest pathways
class PathSimulationGui {
public:
//This constructor creates the initial state of the GUI and the map that the user can use
    PathSimulationGui();
    
private: 
    ifstream promptfileSave();
    string promptfileName();
    //This function draws every single node in the map
    void drawNode();
    //This function draws every single node in the map
    void drawPath();
    //This function draws the pathway of the quickest path in a green color
    void updatePath();
    //This function makes sure that only two nodes are ever selected
    void resetSelectNode();
    //This function draws the path between two nodes, in the correct color
    void drawSinglePath(roadNode* One, roadNode* Two,string color);
    //This function can either select or create new nodes depending on
    //what has been pressed
    void mouseClickProcess(GEvent event);
    //This function creates the buttons and checkboxes that the user can interact with
    void initializeGui();
    //This button checks if a button has been pressed, and does a certain action
    //depending on whether certain checkboxes are selected, such as creating new nodes
    //or finding the fastest path between nodes
    void buttonClickProcess(GEvent event);
    //This function creates buttons, and is to reduce redundancy
    GButton* createButton(string text, GWindow::Region region);
    //This function creates new checkboxes, in order to reduce redundancy
    GCheckBox* createCheckBox(string text, GWindow::Region region);
     //This function finds the next node in the fastest path and colors it green, as well
    //as the path recursively
    void incrementFindPath();
    //This function creates a node at a specific location inside of the node, along with its color
    void createNodeTemp(roadNode* node, string type);
    //This function creates a new blank node if the user clicks on an empty spot when trying to create
    //new nodes
    void createNodeTemp(GEvent event);
    //This function creates a new node that then is added to the general list of nodes
    void createNodePerm(roadNode* node);
    ///This function detects whether a node has been pressed on and then colors it blue if it has been
    bool detectNode(GEvent event);
    //This function takes an event as a parameter and changes the checked status of checkboxes
    void checkBoxProcess(GEvent event);
    //This function finds the fastest path between two selected nodes
    void findPath();
    //This function redraws every single node in the map of nodes
    void renewNode();
    //This int makes sure that the selected nodes are reset at proper times
    int selectNumber;
    //This bool makes sure for the function to only create permenant nodes at correct times
    bool newNodePossible;
    //These ints is used to create new node locations
    int newNode_x;
    int newNode_y;
    ///This is the window that the GUI uses
    GWindow* Frame;
    //This vector contains the fastest pathway
    vector<int> getPath;
    //This map contains all of the ImageNodes so that they can be drawn
    map<int, ImageNode*> ImageNodeList;
    //This queue contains the nodes that have been selected by the user
    queue<ImageNode*> SelectedQueue;
    //This map is the map of all nodes that are connected to each other
    map<int, roadNode*>* network; 
    //These next GObjects are checkboxes that the user can use to either connect two nodes,
    //add new links, create new nodes, erase nodes, or perform actions
    GCheckBox* selectLink;
    GCheckBox* selectCreate;
    GCheckBox* selectErase;
    GButton* save;
    GButton* execute;
    GButton* connect;
    //This network manager is for actually finding the fastest path
    networkManager* newMap;
};

#endif