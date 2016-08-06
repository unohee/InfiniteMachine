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