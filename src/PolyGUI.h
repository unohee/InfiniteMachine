#pragma once

#include "ofMain.h"
#include "ofxMeshFont2D.h"
#include "INF_Utils.h"

#include <iostream>
#include <stdexcept>


struct Step{
public:
    
    int *accent;
    float radius;
    ofPoint pos;
    bool isFloat;
    bool on;
    
    Step(ofPoint p, bool _on):pos(p), on(_on), radius(15), accent(0)
    {
        //constructor
        
    };
    ~Step()
    {
        //destructor
        if(accent != NULL)
            delete accent;
    };
    bool mouseOver(){
        float disX = pos.x - ofGetMouseX();
        float disY = pos.y - ofGetMouseY();
        (sqrt(pow(disX, 2) + pow(disY,2)) < radius * 2 ) ? isFloat = 1 : isFloat = 0;
    }
    void render(){
        ofSetColor(ofColor::red);
        (on) ? ofFill() : ofNoFill();
        ofDrawCircle(pos.x, pos.y , radius);
    }

};

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
        if(!step_Arr.empty())
            for_each(step_Arr.begin(), step_Arr.end(), DeleteVector<Step*>()); //flush all pointers in vectors
        cout<<"[PolyGUI is deleted]"<<endl;
    }
    
    void mouseOver();
    void setOSC(string HOST, int PORT){
        address = HOST;
    };
    void createPoly(vector<bool> &seq);
    void vertAdd(vector<ofVec3f>&v);
    void createMesh();
    void draw();
    
    vector<ofVec3f>steps;
    vector<Step*> step_Arr;
    
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