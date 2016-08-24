//
//  Sequence.h
//
//  Created by Heewon Oh on 06/08/2016.
//
//

#pragma once
#include <iostream>
#include <vector>
#include <cmath>

enum DRUM_NOTE {KICK, SNARE, PERC, HAT};

using namespace std;
class Sequence{
    
public:
    
    int index, pitch, length, onset;
    vector<bool>pattern;
    vector<int>velocity;
    
    Sequence():index(0), onset(0), length(0), pitch(36){
        
    };
    Sequence(int _index, vector<bool> &v):index(_index), length(16), pitch(36){
        for(int i=0; i < pattern.size();i++){
            if(pattern[i] == 1)
                onset ++;
        }
        length = v.size();
        pattern.reserve(length);
        pattern = move(v);//copy
        
    }
    ~Sequence(){
        pattern.clear();
        velocity.clear();
    }
    void setPattern(vector<bool>v){
        length = v.size();
        pattern.reserve(length);
        pattern = move(v);//copy
        
        for(int i=0; i < pattern.size();i++){
            if(pattern[i] == 1)
                onset ++;
        }
    }
    vector<bool> getPattern(){
        if(pattern.size() >0)
            return pattern;
    }
};