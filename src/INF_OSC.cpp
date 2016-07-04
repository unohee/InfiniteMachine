//
//  INF_OSC.cpp
//
//  Imported from openFrameworks' OSC Receive Example.
//  Edited by Heewon Oh on 04/07/2016.
//
//

#include "INF_OSC.h"

void OSC_Receive::setup(){
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
}
//--------------------------------------------------------------
void OSC_Receive::update(){
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        Ableton state;
        
        if(m.getAddress()== "/transport/tempo"){
            state.tempo = m.getArgAsFloat(0);
        }else if(m.getAddress()== "/transport/play"){
            state.isPlay = m.getArgAsBool(0);
        }else if(m.getAddress()== "/transport/currentBar"){
            state.bar = m.getArgAsInt(0);
        }else if(m.getAddress()== "/transport/currentBeat"){
            state.bar = m.getArgAsInt(0);
        }else{
            //do nothing
        }
        ofNotifyEvent(AbletonPlayed, state, this);
    }
}
//--------------------------------------------------------------