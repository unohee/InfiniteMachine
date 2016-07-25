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
    bool bEuclid;
    
    ofEvent<SequenceEvent>stepUpdated;
    
    //Sequence
    int stepAmt;
    vector<shared_ptr<CircleButton>>steps;
    vector<shared_ptr<ofPoint>>stepPos;
    vector<bool>stepState;
    
    circleStep(ofPoint p, float radius);
    ~circleStep(){
        steps.clear();
        stepPos.clear();
        //cout<<"[Cyclic Sequence "<<index<<" Deleted]"<<endl;
    };
    void setup();
    void setMode(SEQUENCER_MODE mode);
    void draw();
    void print();
    void stepClicked(ButtonEvent &e);
    void setSequence(vector<bool> &v);
};


#endif /* circleStep_h */
