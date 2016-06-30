//
//  DatIndex.h
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#ifndef DatIndex_h
#define DatIndex_h

#include "DatPanel.h"
#include "DatButton.h"
#include "DatDropdown.h"

class DatIndex{
public:
    
    ofEvent<int>pageChanged;
    static ofEvent<int>pageChangedGlobal;
    
    ofPoint pos;
    int width, gap, size;
    int buttonIndex;
    vector<DatButton*> buttons; // numberbox
    vector<ofxDatGuiComponent*> control;
    
    
    //group of buttons for page browsing + MIDI I/O device setup etc.
    DatIndex();
    DatIndex(int x, int y);
    ~DatIndex(){
        for_each(buttons.begin(), buttons.end(), DeleteVector<DatButton*>());
        for_each(control.begin(), control.end(), DeleteVector<ofxDatGuiComponent*>());
        cout<<"[UPPER DOCKER DELETED]"<<endl;
    };
    
    void setup();
    void update();
    void render();
    int getWidth(){return size;};
    void exit();//deletion process
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    
    
};





#endif /* DatIndex_h */

