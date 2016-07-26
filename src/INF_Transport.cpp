//
//  INF_Transport.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 26/07/2016.
//
//

#include "INF_Transport.h"

INF_Transport::INF_Transport(){
    
}
//--------------------------------------------------------------
INF_Transport::~INF_Transport(){
    
}//--------------------------------------------------------------
void INF_Transport::setup(){
    
    shared_ptr<ofxDatGuiLabel> label = shared_ptr<ofxDatGuiLabel>(new ofxDatGuiLabel("foo"));
    label->setPosition(pos.x, pos.y);
    components.push_back(label);
    
}
//--------------------------------------------------------------
void INF_Transport::update(){
    for(auto &x:components){
        x->setWidth(width / components.size(), 0);
        x->update();
    }
    
}
//--------------------------------------------------------------
void INF_Transport::draw(){
    for(auto &x:components)
        x->draw();
}
//--------------------------------------------------------------