#pragma once

#include "ofMain.h"
#include "ofxMeshFont2D.h"

class PolyGUI : public ofNode {
public:
    
    
    PolyGUI(){
        cout<<"[PolyGUI initialized]"<<ofGetElapsedTimef()<<endl;
    }
    PolyGUI(float _radius, ofVec3f _pos, string typeTag);//completed constructor
    ~PolyGUI(){//Destructor;
        cout<<"PolyGUI is deleted"<<endl;
    }
    void mouseOver(ofVec3f input) {
        float disX = pos.x - input.x;
        float disY = pos.y - input.y;
        (sqrt(pow(disX, 2) + pow(disY,2)) < radius*2 ) ? isFloat : !isFloat;
    }
    void setOSC(string HOST, int PORT){
        address = HOST;
    };
    void createPoly(vector<bool> &seq);
    void createMesh();
    using ofNode::draw;
    void draw();
    
    vector<ofVec3f>steps;
    
    float width, height;
    float radius;
    ofMatrix4x4 m;
    ofVec3f pos;
    
    bool isFloat;
    int playHead;
    float angle;
    int length, pulses;
    
    string typeTag;
    string address;
    
    //cFrame
    ofPolyline outerPoly, innerPoly;
    ofMesh point, clock;
    ofMesh mesh;//cFrame
    ofMesh meshOutline;//cFrame
    float elapsedTime;
    
    //rectFrame
    ofMesh polyLine;
    float lineWidth = 2;
    ofxMeshFont2D gui_id,gui_adrs;
    vector<ofxMeshFont2D> fonts;
    
};