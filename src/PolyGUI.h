#pragma once

#include "ofMain.h"
#include "ofxMeshFont2D.h"
#include "INF_Utils.h"
#include "Bjorklund.h"

#include <iostream>
#include <stdexcept>


struct Step{
public:
    
    bool on;
    int accent;
    int note;
    ofPoint pos;

    bool isFloat;
    float radius;
    
    Step():on(false){};
    Step(ofPoint _pos, bool _on):pos(_pos),on(_on), accent(0)
    {
        //constructor
        
    };
    ~Step()
    {
        //destructor
        
        
    };
    void mouseOver(bool &mouseClicked){
        float disX = pos.x - ofGetMouseX();
        float disY = pos.y - ofGetMouseY();
        (sqrt(pow(disX, 2) + pow(disY,2)) < radius * 2 ) ? isFloat = 1 : isFloat = 0;
    }
    void render(){
        (on) ? ofFill() : ofNoFill();
        ofDrawCircle(pos.x, pos.y, radius);
    }


};

struct Seq_Loop{
public:
    
    vector<Step>step_Arr;
    vector<ofPoint> pos;
    
    int stepAmount;
    int pulses;
    float radius;
    
    Seq_Loop(int seq_len):stepAmount(seq_len){
        
        //create a group of empty steps
        if(!step_Arr.empty())
            step_Arr.clear();
        float angle = 360 / stepAmount;
        
        for(int i = 0; i < stepAmount; i++){
            pos.insert(pos.begin()+i, ofPoint(radius * cos(angle*i*PI/180), radius * sin(angle*i*PI/180)));
            
            Step temp = Step(pos[i],0);
            temp.radius = 15;
            step_Arr.insert(step_Arr.begin()+i, temp);
        }
    };
    
    Seq_Loop(int seq_len, int seq_pulse):stepAmount(seq_len), pulses(seq_pulse){
        
        //create a Bjorklund sequence
        if(!step_Arr.empty())
            step_Arr.clear();
        
        //gets all points
        for(int i=0;i < stepAmount;i++){
            
        }
    };
    
    ~Seq_Loop(){
        
    }
    
    void render(){
        for(int i=0;i < stepAmount;i++){
            
        }
    }
};

typedef vector<unique_ptr<Seq_Loop>> seqCollection;

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
        try{
            if(!step_Arr.empty())
                for_each(step_Arr.begin(), step_Arr.end(), DeleteVector<Step*>()); //flush all pointers in vectors
        }catch(exception e){
            cout<<e.what()<<endl;
        }
        
        cout<<"[PolyGUI is deleted]"<<endl;
    }
    
    void mouseOver();
    void createPoly(int seq_len);
    void createPoly(vector<bool> &seq);
    vector<bool>seq_Return();
    void createMesh();
    void draw();
    
    vector<ofVec3f>steps;
    vector<bool>isOn;
    vector<Step*> step_Arr;
    
    
    
    float width, height;
    float radius;
    ofMatrix4x4 m;
    ofVec3f pos;
    
    bool euclid;
    bool isFloat;
    
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