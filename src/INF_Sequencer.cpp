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
    ofLogNotice()<<"Sequence Agent Deallocated"<<endl;
}
void INF_Sequencer::setup(int length, int pulse, int timeSpan){
    seq_len = length; seq_pulse = pulse;
    pattern.reserve(seq_len);
}
//--------------------------------------------------------------
void INF_Sequencer::generate(){
    auto_ptr<Bjorklund> euclid = auto_ptr<Bjorklund>(new Bjorklund());
    auto_ptr<GCD> gcd = auto_ptr<GCD>(new GCD());
    
    vector<bool> first, second;
    vector<bool>::iterator outputIterator;
    
    //before apply Bjorklund's Algorithm with two given numbers, we need to find the GCD of Two input number (which is length and amount of onset)
    
    //Note that minimum length of sequence is 2.
    gcd->gen(seq_len, seq_pulse);
    //GCD algorithm finds the subsets through the process of finding GCD(Greator Common Divisor)
    if(seq_pulse >= 1){
        if(gcd->subsets.size() > 2 && gcd->subsets[1]->length + gcd->subsets[2]->length == seq_len){
            //this is compound set.
            //it joins 2 euclidean rhythms into one compound rhythm. it is different as simply applying two numbers into Bjorklund algorithm. it makes rhythm sequence more interesting while it still explicits the characteristic feature of Euclidean rhythm, or poly-rhythm.
            ofLogNotice()<<"Compound Euclidean 2-3"<<"Size of subsets: "<<gcd->subsets.size()<<endl;
            euclid->init(gcd->subsets[1]->length, gcd->subsets[1]->onset);
            first = euclid->LoadSequence();
            euclid->init(gcd->subsets[2]->length, gcd->subsets[2]->onset);
            second = euclid->LoadSequence();
            pattern = al->join(first, second);
        }else if(gcd->subsets.size() <=2){
            ofLogNotice()<<"Single Euclidean"<<endl;
            euclid->init(seq_len, seq_pulse);
            pattern = euclid->LoadSequence();
        }else{
            ofLogNotice()<<"Single Euclidean"<<endl;
            euclid->init(seq_len, seq_pulse);
            pattern = euclid->LoadSequence();
        }
    }else{
        euclid->init(seq_len, seq_pulse);
        pattern = euclid->LoadSequence();
    }
    
    isEuclid = true;
    bGen = true;
    first.clear(); second.clear();
    euclid.reset();
    gcd.reset();
    
    print(pattern);
//    cout<<"Output :";
//    for(outputIterator = pattern.begin();
//        outputIterator != pattern.end();
//        outputIterator++){
//        if(*outputIterator == 1)
//            cout<<"X";
//        else
//            cout<<".";
//    }
//    cout<<endl;
}
//--------------------------------------------------------------
vector<bool> INF_Sequencer::getPattern(){
    if(pattern.size() > 1)
        return pattern;
}
//--------------------------------------------------------------
vector<bool> makeComp(INF_Sequencer &seq){
    int onset = 0; int offset = 0;
    int length = seq.seq_len;
    auto_ptr<Algorithms> al = auto_ptr<Algorithms>(new Algorithms());
    
    vector<bool> input; //patterns from outside function
    vector<bool> output; //pattern which will be created(and returned) in this function
    input = seq.getPattern();
    output.reserve(length);
    //friend function gets directly other sequencers' pattern.
    //in order to create complementary set of input pattern, function has to count the amount of onsets.
    onset = seq.seq_len - seq.seq_pulse; //new set's onset
    output = al->makeComp(input); //check Algorithm implementation..
    
    print(output);

    return output;
}
//--------------------------------------------------------------
