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
#include "ofxMeshFont2D.h"

class numberBox{
    
    int *index;
    int width, height;
    char *nb_index;
    ofPoint pos;
    ofxMeshFont2D number;
    bool clicked;
    
    
    numberBox(ofPoint p):pos(p) index(0){
        number = ofxMeshFont2D("/Users/uno/Developer/of_v20160609_osx_release/apps/myApps/Infinite_Machine_Alpha/bin/data/ofxbraitsch/fonts/Verdana.ttf",8);
    }
    ~numberBox(){
        try {
            if(index != NULL)
                delete index;
            if(nb_index != NULL)
                delete nb_index
        } catch (exception e) {
            cout<<"[Numberbox :"<<e.what()<<"]"<<endl;
        }
        
    }
    void render(){
        ofDrawRectangle(pos.x,pos.y, 15,15);
    };
    int getIndex(){return index;};

    
};
#endif /* numberBox_h */
