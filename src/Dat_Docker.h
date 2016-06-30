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
#include "DatDropdown.h"
#include "ImageButton.h"
#include "ButtonEvent.h"

class Dat_Docker{
public:
    
    //ofEvents
    ofEvent<int>deviceFocus; //eventArgs for linking GUI and MIDI Interface
    ofEvent<int>channelChanged;
    ofEvent<bool>deviceRefreshed;
    static ofEvent<int>deviceFocusGlobal;
    static ofEvent<int>midiChGlobal;
    
    //GUI Components
    vector<ofxDatGuiComponent*> components;
    vector<ImageButton*>buttons;
    vector<string>ch;
    DatIndex *browser;
    DatDropdown *device_list;
    vector<DatDropdown*> midi_lists;
    
    
    int width;
    int deviceNum;
    bool start;
    
    //constructor and functions
    Dat_Docker();
    Dat_Docker(vector<string>&deviceList);
    ~Dat_Docker(){
        delete browser;
    };
    int getWidth(){
        return width;
    }
    void getDeviceList(vector<string> &list);
    void selectDevice(ofxDatGuiDropdownEvent e);
    void selectChannel(ofxDatGuiDropdownEvent e);
    void bpmChanged(ofxDatGuiSliderEvent e){};
    void modeChanged(ofxDatGuiDropdownEvent e){};
    void customButtonEvent(customEvent &e);
    
    
    void pageAdded(ofxDatGuiButtonEvent e);
    void deviceRefresh(ofxDatGuiButtonEvent e);
    void update();
    void draw();
    
private:
    vector<string>list;
    
};

#endif /* Dat_Docker_h */
