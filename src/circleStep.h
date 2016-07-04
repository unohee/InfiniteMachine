//
//  circleStep.h
//  CircleTest
//
//  Created by Heewon Oh on 01/07/2016.
//
//

#ifndef circleStep_h
#define circleStep_h

#include "CircleButton.h"
#include "INF_Utils.h"
enum SEQUENCER_MODE {MANUAL, EUCLID};

struct Sequence{
    //Custom ofEvent
    vector<bool>seq;
    int index;
    Sequence(){
        
    };
};

class circleStep{
public:
    
    ofEvent<Sequence>sequenceUpdate;
    //ofPath
    ofPoint pos;
    ofPath circle;
    ofPath inner;
    int x,y, lineWidth;
    int index;
    float radius;
    
    //Sequence
    int stepAmt;
    vector<CircleButton*> steps;
    vector<ofPoint>stepPos;
    
    vector<bool>step_seq;
    bool bEuclid;
    
    circleStep(ofPoint p, float radius);
    ~circleStep(){
        
    };
    void setup();
    void setMode(SEQUENCER_MODE mode);
    void update();
    void draw();
    void stepClicked(CircleEvent &e);
    
    
    void setLength(int seq_len){

    };
    void setPulse(int seq_pulse){
        //now complicated things happen here..
    }
    void setSequence(vector<bool> &v){
        setup();
        for(int i=0; i < v.size();i++){
            step_seq.insert(step_seq.begin()+i, v[i]);
        }
    };
    vector<bool> getSequence(){return step_seq;};
    int getSize(){return step_seq.size();}
    
    
    
    
};

#endif /* circleStep_h */
