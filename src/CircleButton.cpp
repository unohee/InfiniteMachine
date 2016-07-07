//
//  CircleButton.cpp
//  CircleTest
//
//  Created by Heewon Oh on 01/07/2016.
//
//

#include "CircleButton.h"

CircleButton::CircleButton():bFill(false), bClicked(false){
    innerColor = 0;
};
//--------------------------------------------------------------
void CircleButton::setup(int x, int y, float _radius, bool bMouse){
    bMouseRegistered = bMouse;
    if(bMouseRegistered){
        ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
    }else{
        ofUnregisterMouseEvents(this);
    }
    
    this->posX = x;
    this->posY = y;
    this->radius = _radius;
    width = radius * 2;
    height = width;
    
    //inner circle
    inner.setCircleResolution(100);
    inner.circle(posX,posY, radius-lineWidth);
    //outer line
    c.setCircleResolution(100);
    c.arc(posX, posY, radius, radius, 0, 360);
    c.arc(posX,posY,radius - lineWidth,radius - lineWidth, 0,360);
    c.setColor(edgeColor);
    label = to_string(index);
};
//--------------------------------------------------------------
void CircleButton::draw(){
    
    if(bFill)
        inner.setColor(edgeColor);
    else
        inner.setColor(innerColor);
    
    inner.draw();
    c.draw();
}
//--------------------------------------------------------------
void CircleButton::mouseReleased(ofMouseEventArgs & args){
    if(inside(args.x, args.y)){
        bClicked = !bClicked;
        bFill = !bFill;
        
        ButtonEvent b;
        b.index = index;
        b.bClicked = bClicked;
        if(bMouseRegistered)
            ofNotifyEvent(onCircleEvent, b, this);
    }
};
//--------------------------------------------------------------
bool CircleButton::inside(float _x, float _y ){
    return (ofVec2f(_x, _y).distance(ofVec2f(posX, posY)) <radius);
}
//--------------------------------------------------------------