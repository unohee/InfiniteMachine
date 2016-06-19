#pragma once
#include "ofMain.h"
#include "ofxDatGui.h"
#include "INF_Utils.h"

//Base class of ofxDatGui Panels
class DatPanel {
public:
    DatPanel(){
        
    };
    ~DatPanel(){
        try{
            if(!components.empty())
                for_each(components.begin(),components.end(),DeleteVector<ofxDatGuiComponent*>());
        }catch(exception e){
            cout<<e.what()<<endl;
        }
    };
    void update();
    void draw();
    vector<ofxDatGuiComponent*> components;
    
};