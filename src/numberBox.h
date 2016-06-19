//
//  numberBox.h
//  Infinite_Machine_Alpha
//
//  Created by UNO H on 19/06/2016.
//
//

#ifndef numberBox_h
#define numberBox_h

#include "ofMain.h"

class numberBox{
    
    numberBox(ofPoint p):pos(p){
        
    }
    ~numberBox(){
        
    }
    void render(){
        ofDrawRectangle(pos.x,pos.y, 15,15);
    };
    int index;
    char id;
    ofPoint pos;
    
};
#endif /* numberBox_h */
