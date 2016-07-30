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
    
    vector<bool>pattern;
    int index,pitch, velocity;
    
    Sequence():index(0), pitch(36), velocity(80){
        while(pattern.size() < 16){
            pattern.push_back(0);
        }
    };

};

typedef shared_ptr<circleStep> CyclicSeq;
typedef shared_ptr<ofxDatGuiComponent> ofxDatGuiPtr;
typedef shared_ptr<RoundedButton> RButtonPtr;
typedef shared_ptr<INF_Controls> GuiPtr;
typedef shared_ptr<Sequence> Track;

class INF_Module{
    
public:
    
    int index, gap;
    ofPoint pos;
    float radius, cycleRad;
    int seqAmt;
    ofPoint guiLoc;
    
    //smart pointers
    unique_ptr<ofRectangle> rect_ptr;
    unique_ptr<RoundedButton> random;
    unique_ptr<Bjorklund> euclid;
    
    //vectors
    vector<RButtonPtr>rButtons;
    vector<CyclicSeq>stepGui;
    vector<GuiPtr> controls;
    vector<ofxDatGuiPtr>components;
    vector<Track> tracks;
    vector<bool>::iterator sequenceIterator; //DEPRECATED
    
    
    
    INF_Module(){};
    INF_Module(int _index);
    ~INF_Module();
    void setup();
    void setGui();
    void update();
    void makeNew();
    void draw();

    int getWidth() const{
        return rect_ptr->getWidth();
    }
    int setMax(int max){
        
    }
    
    //Event Callbacks
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void customButtonEvent(ButtonEvent &e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void sequenceCallback(SequenceEvent &e);
    void seqParamChanged(Controls &e);
};