//
//  Sequencer.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 13/06/2016.
//
//

#include "Sequencer.h"

Sequencer::Sequencer():step(16),pulses(4){
    //default constructor
    Bjorklund b(step, pulses, 1);
    copy(b.sequence, true);
};
//--------------------------------------------------------------
Sequencer::Sequencer(int seq_len, int seq_pulse):step(seq_len),pulses(seq_pulse)
{
    //parameterized constructor
    Bjorklund b(step, pulses, 1);
    copy(b.sequence, true);
};
//--------------------------------------------------------------
void Sequencer::seq_change(int step, int pulse){
    if(step > 0 && step >= pulse){
        Bjorklund b(step,pulse, 0);
        copy(b.sequence, false);
    }else if(step <= pulse){
        step == pulse;
    }
    Bjorklund b(step,pulse, 0);
    copy(b.sequence, false);
}
//--------------------------------------------------------------
void Sequencer::play(bool isPlay){
    //clock ticks here..
    currentCount=floor(counter.phasor(bps));//this sets up the metronome that ticks in every second, amount of tick is based on BPM conversion above.
    //iterate playHead with Sequences.
    int length = seq.size();
    
    if (lastCount!=currentCount) {//if we have a new timer int this sample, play the sound
        
        if(isPlay)
        {
            notePlayed = seq.at(playHead%length);
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
void Sequencer::copy(vector<bool>&v, bool verbose){
    for(int i=0;i!=v.size();++i){
        seq.insert(seq.begin()+i, v[i]);
    }
    
    if(verbose){
        cout<<"[Sequence is created "<<step<<":"<<pulses<<"]"<<endl;
        cout<<"[Sequence Saved:";
        for(bool x:v)
            cout<<x;
        cout<<"]"<<endl;
    }else{
        
    }
    
    //Task : print sequence is x and .;
}
//--------------------------------------------------------------
void Sequencer::offset(int offset){
    // simple rotation to the left
    std::rotate(seq.begin(), seq.begin() + offset, seq.end());
};
//--------------------------------------------------------------