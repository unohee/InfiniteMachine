//
//  INF_Clock.h
//  Infinite_Machine_Alpha
//
//  Created by UNO H on 17/06/2016.
//
//

#ifndef INF_Clock_h
#define INF_Clock_h

#include "ofxMaxim.h"

class INF_Clock{
public:
    
    //play method
    maxiOsc counter; //Phasor object
    double bps;
    
    int currentCount;
    int lastCount, playHead;
    
    int tempo;
    
    INF_Clock():tempo(120){
        setTempo(tempo);
    }
    void setTempo(int BPM){
        bps = BPM / 60.f * pow(2, 4);
    };
    
    void ticker(bool isPlay){
        //clock ticks here..
        currentCount=floor(counter.phasor(bps));//this sets up the metronome that ticks in every second, amount of tick is based on BPM conversion above.
        //iterate playHead with Sequences.
        if(isPlay){
            if (lastCount!=currentCount) {//if we have a new timer int this sample, play the sound
                playHead ++;
            }
        }
    }
    int sync(){return playHead;};
    
    
    
};

#endif /* INF_Clock_h */
