//
//  Dat_Docker.h
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#ifndef Dat_Docker_h
#define Dat_Docker_h

#include "ofxDatGui.h"
#include "DatIndex.h"
#include "ButtonEvent.h"

struct MidiState{
public:
    
    int device, channel;
    string deviceName;
    MidiState():device(0), channel(0){
        
    }
};

typedef shared_ptr<ofxDatGuiDropdown> DropPTR;

class Dat_Docker{
public:
    
    //ofEvents
    ofEvent<MidiState>deviceState;
    ofEvent<bool>modeChange;
    MidiState midiParam;
    
    //GUI Components
    vector<ofxDatGuiComponent*> components;
    vector<string>ch;
    DatIndex *browser;
    
    vector<DropPTR>deviceGUI;
    
    
    int width, height;
    int deviceNum;
    bool start;
    ofPoint pos;
    
    //constructor and functions
    Dat_Docker();
    Dat_Docker(vector<string>&deviceList);
    ~Dat_Docker(){
        if(browser != NULL)
            delete browser;
    };
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }
    void getDeviceList(vector<string> &list);
    void selectDevice(ofxDatGuiDropdownEvent e);
    void selectChannel(ofxDatGuiDropdownEvent e);
    void modeChanged(ofxDatGuiDropdownEvent e);
    void pageAdded(ofxDatGuiButtonEvent e);
    void update();
    void draw();
    
private:
    vector<string>list;
    
};

#endif /* Dat_Docker_h */
