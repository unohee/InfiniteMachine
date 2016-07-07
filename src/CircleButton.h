
#pragma once
#include "ofMain.h"

struct ButtonEvent{
public:
    int index;
    string label;
    bool bClicked;
    ButtonEvent():index(0),bClicked(false){};
};


class CircleButton{
public:
    
    ofPath c;
    ofPath inner;
    int posX,posY, lineWidth, index;
    int width, height;
    float radius;
    bool bFill, bClicked, bMouseRegistered;
    string label;
    
    
    //Event
    ofEvent<bool>buttonClicked;
    ofEvent<ButtonEvent>onCircleEvent;
    ofColor edgeColor;
    ofColor innerColor;
    
    CircleButton();
    ~CircleButton(){
        ofUnregisterMouseEvents(this);
    }
    void setup(int x, int y, float _radius, bool bMouse);
    void draw();
    void setOn(bool &seq){bFill = seq;};
    void setOn(bool on){bFill = on;};
    
    ofPoint getPos(){
        ofPoint p = ofPoint(posX, posY);
        return p;
    }
    
    void getWidth(){return width;}
    void getHeight(){return height;}
    
    bool inside(float _x, float _y);
    void mouseMoved(ofMouseEventArgs & args){};
    void mouseDragged(ofMouseEventArgs & args){};
    void mousePressed(ofMouseEventArgs & args){};
    void mouseReleased(ofMouseEventArgs & args);
    
    void mouseScrolled(ofMouseEventArgs & args){};
    void mouseEntered(ofMouseEventArgs & args){};
    void mouseExited(ofMouseEventArgs & args){};
    
    
    
};