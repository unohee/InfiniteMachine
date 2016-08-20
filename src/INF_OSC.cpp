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

        if(m.getAddress()== "/transport/tempo"){
            tempo = m.getArgAsFloat(0);
            ofNotifyEvent(tempoChange, tempo, this);
        }else if(m.getAddress()== "/transport/currentBar"){
            state.bar = m.getArgAsInt(0);
            ofNotifyEvent(AbletonState, state, this);
        }else if(m.getAddress()== "/transport/currentBeat"){
            state.beat = m.getArgAsInt(0);
            ofNotifyEvent(AbletonState, state, this);
        }
        
        if(m.getAddress()== "/state/play"){
            bool state;
            state = m.getArgAsBool(0);
            if(state)
                ofLogNotice()<<"Ableton Played"<<endl;
            else
                ofLogNotice()<<"Ableton Stopped"<<endl;
            ofNotifyEvent(onAbletonStart, state, this);
        }
        
        if(m.getAddress()== "/meter/beatPerBar"){
            ofLogNotice()<<"Meter Changed"<<endl;
            cMeter.beats = (int)m.getArgAsFloat(0);
            ofNotifyEvent(onMeterChange, cMeter, this);
        }else if(m.getAddress()== "/meter/beatResolution"){
            cMeter.beatResolution = (int)m.getArgAsFloat(0);
            ofNotifyEvent(onMeterChange, cMeter, this);
        }
        
    }
}
//--------------------------------------------------------------