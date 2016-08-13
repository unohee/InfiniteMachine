//
//  INF_Algorithm.hpp
//
//  Created by Heewon Oh on 06/08/2016.
//
//  Set of Algorithm for Mutation of Euclidean Algorithm


#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Sequence.h"
#include "Bjorklund.h"
#include "ofMain.h"
using namespace std;

class INF_Algorithm{
public:
    //no member variable. everything is arbitrary.
    //pattern processing algorithms
    vector<bool> makeComp(Sequence s);
    vector<bool> join(vector<bool> first, vector<bool> second);
    vector<bool> join(vector<Sequence> &v);
    vector<bool> multiply(Sequence s, int mult);
    vector<bool> permutate(int timespan, vector<bool> &v);
    vector<bool> compound(vector<bool> v, bool isRandom);
    void GCD(Sequence s);
    bool isEuclid(Sequence s);
    
    int beatsPerbar, beatResolution;
    
};