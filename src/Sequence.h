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

using namespace std;
class Sequence{
    
public:
    
    int index, pitch, length, onset;
    vector<bool>pattern;
    vector<int>velocity;
    
    Sequence():index(0), onset(0), length(0), pitch(36){
        
    };
    ~Sequence(){
        pattern.clear();
        velocity.clear();
    }
    void getPattern(vector<bool>v){
        length = v.size();
        pattern.reserve(length);
        velocity.reserve(length);
        pattern = move(v);//copy
        
        for(int i=0; i < pattern.size();i++){
            if(pattern[i] == 1)
                onset ++;
        }
    }
    
};