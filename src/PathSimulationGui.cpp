//Ryan Nguyen, Yan Kochin, CS 133, Final Project:Pathway finding, Professor Obourn
//This project involves an interactable GUI that lets the user find the quickest path
//between nodes, and then allows them to manipulate the pathways and nodes by creating
//new nodes and paths
#include "PathSimulationGui.h"
static const  string GONODE = "Go Node.png";
static const  string NONODE = "No Go Node.png";
static const  string SENODE = "Select Node.png";
static const  string NENODE = "New Node.png";
static const  string MAP = "Map.jpg";
static const  int BUTTON = 0;
static const  int CHECKBOX = 1;
static const  int DS = 10;


static const bool LOAD_DEFAULT_PIC = true;
//This constructor takes in a file and creates a map of nodes that can be interacted with
PathSimulationGui::PathSimulationGui() {
    ifstream file = promptfileSave();
    newMap = new networkManager(&file);
    Frame = new GWindow(1920,1000,true);
    //If the file is readable, then it creates a new object that contains all the information
    //on each of the nodes, as well as a different object that creates the GUI, by creating all
    //of the default information in it
    Frame->setBackground("black");
    Frame->setVisible(true);
    Frame->setResizable(true);
    //This allows the GUI to use information given by the network/map of nodes by creating its
    //own map in the GUI
    network = newMap->exportNetWork();
    Frame->setTitle("Path Finding");
    Frame->setRepaintImmediately(true);
    //This function creates all the interactables that the user can use
    initializeGui();
     //These next two function create the map that the user can see and interact with
    drawPath();
    drawNode();
    Frame->setRepaintImmediately(false);
    Frame->repaint();
}
//This function creates all of the interactable buttons and checkboxes that the user
//can click to manipulate the map, as well as adding a mouse listener that allows
//the user to actually click on the map and change its information
void PathSimulationGui::initializeGui(){
    if (LOAD_DEFAULT_PIC){
        Frame->drawImage(MAP,0,0);
    }
    connect = createButton("Connect", GWindow::REGION_SOUTH);
    execute = createButton("Execute", GWindow::REGION_SOUTH);
    save = createButton("Save", GWindow::REGION_SOUTH);
    selectCreate = createCheckBox("Create", GWindow::REGION_SOUTH);
    selectLink = createCheckBox("Link", GWindow::REGION_SOUTH);
    selectErase = createCheckBox("Remove", GWindow::REGION_SOUTH);
    Frame->setMouseListener([this](GEvent event) {this->mouseClickProcess(event);});
}
//This function reduces redundancy by creating a button each time that it is called, as well as
//adding an action listener to it
GButton* PathSimulationGui::createButton(string text, GWindow::Region region){
    GButton* button = new GButton(text);
    Frame->addToRegion(button, region);
    button->setActionListener([=](GEvent event){this->buttonClickProcess(event);});
    return button;
}
//This function reduces redundancy by creating checkboxes as well as adding a listener to it
GCheckBox* PathSimulationGui::createCheckBox(string text, GWindow::Region region){
    GCheckBox* checkBox = new GCheckBox(text);
    checkBox->setColor("white");
    checkBox->setActionListener([=](GEvent event){this->checkBoxProcess(event);});
    Frame->addToRegion(checkBox, region);
    return checkBox;
}
//This function finds the path whenever the user has selected two nodes and will find a path in real time
void PathSimulationGui::findPath(){
    if (SelectedQueue.size()>=2){
        Frame->clear();
        renewNode();
        Frame->repaint();
        roadNode* One = SelectedQueue.front()->node;
        SelectedQueue.pop();
        roadNode* Two = SelectedQueue.front()->node;
        SelectedQueue.pop();
        SelectedQueue = {};
        newMap->initializeFindPath(One,Two);
        Frame->setTimerListener((50),[this]{
            this->incrementFindPath();
        });
        
    }
}
//This function takes a priority queue and colors the quickest path between two nodes
void PathSimulationGui::incrementFindPath(){
    priority_queue<roadNode*, vector<roadNode*>, RouteCompare> enqueue;
    enqueue = newMap->getEnqueue();
    //if the priority queue is not empty, then the next node is colored as a node in the path
    if (!enqueue.empty()){
        newMap->genPath();
        roadNode* current = enqueue.top();
        createNodeTemp(current,SENODE);
        enqueue.pop();
        while(!enqueue.empty()){
            roadNode* front = enqueue.top();
            createNodeTemp(front,GONODE);
            enqueue.pop();
        }
        Frame->repaint();
    }else{ 
        //otherwise an updated path will be made on top of the green nodes
        Frame->removeTimerListener();
        renewNode();
        getPath = newMap->findPath();
        updatePath();
    }
}
//This function takes an event as a parameter and will change the status depending on
//what checkbox has been pressed
void PathSimulationGui::checkBoxProcess(GEvent event){
    GInteractor* checkBox = event.getInteractor();
    if (checkBox == selectCreate && selectCreate->isChecked()){
        selectLink->setChecked(false);
        selectErase->setChecked(false);
    }
    else if (checkBox == selectErase && selectErase->isChecked()){
        selectCreate->setChecked(false);
        selectLink->setChecked(false);
    }
    else if (checkBox == selectLink && selectLink->isChecked()){
        selectCreate->setChecked(false);
        selectErase->setChecked(false);
    }
}
ifstream PathSimulationGui::promptfileSave(){
    ifstream file(promptfileName());
    while (!file.good()){
        file = ifstream(promptfileName());
    }
    cout << "File is good"<<endl;
    return file;
}
string PathSimulationGui::promptfileName(){
    string fileName;
    cout<<endl<< "Please input a file name: ";
    cin >> fileName;
    return fileName;
}
//This function takes an event as a parameter and if a button has been pressed
//does an action   
void PathSimulationGui::buttonClickProcess(GEvent event){
    GInteractor* button = event.getInteractor();
    //If the button is the connect button and no checkboxes are selected, it will find
    //the quickest path between two nodes
    if (button == connect){
        if (!selectCreate->isChecked() &&
            !selectErase->isChecked() &&
            !selectLink->isChecked()){
                findPath();}
        else{ cout << "All Check Box need to be unchecked"<<endl;}
        }
    else if (button == execute){
        //If the button is the execute button, then it will either create a node, delete one
        //or create a new link between two selected nodes, or if not any of those, it will
        //export the current map to a file
        if (selectCreate->isChecked()){
            if(newNodePossible){
                roadNode* newNode = newMap->createCustomNode(newNode_x,newNode_y);
                createNodePerm(newNode);
                newNodePossible = false;
                renewNode();
            }
        }else if (selectErase->isChecked()){
            //Remove a node from the map
            roadNode* node = SelectedQueue.front()->node;
            ImageNode* temp = ImageNodeList[node->key];
            cout <<"Node key: "<<node->key<<endl;
            cout <<"Image Node: "<<ImageNodeList[node->key]->node->key;
            ImageNodeList.erase(node->key);
            delete(temp);
            newMap->removeNode(node);
            drawPath();
            renewNode();
            SelectedQueue = {}; 
        }
        else if (selectLink->isChecked()){
            //This will create a new link between two nodes
            roadNode* achor = SelectedQueue.front()->node; SelectedQueue.pop();
            while (!SelectedQueue.empty()){
                roadNode* link = SelectedQueue.front()->node;
                newMap->createCustomeLink(achor,link);
                SelectedQueue.pop();
            }
            renewNode();
        }
    }else if (button  == save){
        //This will export a map
        ofstream outfile;
        ofstream outmap;
        string filename = promptfileName();
        outfile.open(filename);
        newMap->exportMap(&outfile,&outmap);
        outmap.close();
        cout<<"file save:"<<endl;
    }
}
//This function will make sure that only a certain number of nodes are selected at a time maximum
//and will always update to have the first node be removed from the selected list,
//a la first-in-first-out
void PathSimulationGui::resetSelectNode(){
    while (SelectedQueue.size() > selectNumber){
        ImageNode* deselect = SelectedQueue.front();
        Frame->draw(deselect->image);
        SelectedQueue.pop();
    }
}
//This function takes an event as a parameter
bool PathSimulationGui::detectNode(GEvent event){
    //This finds the location of the mouse during its click
    int x = event.getX();
    int y = event.getY();
     //This goes through the map of ImageNodes, and if the location of the mouse press
    //is the location of a node, that node will be made blue, as well as adding that node
    //to a queue of selected nodes
    for(const auto& pair:ImageNodeList){
        if (pair.second){
            GImage* image = pair.second->image;
            if (image->contains(x,y)){
                SelectedQueue.push(pair.second); 
                resetSelectNode();
                createNodeTemp(pair.second->node,SENODE);
                createNodeTemp(SelectedQueue.front()->node,GONODE);  
                return true;
            }
        }      
    }
    return false;
}
//This function takes a node, and then draws an image of a node, in that location
void PathSimulationGui::createNodeTemp(roadNode* node, string type){
    int x = (node->cord_x*DS-12);
    int y = (node->cord_y*DS-12);
    Frame->drawImage(type,x,y);
}
//This function takes a click event as a parameter, and if the detectNode function returns false,
//aka does not locate a node, then it will create a blank node
void PathSimulationGui::createNodeTemp(GEvent event){
    renewNode();
     //if the mouse click has not been at a node, then a blank node is made where the click has happened
    if (!detectNode(event)){
        int x = (event.getX() / DS);
        int y = (event.getY() / DS);
        newNode_x = x;
        newNode_y = y;
        Frame->drawImage(NENODE,x*DS-12,y*DS-12); 
        newNodePossible = true;
    }
    
}
//This function checks to see if the mouse has been clicked, and if it has
//does a certain action depending on what the buttons and checkboxes have been set to
void PathSimulationGui::mouseClickProcess(GEvent event){
    int type = event.getEventType();
    if (type == MOUSE_PRESSED){
        resetSelectNode();
        //If the checkbox is to create a new node, one will be made
        if (selectCreate->isChecked()){
            selectNumber = 5;
            createNodeTemp(event);
        }
        //If the checkbox is to delete one node
        else if (selectErase->isChecked()){
            selectNumber = 1;
            detectNode(event);
        }
         //else if the link checkbox is to link many node into one achor node
        else if (selectLink->isChecked()){
            selectNumber = 5;
            detectNode(event);
        }
        //else it will assume the user is using the connect button
        else {
            selectNumber = 2;
            detectNode(event);}
    }
    Frame->repaint();
    
}
//This function takes two nodes and a color and draws one path between those two nodes
//in the specific color set out by the parameter
void PathSimulationGui::drawSinglePath(roadNode* One, roadNode* Two, string color){
    int x1 = One->cord_x*DS;
    int y1 = One->cord_y*DS;
    int x2 = Two->cord_x*DS;
    int y2 = Two->cord_y*DS;
    Frame->setForeground(color);
    Frame->drawLine(x1,y1,x2,y2);
    Frame->setForeground("white");

}
//This function creates a pathway between two user selected nodes by drawing a green path
//between each of the nodes inside of the pathway as well as changing the color of the nodes
//to be green
void PathSimulationGui::updatePath(){
    roadNode* nodeTwo;
    for (int i =1;i<getPath.size();i++){
        roadNode* nodeOne = network->at(getPath[i-1]);
        nodeTwo = network->at(getPath[i]);
        //This sets the path between the two nodes to be green
        drawSinglePath(nodeOne,nodeTwo,"green");
        //This creates a temporary green node above the nodes in the pathway vector
        //so that each node in the path is green rather than red
        createNodeTemp(nodeOne,GONODE);
    }
    createNodeTemp(nodeTwo,GONODE);
    Frame->repaint();

}
//This function draws the pathway between every single node by accessing each node's list
//of nodes that it is connected to
void PathSimulationGui::drawPath(){
    for (const auto& pair: *network){
        for (const auto value : pair.second->nodeList){
            drawSinglePath(pair.second,value,"white");
        }
    }
}
//This function redraws each node image again on the GUI by going through a vector of
//ImageNodes as well as drawing a map of pathways between nodes
void PathSimulationGui::renewNode(){
    Frame->clear();
    if (LOAD_DEFAULT_PIC){
        Frame->drawImage(MAP,0,0);
    }
    drawPath();
    for (const auto& pair:ImageNodeList){
        if (pair.second){
            GImage* image = pair.second->image;
            Frame->draw(image);
        }  
    }
    Frame->repaint();
}
//This function takes a node as a parameter and draws a new node, as well as
//creating a new imageNode by pairing the image with an actual node as well 
//as adding it to a vector that contains imageNodes
void PathSimulationGui::createNodePerm(roadNode* node){
    int x = node->cord_x;
    int y = node->cord_y;   
    GImage* image =  new GImage(NONODE,x*DS-12,y*DS-12);
    ImageNode* imageNode  = new ImageNode(node, image);
    ImageNodeList[node->key] = imageNode;
    Frame->draw(image);

}
//This function goes through every single node inside of the map of nodes
//and draws them by calling on the createNodePerm function
void PathSimulationGui::drawNode(){
    for (const auto& pair : *network){
        createNodePerm(pair.second);
    }
}