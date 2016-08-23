//
//  INF_Sequencer.hpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 21/08/2016.
//
//

#pragma once;
#include "INF_Algorithm.h"
#include "ofMain.h"

typedef INF_Algorithm Algorithms;

class INF_Sequencer{
    //sequencer class that contains pattern, algorithm etc
public:

    vector<bool> pattern;
    int index, timespan;
    int seq_len, seq_pulse;
    bool isEuclid, bGen;
    auto_ptr<Algorithms> al;
    
    INF_Sequencer();
    ~INF_Sequencer();
    void setup(int length, int pulse, int timeSpan);
    void generate();
    vector<bool> getPattern();
    friend vector<bool> makeComp(INF_Sequencer &seq);
    
    
    
};