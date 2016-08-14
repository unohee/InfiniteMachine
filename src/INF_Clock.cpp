//
//  INF_Clock.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 11/08/2016.
//
//

#include "INF_Clock.h"

INF_Clock::INF_Clock():index(0), ticksPerBeat(4), playHead(0){
    
}
INF_Clock::~INF_Clock(){
    
}
void INF_Clock::setTempo(int bpm){
    tempo = bpm;
    bps = (tempo / 60.) * ticksPerBeat;
}
void INF_Clock::setTicks(int tick){
    ticksPerBeat = tick;
    bps = (tempo / 60.) * ticksPerBeat;
}
void INF_Clock::ticker(){
    currentCount=(int)clock.phasor(bps);
    
    if (lastCount!=currentCount){
        output.index = index;
        output.playHead = playHead;
        playHead++;//iterate the playhead
        lastCount=0;//reset the metrotest
        ofNotifyEvent(individualPlayHead, output, this);
    }
}
int INF_Clock::getPlayHead(){
    return playHead;
}