//
//  Sequencer.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 13/06/2016.
//
//

#include "Sequencer.h"


void Sequencer::seq_change(int step, int pulse){
    if(step > 0 && step >= pulse){
        bLund.init(step, pulse);
    }else if(step <= pulse){
        step == pulse;
        bLund.init(step, pulse);
        //throw
    }
}
//--------------------------------------------------------------
void Sequencer::play(bool isPlay){
    //clock ticks here..
    currentCount=floor(counter.phasor(bps));//this sets up the metronome that ticks in every second, amount of tick is based on BPM conversion above.
    //iterate playHead with Sequences.
    int length = bLund.sequence.size();
    
    if (lastCount!=currentCount) {//if we have a new timer int this sample, play the sound
        
        if(isPlay)
        {
            notePlayed = bLund.sequence.at(playHead%length);
            playHead++;
            if(playHead==length) playHead = 0;
            lastCount=0;
        }
        else{
            playHead = 0;
        }
    }
}
//--------------------------------------------------------------
void Sequencer::offset(int offset){
    // simple rotation to the left
    std::rotate(newSeq.begin(), newSeq.begin() + offset, newSeq.end());
};
//--------------------------------------------------------------