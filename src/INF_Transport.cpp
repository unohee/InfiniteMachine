//
//  INF_Transport.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 26/07/2016.
//
//

#include "INF_Transport.h"

INF_Transport::INF_Transport(){
    width=  200;
}
//--------------------------------------------------------------
INF_Transport::~INF_Transport(){
    
}//--------------------------------------------------------------
void INF_Transport::setup(){
    
    shared_ptr<ofxDatGuiLabel> label = shared_ptr<ofxDatGuiLabel>(new ofxDatGuiLabel("4/4"));
    label->setPosition(pos.x, pos.y);
    label->setWidth(200);
    components.push_back(label);

    
    pos.x += label->getWidth();
    shared_ptr<ofxDatGuiToggle> start = shared_ptr<ofxDatGuiToggle>(new ofxDatGuiToggle("Play", bStart));
    start->setPosition(pos.x, pos.y);
    start->setWidth(width);
    components.push_back(start);

    
}
//--------------------------------------------------------------
void INF_Transport::update(){
    for(auto &x:components){
//        x->setWidth(width / components.size(), 100);
        x->update();
    }
    
}
//--------------------------------------------------------------
void INF_Transport::draw(){
    for(auto &x:components)
        x->draw();
}
//--------------------------------------------------------------