//
//  DatBox.h
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#ifndef DatBox_h
#define DatBox_h

#include "ofxDatGui.h"

class DatButton{
    
public:
    ofPoint pos;
    float size;
    int index;
    ofxDatGuiButton *b;
    ofEvent<int> moduleCall;
    bool call_this;

    DatButton(){};
    //note that I changed fontsize in ofxDatGuiTheme.h
    DatButton(ofPoint p, int _ind);
    ~DatButton();
    void update();
    void render();
    void onButtonEvent(ofxDatGuiButtonEvent e);
    ofPoint getPos();
    float getWidth(){return 30;}
    int getIndex(){return index;};
    
};

#endif /* DatBox_h */
