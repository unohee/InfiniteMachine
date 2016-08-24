//
//  INF_Sequencer.cpp
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 21/08/2016.
//
//

#include "INF_Sequencer.hpp"

void print(vector<bool> &v){
    vector<bool>::iterator outputIterator;
    cout<<"Output :";
    for(outputIterator = v.begin();
        outputIterator != v.end();
        outputIterator++){
        if(*outputIterator == 1)
            cout<<"X";
        else
            cout<<".";
    }
    cout<<endl;
}
//--------------------------------------------------------------
INF_Sequencer::INF_Sequencer():bGen(false), seq_len(16), seq_pulse(0){
    al = auto_ptr<Algorithms>(new Algorithms());
}
//--------------------------------------------------------------
INF_Sequencer::~INF_Sequencer(){

}
void INF_Sequencer::setup(int length, int pulse, int timeSpan){
    seq_len = length; seq_pulse = pulse;
    pattern.reserve(seq_len);
}
//--------------------------------------------------------------
void INF_Sequencer::generate(){
    pattern = al->Euclidean(seq_len, seq_pulse);
    isEuclid = true;
    bGen = true;
    print(pattern);
}
//--------------------------------------------------------------
void INF_Sequencer::makeComp(vector<bool> v){
    vector<bool> output; //pattern which will be created(and returned) in this function
    output.reserve(v.size());
    //in order to create complementary set of input pattern, function has to count the amount of onsets.
    output = al->makeComp(v); //check Algorithm implementation..
    
    print(output);
    pattern = output;
}
//--------------------------------------------------------------
void INF_Sequencer::rotate(int offset){
    if(pattern.size() > 1 && bGen == true){
        std::rotate(pattern.begin(), pattern.end()-offset, pattern.end());
    }
    else{
        generate();
    }

}
//--------------------------------------------------------------
vector<bool> INF_Sequencer::getPattern(){
    if(pattern.size() > 1)
        return pattern;
}
//--------------------------------------------------------------

