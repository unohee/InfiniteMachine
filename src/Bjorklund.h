#ifndef Bjorklund_h
#define Bjorklund_h

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

class Bjorklund{

public:

    Bjorklund(){};
    Bjorklund(int step, int pulse): lengthOfSeq(step), pulseAmt(pulse){
        if(lengthOfSeq <= 0 || lengthOfSeq < pulseAmt) lengthOfSeq = pulseAmt;
        init();
    };
    ~Bjorklund(){
        //destructor
        clear();
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

};

#endif /* bjorklund_h*/
