
#pragma once
#include "ofxOsc.h"

#define PORT 8080
#define NUM_MSG_STRINGS 20

struct Ableton{
public:
    //Parameters that is received from Ableton Live
    int tempo, bar, beat;
    bool isPlay;
    Ableton(){};
};

class OSC_Receive{
public:
    
    OSC_Receive(){};
    ~OSC_Receive(){};
    void setup();
    void update();
    
    ofxOscReceiver receiver;
    ofEvent<Ableton> AbletonPlayed;
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
};

class OSC_Sender{
public:
    
    OSC_Sender(){};
    
};