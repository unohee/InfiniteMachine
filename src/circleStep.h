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
    
    //ofPath
    ofPoint pos;
    ofPath circle;
    ofPath inner;
    ofColor c;
    int x,y, lineWidth;
    int index;
    float radius;
    
    //Sequence
    int stepAmt;
    vector<shared_ptr<CircleButton>>steps;
    vector<shared_ptr<ofPoint>>stepPos;
    
    vector<bool>step_seq;
//    unique_ptr<Sequence> track;
    
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
    void setSequence(vector<bool> &v){
        for(int i=0; i < v.size();i++){
            steps[i]->setOn(v.at(i));
        }
        setup();
        /*
        track->pattern.clear();
        for(int i=0; i < v.size();i++){
            track->pattern.insert(track->pattern.begin()+i, v[i]);
        }
        setup();
         */
    };
};


#endif /* circleStep_h */
