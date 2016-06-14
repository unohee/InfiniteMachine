//
//  Panel.h
//  Infinite_Machine-master
//
//  Created by Heewon Oh on 4/4/16.
//
//

#pragma once
#include "ofMain.h"
#include "ofxMeshFont2D.h"

class Panel :public ofNode{
public:
    
    Panel(){
        
    };
    ~Panel(){
        
    };
    float width, height;
    float radius;
    ofMatrix4x4 m;
    ofVec3f pos;
    ofVec2f pos2d;

};
