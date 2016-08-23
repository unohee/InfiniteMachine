//
//  DatButton.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 23/08/2016.
//
//

#include "DatButton.h"

DatButton::DatButton(ofPoint p, int _ind):pos(p), index(_ind){
    b = new ofxDatGuiButton(to_string(index));
    b->setStripe(ofColor(0), 0);
    b->setPosition(pos.x, pos.y);
    b->onButtonEvent(this, &DatButton::onButtonEvent);
    b->setWidth(30);
}
//--------------------------------------------------------------
DatButton::~DatButton(){
    if(b !=NULL)
        delete b;
}
//--------------------------------------------------------------
void DatButton::update(){
    b->update();
}
//--------------------------------------------------------------
void DatButton::render(){
    b->draw();
}
//--------------------------------------------------------------
void DatButton::onButtonEvent(ofxDatGuiButtonEvent e){
    if (e.target == b){
        call_this = true;
        int index_this = index - 1;
        ofNotifyEvent(moduleCall, index_this, this);
    }else{
        call_this = false;
    }
}
//--------------------------------------------------------------
ofPoint DatButton::getPos(){
    ofPoint p_this(b->getX(), b->getY());
    return p_this;
}
//--------------------------------------------------------------