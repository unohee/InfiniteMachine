//
//  Dat_dropdown.h
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#ifndef DatDropdown_h
#define DatDropdown_h

#include "ofxDatGui.h"
#include <vector>

using namespace std;

class DatDropdown{
  
public:
    vector<string>list = {"1", "2", "3", "4"};
    ofxDatGuiDropdown* menus;
    ofPoint pos;
    
    
    DatDropdown():menus(NULL), pos(ofPoint(0,0)){};
    DatDropdown(string label, int x, int y, vector<string>&v):pos(ofPoint(x,y)),list(v){
        //Receives the list from out of class.
        menus = new ofxDatGuiDropdown(label, list);
        menus->setPosition(pos.x, pos.y);
    };
    ~DatDropdown(){
        if(menus != NULL)
            delete menus;
    };
    void setWidth(int width){menus->setWidth(width);};
    int getWidth(){return menus->getWidth();};
    
    void setPosition(ofPoint p){
        menus->setPosition(p.x, p.y);
    }
    void update(){
        menus->update();
    };
    void render(){
        menus->draw();
    };
    
};

#endif /* DatDropdown_h */
