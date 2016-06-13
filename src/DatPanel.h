#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"

//Base class of ofxDatGui Panels
class DatPanel {
public:
    DatPanel(){
        
    };
    ~DatPanel(){
        for (int i = 0; i < components.size(); ++i) {
            delete components[i];
        }
        components.clear();
    };
    void update();
    void draw();
    vector<ofxDatGuiComponent*> components;
    
};