//
//  INF_Algorithm.cpp
//  collection of algorithm to alter / create / join Euclidean Pattern.
//
//  Created by Heewon Oh on 06/08/2016.
//
//

#include "INF_Algorithm.h"

vector<bool> INF_Algorithm::makeComp(Sequence s){
    //complementary rhythm set for Euclidean Rhythm
    int offset = 0;
    vector<bool> comp;
    comp.reserve(s.length);
    
    int pulse, length;
    length = s.length;
    if(s.onset >=1)
        pulse = s.length - s.onset;//E(n,k)'s subset is E(n-k, k)
    
    Bjorklund *b = new Bjorklund(length, pulse);
    comp = b->LoadSequence();

    for(int i=0; i<comp.size();i++){
        if(s.pattern[i] == true && comp[i]== true){
            offset++;
            std::rotate(comp.begin(), comp.begin()+(offset-1), comp.end());
        }
    }
    delete b;
    return comp;
}
vector<bool> INF_Algorithm::compound(vector<bool> v, bool isRandom){
    vector<bool> output;
    vector<bool>::iterator outputIterator;
    int length, onset, rand;
    
    length = 16 - v.size();
    cout<<"Length :"<<length<<endl;
    if(isRandom){
        do{
            rand = (int)ofRandom(length-1);
            if(rand < length && rand > 2){
                onset = rand;
                cout<<"Onset :"<<onset<<endl;
                break;
            }
        }while(rand != length);
    }else{
        int previous =0;
        for(int i=0;i < v.size();i++){
            if(v[i] == 1){
                previous ++; // calculate input sequence's onset
            }
        }
        onset = length - previous;
        cout<<"onset (not random) :"<< onset<<endl;
    }
    Bjorklund *b = new Bjorklund(length,onset);
    b->iter();
    output = b->LoadSequence();
    delete b;
    
    for(outputIterator = output.begin();
        outputIterator != output.end();
        outputIterator++){
        cout<<*outputIterator;
    }
    cout<<'\n';
    cout<<"Length :"<<output.size()<<endl;
    return output;
}
//--------------------------------------------------------------
vector<bool> INF_Algorithm::permutate(int timespan, vector<bool> &v){
    //Permutation process
    //fits euclidean sequence of different timespan (notes) into 16th Grid (or Mother-set)
    //
    vector<bool>output;
    vector<bool>::iterator outputIterator;
    int counter = 0;
    int indices = 0;
    int length;
    
    //**** only use this function as input is euclidean ****
    if(timespan == 2){ //if clock ticks twice per beat.. (quaver)
        length = beatsPerbar * beatResolution;
        output.reserve(length);
        do{
            if(counter % 2 == 1){
                output.insert(output.begin()+counter, 0);
                indices ++;
            }else{
                output.insert(output.begin()+counter, v[indices]);
            }
            counter ++;
        }while(counter < length);
        
    }else if(timespan == 3){//triplets
        length = timespan * beatsPerbar;
        output.reserve(length);
        //only do rotation. graphical notations is equivalent as internal sequence.
        
    }else if(timespan == 4){ //semiquaver
        //do nothing.
        output = v;
    }else if(timespan == 5){//quintuplets
        //only do rotation
        //if timespan is bigger than 4, the maximum length is bigger than mother sequence (of 16 grid in 4/4)
        //check onsets on every 5 notes and rotate
    }else if(timespan == 6){//sextuplets
        //check onsets on every 6 notes
        
    }else if(timespan == 7){//septuplets
        //check onsets on every 7 notes
    }else if(timespan == 8){//double time
        
    }
    
    for(outputIterator = output.begin();
        outputIterator != output.end();
        outputIterator++){
        cout<<*outputIterator;
    }
    cout<<'\n';
    cout<<"Length :"<<output.size()<<endl;
    
    //once the process's done. find the optimal offsets to avoid interlocking with target sequence.
    
    return output;
}
//--------------------------------------------------------------
vector<bool> INF_Algorithm::join(vector<bool> first, vector<bool> second){
    vector<bool>join;
    int length = 0;
    int counter = 0;
    length = first.size() + second.size();
    
    do{
        join.push_back(first[counter]);
        counter ++;
    }while(join.size() < first.size());
    
    counter = 0;
    
    do{
        join.push_back(second[counter]);
        counter ++;
    }while(join.size() < length);
    
    return join;
}
//--------------------------------------------------------------
vector<bool> INF_Algorithm::join(vector<Sequence> &v){
    vector<bool>concated;
    int length = 0;
    int counter = 0;
    int level = 0;
    
    for(int i=0; i < v.size();i++){
        length += v[i].pattern.size();
    }
    cout<<"Concated Length::"<<length<<"Size :"<<v.size()<<endl;
    concated.reserve(length);
    
    do{
        concated.push_back(v[level].pattern[counter]);
        if(concated.size() == v[level].pattern.size()){
            counter = 0;
            level += 1;
        }else if(concated.size() < length && counter <= v[level].pattern.size()){
            counter ++;
        }
        
        if(counter == v[level].pattern.size()){
            break;
        }
    }while(concated.size() < length);
    
    return concated;
}
//--------------------------------------------------------------
vector<bool> INF_Algorithm::multiply(Sequence s,int mult){
    //Concatenation process of multiple Euclidean Rhythm
    //Gomez-Martin et.al 's theorem:
    //"for any Euclidean Rhythm E(k,n) with 1<= k <= n, and any natural number c,
    //E(ck, cn) + E(k,n) is a rotation of E((c+1)k,(c+1)n)."
    vector<bool>multiplied;
    multiplied.resize((mult+1)*s.length);
    if(mult >0){
        Bjorklund *b = new Bjorklund((mult+1)*s.length, (mult+1)*s.onset);
        multiplied = b->LoadSequence();
        return multiplied;
        delete b;
    }
}
//--------------------------------------------------------------
bool INF_Algorithm::isEuclid(Sequence s){
    int length, onset, offset, iterator;
    vector<bool>pattern;
    bool bEuclid;
    length = s.length;
    onset = s.onset;
    offset = 0;
    iterator = 0;
    
    Bjorklund *b = new Bjorklund(length, onset);
    pattern = b->LoadSequence();
    delete b;
    
    for(int i=0; i<pattern.size();i++){
        if(s.pattern[i] != pattern[i]){//check whether input pattern is 'rotated' Euclidean String.
            
            //if it's not matched, it keeps rotating pattern
            offset++;
            std::rotate(pattern.begin(), pattern.begin()+(offset-1), pattern.end());
            if(i == pattern.size()){
                bEuclid = false;
                break; //search ends when iterator reaches at the end of sequence
                return false;
            }
        }else if(s.pattern == pattern){
            return true;
        }
    }
}
//--------------------------------------------------------------