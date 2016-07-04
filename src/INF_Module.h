//
//  INF_Module.h
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "circleStep.h"
#include "Bjorklund.h"

class INF_Module{
    
public:
    
    int index, gap;
    ofPoint pos;
    float radius;
    int seqAmt;
    
    vector<circleStep*>stepGui;
    vector<ofxDatGuiComponent*>components;
    vector<Bjorklund*>euclids;
    vector<bool>loop;
    vector<bool>::iterator sequenceIterator;
    
    ofRectangle *rect;
    
    INF_Module(){};
    INF_Module(int _index);
    ~INF_Module();
    void setup();
    void setGui();
    void update();
    void draw();
    void exit();
    
    //Event Callbacks
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void sequenceCallback(Sequence &e);
};