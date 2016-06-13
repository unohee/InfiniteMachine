#include "Bjorklund.h"

//Edited NoisyLittleBurger's Bjorklund Algorithm in C
//http://www.noisylittlebugger.net/diy/bjorklund/Bjorklund_Working_Final/Bjorklund_algorithm_arduino.txt
//CHANGED :
//1. use dynamic array.
//2. fixed sequence's off-spot problem
//3. added Explanation about Algorithm based on G.Touissant's Paper,
//"The Euclidean Algorithm Generates Traditional Musical Rhythms"
//
//--------------------------------------------------------------
void Bjorklund::init(){
    try{
        iter();
        
    }catch(out_of_range){
        cerr<<"pulse::out_of_range"<<'\n';
    }
}
void Bjorklund::init(int step, int pulse){
    lengthOfSeq = step;
    pulseAmt = pulse;
    
    try{
        iter();
        
    }catch(out_of_range){
        cerr<<"pulse::out_of_range"<<'\n';
    }
}
void Bjorklund::iter(){
    //\Bjorklund algorithm
    //\do E[k,n]. k is number of one's in sequence, and n is the length of sequence.
    int divisor = lengthOfSeq   - pulseAmt; //initial amount of zero's
    if(divisor < 0) throw out_of_range{"Divisor has to be greator than 0"};
    
        //Error Handling* this iteration only be computed when pulse is greater than 0.
    
    //Actual iteration process
   if(pulseAmt > 0){
        remainder.resize(lengthOfSeq); count.resize(lengthOfSeq);
        
        remainder.insert(remainder.begin(), pulseAmt); //first elements of remainder is the amount of ones's
        //iteration
        int index = 0; //we start algorithm from first index.
        do{
            //The smaller number is repeatedly subtracted from the greater until the greater is zero or becomes smaller than the smaller
            count.at(index) = divisor / remainder[index];
            remainder.at(index+1) = divisor % remainder[index];
            divisor = remainder.at(index);
            index++; //move to next step.
        }
        while(remainder.at(index) > 0);
        
        count.at(index) = divisor;
        buildSeq(index); //place one's and zero's

    }else if(pulseAmt == 0){
        //0 pulses don't need iteration. thus it only returns 0 in all steps.
        for(int i = 0; i < lengthOfSeq; i++){
            sequence.insert(sequence.begin()+i, 0);
        }
    }
}
void Bjorklund::buildSeq(int slot){
    //construct a binary sequence of n bits with k one‚Äôs, such that the k one‚Äôs are distributed as evenly as possible among the zero‚Äôs
    int step = 0;
    if(sequence.size() < lengthOfSeq){
        if (slot == -1) {
            sequence.insert(sequence.begin()+step, false); //insert 0 into array
        }
        else if (slot == -2)  {
            sequence.insert(sequence.begin()+step, true); //insert 1 into array
        }
        else {
            for (unsigned int i = 0; i < count.at(slot); i++)
                buildSeq(slot-1);
            if (remainder.at(slot) !=0)
                buildSeq(slot-2);
        }
        step ++;
    }
}
void Bjorklund::clear(){
    //plush all data before create new sequence.
    sequence.clear();
    remainder.clear();
    count.clear();
}
void Bjorklund::print(){
    for(int i=0; i != sequence.size();i++){
        cout<<sequence.at(i);
    }
    cout<<'\n';
    cout<<"Size : "<<sequence.size()<<'\n';
}
