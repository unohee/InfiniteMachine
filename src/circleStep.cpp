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
    
    //create unique pointer that stores data of Sequence..
    track = unique_ptr<Sequence>(new Sequence());
    
    for(int i=0; i < stepAmt;i++){
        //allocate memory size first.
        step_seq.push_back(false);
        track ->pattern.push_back(0);
        track ->index = make_unique<int>(index);
    }
    //color of step is randomly chosen.
    int randMin = 20;
    c = ofColor((int)ofRandom(randMin, 255),(int)ofRandom(randMin, 255),(int)ofRandom(randMin, 255));
}
//--------------------------------------------------------------
void circleStep::setup(){
    if(!stepPos.empty())stepPos.clear();
    if(!steps.empty()){steps.clear();}
    
    float angle = 360.f / stepAmt;
//    float angle = 360.f / 16;
    
    //create a set of buttons
    for(int i = 0; i < stepAmt; i++){
        //calculate positions
        shared_ptr<ofPoint>p = shared_ptr<ofPoint>(new ofPoint(pos.x+radius * cos(angle*i*PI/180), pos.y+radius * sin(angle*i*PI/180)));
        stepPos.insert(stepPos.begin()+i, p);
        
        //adding circles into vector
        shared_ptr<CircleButton> step = shared_ptr<CircleButton>(new CircleButton());
        step->index = i;
        step->lineWidth = 2.5;
        step->edgeColor = c;
//        step->setOn(step_seq[i]);
        step->setOn(track->pattern[i]);
        step->setup(stepPos[i]->x, stepPos[i]->y, 12, true);
        steps.insert(steps.begin()+i, std::move(step));
        ofAddListener(steps[i]->onCircleEvent, this, &circleStep::stepClicked);
    }
    cout<<"[Cyclic Sequence "<<index<<" created]"<<endl;
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
    if(step_seq.size() > 0)
        for(int i =0; i < step_seq.size();i++){
//            cout<<step_seq[i];
            cout<<track->pattern[i];
        }
    else
        cout<<"Sequence is empty"<<endl;
}
//--------------------------------------------------------------
void circleStep::stepClicked(ButtonEvent &e){
    step_seq.at(e.index) = e.bClicked; //replace elements by buttons' indices
    
    track->pattern.at(e.index) = e.bClicked;
    cout<<"[Track"<<index<<":";
    print();
    cout<<"]"<<endl;

}
