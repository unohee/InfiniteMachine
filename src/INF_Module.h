//
//  INF_Module.h
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "Sequence.h"
#include "INF_Controls.hpp"
#include "INF_Algorithm.h"
//Custom GUI
#include "RoundedButton.h"
#include "CircleStep.h"

typedef shared_ptr<circleStep> CyclicSeq;
typedef shared_ptr<ofxDatGuiComponent> ofxDatGuiPtr;
typedef shared_ptr<RoundedButton> RButtonPtr;
typedef shared_ptr<INF_Controls> GuiPtr;
typedef shared_ptr<Sequence> Track;
typedef INF_Algorithm Algorithms;
class INF_Module{
    
public:
    
    int index, gap;
    ofPoint pos;
    float radius, cycleRad;
    int seqAmt, tempoVal;
    int beatAmt, beatResolution;
    ofPoint guiLoc;
    //smart pointers
    unique_ptr<ofRectangle> rect_ptr;
    unique_ptr<RoundedButton> random;
    
    //vectors
    vector<RButtonPtr>rButtons;
    vector<CyclicSeq>stepGui;
    vector<GuiPtr> controls;
    vector<ofxDatGuiPtr>components;
    vector<Track> tracks;
    
    
    INF_Module(){};
    INF_Module(int _index);
    ~INF_Module();
    void setup();
    void setGui();
    void update();
    void draw();
    void setMeter(int amount, int beatResolution);
    int getClock();
    int getWidth() const{
        return rect_ptr->getWidth();
    }
    
    
    //Event Callbacks
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void customButtonEvent(ButtonEvent &e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void sequenceCallback(SequenceEvent &e);
    void seqParamChanged(Controls &e);
};