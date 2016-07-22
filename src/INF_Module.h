//
//  INF_Module.h
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "RoundedButton.h"
#include "INF_Controls.hpp"
#include "CircleStep.h"
#include "Bjorklund.h"


struct Sequence{
    Sequence(){};
    vector<bool>pattern;
    unique_ptr<int> index;
};

typedef shared_ptr<circleStep> CyclicSeq;
typedef shared_ptr<ofxDatGuiComponent> ofxDatGuiPtr;
typedef shared_ptr<RoundedButton> RButtonPtr;
typedef shared_ptr<INF_Controls> GuiPtr;
typedef unique_ptr<Sequence> Track;
class INF_Module{
    
public:
    
    int index, gap;
    ofPoint pos;
    float radius, cycleRad;
    int seqAmt;
    bool bEuclid;
    
    ofPoint guiLoc;
    unique_ptr<ofRectangle> rect_ptr;
    unique_ptr<RoundedButton> random;
    vector<RButtonPtr>rButtons;
    vector<CyclicSeq>stepGui;
    vector<GuiPtr> controls;
    vector<ofxDatGuiPtr>components;
    unique_ptr<Bjorklund> euclid;
    vector<Track> tracks;
    
    vector<bool>loop;
    vector<bool>::iterator sequenceIterator;
    
    INF_Module(){};
    INF_Module(int _index);
    ~INF_Module();
    void setup();
    void setGui();
    void update();
    void draw();
    
    //
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