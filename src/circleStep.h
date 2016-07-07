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

struct SequenceEvent{
    //Custom ofEvent
    vector<bool>seq;
    int index;
    
    SequenceEvent(){
        
    };
};

class circleStep{
public:
    
    ofEvent<SequenceEvent>sequenceUpdate;
    //ofPath
    ofPoint pos;
    ofPath circle;
    ofPath inner;
    int x,y, lineWidth;
    int index;
    float radius;
    
    //Sequence
    int stepAmt;
    vector<shared_ptr<CircleButton>>steps;
    vector<shared_ptr<ofPoint>>stepPos;
    
    vector<bool>step_seq;
    bool bEuclid;
    
    circleStep(ofPoint p, float radius);
    ~circleStep(){
        steps.clear();
        stepPos.clear();
        step_seq.clear();
        cout<<"[Cyclic Sequence "<<index<<" Deleted]"<<endl;
    };
    void setup();
    void setMode(SEQUENCER_MODE mode);
    void draw();
    void stepClicked(ButtonEvent &e);
    void setLength(int seq_len){
        
    };
    void setPulse(int seq_pulse){
        //now complicated things happen here..
    }
    void setSequence(vector<bool> &v){
        step_seq.clear();
        for(int i=0; i < v.size();i++){
            step_seq.insert(step_seq.begin()+i, v[i]);
        }
        setup();
    };
    vector<bool> getSequence(){return step_seq;};
    int getSize(){return step_seq.size();}
    
};

#endif /* circleStep_h */
