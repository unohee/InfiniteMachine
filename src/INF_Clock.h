#pragma once
#include "ofxMaxim.h"
#include "ofMain.h"


struct ClockOut{
    
    int playHead, index;
    
    ClockOut():playHead(0), index(0){
        
    };
    ~ClockOut(){
        
    };
};

class INF_Clock{
public:
    //    ofEvent<int>individualPlayHead;
    ofEvent<ClockOut>individualPlayHead;
    ClockOut output;
    
    maxiOsc clock;
    
    int index, tempo, ticksPerBeat;
    
    INF_Clock();
    ~INF_Clock();
    void setTempo(int bpm);
    void setTicks(int tick);
    void ticker();
    int getPlayHead();
    
    int currentCount, lastCount;
    int playHead;
    float bps;
    
};
