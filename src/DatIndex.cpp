//
//  DatIndex.cpp
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#include "DatIndex.h"
DatIndex::DatIndex():size(30), buttonIndex(1), pos(ofPoint(0,0)), gap(30), width(0){
    //constructor
    width = pos.x + gap;
    //the first page
    DatButton *db;
    db = new DatButton(ofPoint(width+gap*buttonIndex,pos.y), buttonIndex);
    buttons.push_back(db);
    ofAddListener(db->moduleCall, this, &DatIndex::pageCalled);
}
//--------------------------------------------------------------
DatIndex::DatIndex(int x, int y):size(30), buttonIndex(1), pos(ofPoint(x,y)), gap(30){
    width = pos.x + gap;
    DatButton *db;
    db = new DatButton(ofPoint(width+gap*buttonIndex,pos.y), buttonIndex);
    buttons.push_back(db);
    ofAddListener(db->moduleCall, this, &DatIndex::pageCalled);
}
//--------------------------------------------------------------
void DatIndex::setup(){
    //PAGE Controls
    ofxDatGuiButton *b;
    b = new ofxDatGuiButton("+");
    b->setStripe(ofColor(68,0,255), 2);
    b->setPosition(pos.x,pos.y);
    b->onButtonEvent(this, &DatIndex::onButtonEvent);
    b->setWidth(gap);
    size += gap;
        control.push_back(b);
    
    b =new ofxDatGuiButton("-");
    b->setStripe(ofColor(0,255,46), 2);
    b->setPosition(pos.x+gap,pos.y);
    b->onButtonEvent(this, &DatIndex::onButtonEvent);
    b->setWidth(gap);
    size += gap;
        control.push_back(b);
}
//--------------------------------------------------------------
void DatIndex::update(){
    if(!buttons.empty())
        for(auto &b:buttons)b->update();
    for(auto &c:control)c->update();//CONTROLLER UPDATE
}
//--------------------------------------------------------------
void DatIndex::render(){
    if(!buttons.empty())
        for(auto &b:buttons)b->render();
    
    for(auto &c:control)c->draw();//CONTROLLER RENDERING
}
//--------------------------------------------------------------
void DatIndex::onButtonEvent(ofxDatGuiButtonEvent e){
    string target;
    target = e.target->getLabel();
    ofLogNotice()<<target<<endl;
    ofNotifyEvent(moduleAdded, target, this);
    if(e.target->is("+")){
        if(buttonIndex < 8){

            buttonIndex ++;
            DatButton *db;
            db = new DatButton(ofPoint(width+gap*buttonIndex,0), buttonIndex);
            size += gap;
            ofAddListener(db->moduleCall, this, &DatIndex::pageCalled);
            buttons.push_back(db);
            bAdded = true;
        }
        
    }else if(e.target->is("-")){
        if(buttons.size() > 1 ){
            buttonIndex --;
            buttons.pop_back();
            size -= gap;
            ofRemoveListener(buttons[buttonIndex]->moduleCall, this, &DatIndex::pageCalled);
            delete buttons[buttonIndex];
            bAdded = false;
        }else{
            
        }
    }
    
}
//--------------------------------------------------------------
void DatIndex::pageCalled(int &eventArgs){
    ofLogNotice()<<"Page "<<eventArgs<<" is called"<<endl;
    ofNotifyEvent(pageChanged, eventArgs, this);
}
//--------------------------------------------------------------

