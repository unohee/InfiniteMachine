//
//  INF_Transport.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 26/07/2016.
//
//

#include "INF_Transport.h"

INF_Transport::INF_Transport():tempo(120), beatResolution(4),ticksPerBeat(4){
    cMeter.beatResolution = beatResolution;
    cMeter.beats = ticksPerBeat;
}
//--------------------------------------------------------------
INF_Transport::~INF_Transport(){
    text.reset();
    tempoSlider.reset();
    start.reset();
}//--------------------------------------------------------------
void INF_Transport::setup(){
    
    text = unique_ptr<ofxDatGuiTextInput>(new ofxDatGuiTextInput("Time", meter));
    text->setPosition(pos.x, pos.y);
    text->setWidth(200, 50);
    text->setText("4/4");
    text->onTextInputEvent(this, &INF_Transport::onTextInput);
    
    //BPM SLIDER
    pos.x += text->getWidth();
    tempo.set("BPM", 120, 40, 200); //init ofParameter
    tempoSlider = unique_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider(tempo));
    tempoSlider->setPosition(pos.x, pos.y);
    tempoSlider->setWidth(200, 50);
    tempoSlider->setPrecision(0);
    tempoSlider->setValue(120);
    tempoSlider->onSliderEvent(this, &INF_Transport::onSliderEvent);
    pos.x += tempoSlider->getWidth();
    
    start = unique_ptr<ofxDatGuiToggle>(new ofxDatGuiToggle("Play", bStart));
    start->setPosition(pos.x, pos.y);
    start->setWidth(200);
    start->onToggleEvent(this, &INF_Transport::onToggleEvent);
    
    pos.x += start->getWidth();
    status = unique_ptr<ofxDatGuiLabel>(new ofxDatGuiLabel("Status:"));
    status->setPosition(pos.x, pos.y);
    status->setWidth(540);
    status->setOpacity(80);
}
//--------------------------------------------------------------
void INF_Transport::update(){
    text->update();
    tempoSlider->update();
    start->update();
    status->update();
}
//--------------------------------------------------------------
void INF_Transport::draw(){
    text->draw();
    tempoSlider->draw();
    start->draw();
    status->draw();
}
//--------------------------------------------------------------
void INF_Transport::setTimeSignature(int beat, int amount){
    meter = to_string(amount) + "/" + to_string(beat);
    text->setText(meter);
    cMeter.beatResolution = beat;
    cMeter.beats = amount;
    ofNotifyEvent(MeterChanged, cMeter, this);
}
//--------------------------------------------------------------
void INF_Transport::onTextInput(ofxDatGuiTextInputEvent e){
    currentMeter c;
    //parsing strings
    meter = e.text;
    string s;
    s = "/";
    vector<string> v = ofSplitString(meter, s);
    cout<<v[0]<<"/"<<v[1]<<endl;
    cMeter.beats = stoi(v[0]);
    cMeter.beatResolution = stoi(v[1]);
    ofNotifyEvent(MeterChanged, cMeter, this);
}
//--------------------------------------------------------------
void INF_Transport::onSliderEvent(ofxDatGuiSliderEvent e){
    int BPM = tempo;
    ofNotifyEvent(tempoChange, BPM, this);
}
//--------------------------------------------------------------
void INF_Transport::onToggleEvent(ofxDatGuiToggleEvent e){
    currentState.play = e.checked;
    ofNotifyEvent(TransportCallback, currentState, this);
}
