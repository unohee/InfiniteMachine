#ifndef Bjorklund_h
#define Bjorklund_h

#include "ofMain.h"
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class Bjorklund{

public:

    Bjorklund():verbose(0){};
    Bjorklund(int step, int pulse, bool _verbose): lengthOfSeq(step), pulseAmt(pulse), verbose(_verbose){
        if(lengthOfSeq <= 0 || lengthOfSeq < pulseAmt) lengthOfSeq = pulseAmt;
        init();
    };
    ~Bjorklund(){
        if(verbose)
            cout<<"[Bjorklund::Deleted] "<<ofGetElapsedTimef()<<endl;
    };
    void init();
    void init(int step, int pulse);
    
    void iter();
    void buildSeq(int slot);
    void clear();
    void print();
    
    int getSequence(int index) {return sequence.at(index);};
    int size() {return (int)sequence.size();};

    vector<bool>sequence;
    vector<int>remainder;
    vector<int>count;

    int lengthOfSeq;
    int pulseAmt;
    
private:
    bool verbose;

};

#endif /* bjorklund_h*/
