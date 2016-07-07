//
//  RoundedButton.cpp
//  CircleTest
//
//  Created by Heewon Oh on 07/07/2016.
//
//

#include "RoundedButton.h"

//ROUNDEDBUTTON
RoundedButton::RoundedButton():width(100), height(30),roundness(20), fontSize(16), label(""){
    font.load("Verdana.ttf", fontSize);
}
//--------------------------------------------------------------
RoundedButton::~RoundedButton(){
    ofUnregisterMouseEvents(this);
}
//--------------------------------------------------------------
void RoundedButton::set(ofPoint &p){
    ofRegisterMouseEvents(this);
    this->pos.x = p.x;
    this->pos.y = p.y;
    
    pos = p;
    buttonShape.rectRounded(pos, width, height, roundness, roundness, roundness, roundness);
}
//--------------------------------------------------------------
void RoundedButton::setFontSize(int size){
    fontSize = size;
    font.load("verdana.ttf", fontSize);
}
//--------------------------------------------------------------
void RoundedButton::setLabel(string _label){
    if(font.isLoaded()){
        label = _label;
        width = font.stringWidth(label)+30;
        height = font.stringHeight(label)+14;
    }
}
//--------------------------------------------------------------
void RoundedButton::setColor(ofColor panel, ofColor text){
    buttonShape.setColor(panel);
    textColor = text;
}
//--------------------------------------------------------------
void RoundedButton::draw(){
    if(!font.isAntiAliased());
    ofEnableSmoothing();
    buttonShape.draw();
    ofPushStyle();
    ofSetColor(textColor);
    font.drawStringCentered(label, pos.x+width/2, pos.y+height/2);
    ofPopStyle();
}
void RoundedButton::mouseReleased(ofMouseEventArgs & args){
    if(inside(args.x, args.y)){
        bClicked = true;
        ButtonEvent b;
        b.label = label;
        b.bClicked = bClicked;
        ofNotifyEvent(onButtonEvent, b, this);
    }else{
        bClicked = false;
    }
};
//--------------------------------------------------------------
bool RoundedButton::inside(float x, float y){
    if (x >= pos.x && x <= pos.x+width &&
        y >= pos.y && y <= pos.y+height) {
        return true;
    } else {
        return false;
    }
}
