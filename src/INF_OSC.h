
#pragma once
#include "ofxOsc.h"
#include "Meter.h"

#define PORT 8080
#define NUM_MSG_STRINGS 20

struct Ableton{
public:
    //Parameters that is received from Ableton Live
    int bar, beat;
    Ableton(){};
};

class OSC_Receive{
public:
    
    OSC_Receive(){};
    ~OSC_Receive(){};
    void setup();
    void update();
    
    ofxOscReceiver receiver;
    ofEvent<Ableton> AbletonState;
    ofEvent<int>tempoChange;
    ofEvent<bool> onAbletonStart;
    ofEvent<currentMeter> onMeterChange;
    
    Ableton state;
    currentMeter cMeter;
    int tempo;
    
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
};

class OSC_Sender{
public:
    
    OSC_Sender(){};
    
};