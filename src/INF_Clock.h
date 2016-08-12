#pragma once
#include "ofxMaxim.h"
#include "ofMain.h"

class INF_Clock{
public:
    
    unique_ptr<maxiOsc> clock;
    ofEvent<int>clockTicks;
    
    
    INF_Clock();
    ~INF_Clock();
    void setTempo(int bpm);
    void setTicks(int tick);
    void ticker();
    int getPlayHead();

private:
    int currentCount, lastCount;
    int playHead, ticksPerBeat;
    float bps;
    
};
