//
//  GCD.hpp
//  Gridview
//
//  Created by Heewon Oh on 04/08/2016.
//
//
#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include "Sequence.h"

using namespace std;

struct Euclid{
public:
    
    int length, onset;
    vector<bool>sequence;
    Euclid(){};
    
};

class GCD{
public:
    
    int in1, in2;
    int setAmt;
    
    GCD(){};
    ~GCD(){
        for(auto &x:subsets)
            x.reset();
            
        subsets.clear();
    };
    int gen(int _in1, int _in2);
    vector<unique_ptr<Euclid>> subsets;
    
};