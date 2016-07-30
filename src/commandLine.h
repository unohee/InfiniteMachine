

#pragma once
#include "ofMain.h"

class commandLine{
public:
    
    ofRectangle rect;
    string message;
    
    commandLine();
    ~commandLine();
    
    void update();
    void render();
    
};