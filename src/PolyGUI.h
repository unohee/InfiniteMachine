#pragma once

#include "ofMain.h"
#include "ofxMeshFont2D.h"
#include <iostream>
#include <stdexcept>

class PolyGUI : public ofNode {
public:
    
    
    PolyGUI(){
        point.setMode(OF_PRIMITIVE_POINTS);
        innerPoly.setMode(OF_PRIMITIVE_LINE_LOOP);
        outerPoly.setMode(OF_PRIMITIVE_LINE_LOOP);
        cout<<"[PolyGUI initialized]"<<ofGetElapsedTimef()<<endl;
    }
    PolyGUI(float _radius, ofVec3f &_pos, string &typeTag);//completed constructor
    ~PolyGUI(){//Destructor;
        cout<<"[PolyGUI is deleted]"<<endl;
    }
    
    void mouseOver();
    void setOSC(string HOST, int PORT){
        address = HOST;
    };
    void createPoly(vector<bool> &seq);
    void createMesh();
    void draw();
    
    vector<ofVec3f>steps;
    
    float width, height;
    float radius;
    ofMatrix4x4 m;
    ofVec3f pos;
    
    bool isFloat;
    int playHead;
    int pulses;
    
    string typeTag;
    string address;
    
    //cFrame
    ofVboMesh outerPoly;
    ofVboMesh innerPoly;
    ofMesh point, clock;
    ofMesh mesh ;//cFrame
    ofMesh meshOutline;//cFrame
    float elapsedTime;
    
    //rectFrame
    ofMesh polyLine;
    float lineWidth = 2;
    ofxMeshFont2D gui_id,gui_adrs;
    vector<ofxMeshFont2D> fonts;
    
};