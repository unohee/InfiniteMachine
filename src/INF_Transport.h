//
//  INF_Transport.h
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 26/07/2016.
//
//

#ifndef INF_Transport_h
#define INF_Transport_h

#include "ofxDatGui.h"
#include "ofxMaxim.h"
#include "ofMain.h"

typedef shared_ptr<ofxDatGuiComponent> DatGuiPtr;


struct TransportMessage{
    float BPM;
    bool mode;
    string timeSignature;
};

class INF_Transport{
public:
    
    unique_ptr<ofxDatGuiTextInput> text;
    unique_ptr<ofxDatGuiSlider> tempoSlider;
    vector<DatGuiPtr> components;
    ofPoint pos;
    
    ofEvent<TransportMessage> ClockCallback;
    TransportMessage currentState;
    
    int width;
    float tempoVal;
    bool bStart, bFreeze;
    INF_Transport();
    ~INF_Transport();

    void setup();
    void update();
    void draw();
    void setMode(bool isSlave);
    void setTimeSignature(int beat, int amount);
    float ClockSync();
    string meter;
    
    void onTextInput(ofxDatGuiTextInputEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
};

#endif /* INF_Transport_h */
