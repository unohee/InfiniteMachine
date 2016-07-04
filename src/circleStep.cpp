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
    for(int i=0; i < stepAmt;i++)
        step_seq.push_back(false);
}
//--------------------------------------------------------------
void circleStep::setup(){
    if(!stepPos.empty())stepPos.clear();
    if(!steps.empty()){//delete pointers(if it is not NULL)
        for_each(steps.begin(), steps.end(), DeleteVector<CircleButton*>());
        steps.clear();
    }
    
    float angle = 360.f / stepAmt;
    int randMin = 20;
    ofColor c = ofColor((int)ofRandom(randMin, 255),(int)ofRandom(randMin, 255),(int)ofRandom(randMin, 255));
    
    for(int i = 0; i < stepAmt; i++){
        stepPos.insert(stepPos.begin()+i,
                       ofPoint(pos.x+radius * cos(angle*i*PI/180), pos.y+radius * sin(angle*i*PI/180)));
    }
    
    for(int i=0; i <stepPos.size();i++){
        CircleButton *step = new CircleButton();
        step->index = i;
        step->lineWidth = 2.5;
        step->edgeColor = c;
        step->setup(stepPos[i].x, stepPos[i].y, 10, true);
        steps.push_back(step);
        ofAddListener(step->onCircleEvent, this, &circleStep::stepClicked);
    }
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
void circleStep::update(){
    
}
//--------------------------------------------------------------
void circleStep::draw(){
    circle.draw();
    //SEQ LINE
    for(auto x:steps)x->draw();
}
//--------------------------------------------------------------
void circleStep::stepClicked(CircleEvent &e){
    step_seq.at(e.index) = e.bClicked; //replace elements by button indices
    
    Sequence newSeq;
    newSeq.seq = step_seq;
    newSeq.index = index;
    ofNotifyEvent(sequenceUpdate, newSeq, this);
}
