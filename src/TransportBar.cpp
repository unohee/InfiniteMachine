//
//  TransportBar.cpp
//  InfinityMachine-ALPHA
//
//  Created by Heewon Oh on 4/24/16.
//
//

#include "TransportBar.h"

//--------------------------------------------------------------
void TransportBar::setup(){

    //ofxDatGui Setup
    //Framerate
    ofxDatGuiComponent* component;
    component = new ofxDatGuiFRM(0.01f);//instantiate FRM object and set refreshrate
    components.push_back(component);
    
    //TEXTINPUT (IP + PORT)
    component = new ofxDatGuiTextInput("IP Address", netAddress);
    component->onTextInputEvent(this, &TransportBar::setNetwork);
    components.push_back(component);
    //BPM SLIDER
    ofxDatGuiSlider* bpmSlider = new ofxDatGuiSlider("BPM", 20, 240);
    bpmSlider->setPrecision(0);
    bpmSlider->setValue(130);
    bpmSlider->onSliderEvent(this, &TransportBar::bpmChanged); //add event method
    components.push_back(bpmSlider);
    
    //PLAY / Stop Toggle
    ofxDatGuiToggle* play = new ofxDatGuiToggle("PLAY", start);
    
    play->onButtonEvent(this, &TransportBar::setPlayback);
    components.push_back(play);
}
//--------------------------------------------------------------
void TransportBar::update(float windowWidth){
    //flexible position of dock
    float gap = windowWidth / components.size();
    for(int i=0;i < components.size();++i){
        if(i <= 2){
            components[i]->setWidth(gap, 0.45);
        }else{
            components[i]->setWidth(gap, 0.2);
        }
        components[i]->setPosition(gap*i, ofGetHeight() - components[i]->getHeight());
    }
    for(auto components:components) components->update();
}
//--------------------------------------------------------------
void TransportBar::draw(){
    for(auto components:components) components->draw();
    
}