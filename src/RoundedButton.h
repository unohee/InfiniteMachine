#pragma once
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include "CircleButton.h"

class RoundedButton{
public:
    
    ofEvent<ButtonEvent>onButtonEvent;
    
    ofPath buttonShape;
    ofxCenteredTrueTypeFont font;
    string label;
    ofVec2f pos;
    ofColor textColor;
    bool bClicked;
    int width, height, fontSize;
    float roundness;
    
    
    RoundedButton();
    ~RoundedButton();
    void set (ofPoint &p);
    void setFontSize(int size);
    void setLabel(string _label);
    void setColor(ofColor panel, ofColor text);
    void draw();
    bool inside(float x, float y);
    float getWidth(){return width;};
    
    
    
    void mouseMoved(ofMouseEventArgs & args){};
    void mouseDragged(ofMouseEventArgs & args){};
    void mousePressed(ofMouseEventArgs & args){};
    void mouseReleased(ofMouseEventArgs & args);
    
    void mouseScrolled(ofMouseEventArgs & args){};
    void mouseEntered(ofMouseEventArgs & args){};
    void mouseExited(ofMouseEventArgs & args){};
};