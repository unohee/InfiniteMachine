//
//  circleStep.cpp
//  CircleTest
//
//  Created by Heewon Oh on 01/07/2016.
//
//

#include "circleStep.h"

circleStep::circleStep(ofPoint p, float _radius):index(0),pos(p), radius(_radius), stepAmt(16), bEuclid(false){
    circle.setCircleResolution(100);
    circle.arc(pos.x, pos.y, radius, radius, 0, 360);
    circle.arc(pos.x,pos.y,radius - 2.5,radius - 2.5, 0,360);
    circle.setColor(60);
    
    for(int i=0; i < stepAmt; i++)
        stepState.push_back(0);
    
    //color of steps is randomly chosen.
    int randMin = 20;
    c = ofColor((int)ofRandom(randMin, 255),(int)ofRandom(randMin, 255),(int)ofRandom(randMin, 255));
}
//--------------------------------------------------------------
void circleStep::setup(){
    if(!stepPos.empty())stepPos.clear();
    if(!steps.empty()){steps.clear();}
    
    float angle = 360.f / stepAmt;  
    //create a set of buttons
    for(int i = 0; i < stepAmt; i++){
        //calculate positions
        shared_ptr<ofPoint>p = shared_ptr<ofPoint>(new ofPoint(pos.x+radius * cos(angle*i*PI/180), pos.y+radius * sin(angle*i*PI/180)));
        stepPos.insert(stepPos.begin()+i, p);
        
        //adding circles at vectors
        shared_ptr<CircleButton> step = shared_ptr<CircleButton>(new CircleButton());
        step->index = i;
        step->lineWidth = 2.5;
        step->edgeColor = c;
        step->setOn(stepState[i]);
        step->setup(stepPos[i]->x, stepPos[i]->y, 12, true);
        steps.insert(steps.begin()+i, std::move(step));
        ofAddListener(steps[i]->onCircleEvent, this, &circleStep::stepClicked);
    }
    //cout<<"[Cyclic Sequence "<<index<<" created]"<<endl;
}
//--------------------------------------------------------------
void circleStep::setMode(SEQUENCER_MODE mode){
    if(mode == MANUAL){
        bEuclid = false;
    }else if(mode == EUCLID){
        bEuclid = true;
    }
}
//--------------------------------------------------------------
void circleStep::draw(){
    circle.draw();
    //SEQ LINE
    for(auto &x:steps)x->draw();
}
//--------------------------------------------------------------
void circleStep::print(){
    //printout
    cout<<"[Track"<<index<<":";
    for(auto x : stepState)
        cout<<x;
    cout<<"]"<<endl;
}
//--------------------------------------------------------------
void circleStep::stepClicked(ButtonEvent &e){
    stepState.at(e.index) = e.bClicked;
    print();
    
    SequenceEvent seqEvent;
    seqEvent.seq = stepState;
    seqEvent.index = index;
    ofNotifyEvent(stepUpdated, seqEvent, this);
}
//--------------------------------------------------------------
void circleStep::setSequence(vector<bool> &v){
    stepState.clear();
    for(int i=0; i < v.size();i++){
        stepState.insert(stepState.begin()+i, v.at(i));
    }
    setup();
    print();
};
