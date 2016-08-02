#pragma once
#include "ofxDatGui.h"
#include "ofxMaxim.h"
#include "ofMain.h"

struct TransportMessage{
    float BPM;
    bool play;
    string timeSignature;
};

class INF_Transport{
public:
    
    unique_ptr<ofxDatGuiTextInput> text;
    unique_ptr<ofxDatGuiSlider> tempoSlider;
    unique_ptr<ofxDatGuiToggle> start;
    unique_ptr<ofxDatGuiLabel> status;
    ofPoint pos;
    
    ofEvent<TransportMessage> ClockCallback;
    TransportMessage currentState;
    
    maxiOsc clock;
    int width;
    float tempoVal;
    bool bStart, bFreeze;
    INF_Transport();
    ~INF_Transport();

    void setup();
    void update();
    void draw();
    void setTimeSignature(int beat, int amount);
    float getClock();
    float getClock(int ticks);
    string meter;
    
    void onTextInput(ofxDatGuiTextInputEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
};