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
#include "PolyGUI.h" // GUI
#include "ofMain.h"

struct Steps{
public:
    
    int *accent;
    bool on;
    
    Steps():on(false), accent(0){
        
    }
    ~Steps()
    {
        //destructor
        if(accent != NULL)
            delete accent;
    };
};



//operator overloading test
struct Loop: public Bjorklund{
public:
    
    Loop(){};
    Loop(vector<bool> &v){
        //constructor for usual step sequencer
        //gets sequence from PolyGUI
    }
    Loop(int &step, int &pulse):seq_len(step), seq_pulse(pulse){
        //constructor for Euclidean Rhythm sequence
        Bjorklund(seq_len, seq_pulse, true);
    }
    vector<bool> copy(vector<bool>&v, bool verbose){
        seq.clear();
        for(int i=0;i!=v.size();++i){
            seq.insert(seq.begin()+i, v[i]);
        }
        if(verbose){
            cout<<"[Sequence is created "<<seq_len<<":"<<seq_pulse<<"] "<<ofGetElapsedTimef()<<endl;
            cout<<"[Sequence Saved:";
            for(bool x:v)
                cout<<x;
            cout<<"]"<<endl;
        }
        return v;
    }
    bool trigger(int playHead){
        return (euclid) ? sequence[playHead%seq_len] : 0;
    }
    
    bool euclid;
    int seq_len, seq_pulse;
    vector<bool> seq;
};

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
    void play(int &playHead);
    
    void draw();
    
    
    void setNote(int &pitch){note = pitch;};
    bool trigger(){return (notePlayed == true ? 1 : 0); };
    void setClock(int BPM, int speed){bps = BPM / 60.f * pow(2,speed); };
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
    double bps;
    
    int currentCount;
    int lastCount, playHead;
    
};


#endif /* Sequencer_h */
//