#pragma once
#include "ofxDatGui.h"
#include "ofxMaxim.h"
#include "ofMain.h"
#include "Meter.h"

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
    
    ofEvent<int>tempoChange;
    ofEvent<TransportMessage> TransportCallback;
    ofEvent<currentMeter> MeterChanged;
    
    TransportMessage currentState;
    currentMeter cMeter;
    maxiOsc clock;
    int ticksPerBeat, beatResolution;
    ofParameter<int> tempo;
    float bps;
    bool bStart, bFreeze;
    INF_Transport();
    ~INF_Transport();

    void setup();
    void update();
    void draw();
    void setTimeSignature(int beat, int amount);
    string meter;
    
    void onTextInput(ofxDatGuiTextInputEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void onToggleEvent(ofxDatGuiToggleEvent e);
};