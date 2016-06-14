//
//  Sequencer.hpp
//  Infinite_Machine
//
//  Created by Heewon Oh on 3/3/16.
//
//

#ifndef Sequencer_h
#define Sequencer_h

#include "ofxMaxim.h"
#include "Bjorklund.h"
#include "ofMain.h"

class Sequencer {
public:
    
    Sequencer();
    Sequencer(int &seq_len, int &seq_pulse);
    
    ~Sequencer(){
        cout<<"[Sequencer Deleted]"<<endl;
    }
    
    void copy(vector<bool>&v, bool verbose);
    void seq_change(int step, int pulse);
    void play(bool isPlay);
    void setNote(int &pitch){note = pitch;};
    bool trigger(){return (notePlayed == true ? 1 : 0); };
    void setClock(int BPM, int ticks){bps = BPM / 60.f * ticks; };
    void offset(int offset);
    bool notePlayed;
    
    //sequencer
    vector<bool>seq;
    int step;
    int pulses;
    
private:
    
    int note;
    //play method
    //Transport Control (Maximilian)
    maxiOsc counter; //Phasor object
    maxiClock mClock;
    double bps;
    
    int currentCount;
    int lastCount, playHead;
    
};


#endif /* Sequencer_h */
//