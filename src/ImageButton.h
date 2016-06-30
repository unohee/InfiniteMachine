//
//  ImageButton.hpp
//  GuiTest
//
//  Created by Heewon Oh on 29/06/2016.
//
//

#ifndef ImageButton_h
#define ImageButton_h

#include "ofMain.h"

struct customEvent{
    
    string label;
    bool toggle;
};

class ImageButton{
public:
    ofEvent<customEvent>buttonClicked;
    ofEvent<bool>clickedInside;

    int size;
    bool isClicked;
    string label;
    ofPoint pos;
    ofImage img;
    
    ImageButton(string path, string _label);
    ~ImageButton(){
        ofUnregisterMouseEvents(this); // disable listening to mouse events.
    };
    
    
    void setPosition(int x, int y);
    void setSize(int size);
    int getWidth(){return size;};
    int getHeight(){return size;};
    void render();
    bool inside(float _x, float _y );
    
    
    void mouseMoved(ofMouseEventArgs & args){};
    void mouseDragged(ofMouseEventArgs & args){};
    void mousePressed(ofMouseEventArgs & args){};
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args){};
    void mouseEntered(ofMouseEventArgs & args){};
    void mouseExited(ofMouseEventArgs & args){};
    
};


#endif /* ImageButton_hpp */
