//
//  INF_Clock.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 11/08/2016.
//
//

#include "INF_Clock.h"

INF_Clock::INF_Clock():ticksPerBeat(4){
    
}
INF_Clock::~INF_Clock(){
    
}
void INF_Clock::setTempo(int bpm){
    bps = (bpm / 60.) * ticksPerBeat;
}
void INF_Clock::setTicks(int tick){
    ticksPerBeat = tick;
}
void INF_Clock::ticker(){
    currentCount=(int)clock->phasor(bps);
    
    if (lastCount!=currentCount){
        ofNotifyEvent(clockTicks, playHead, this);
        playHead++;//iterate the playhead
        lastCount=0;//reset the metrotest
    }
}
int INF_Clock::getPlayHead(){
    return playHead;
}