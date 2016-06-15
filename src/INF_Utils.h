//
//  INF_Utils.h
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 14/06/2016.
//
//

#ifndef INF_Utils_h
#define INF_Utils_h

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

template<class T> class DeleteVector
{
public:
    // Overloaded () operator.
    // This will be called by for_each() function.
    bool operator()(T x) const
    {
        // Delete pointer.
        delete x;
        return true;
    }
};
//vector<int> urn(int length){
//    srand (time(NULL));
//    //create an array.
//    vector<int>v;
//    vector<int>list;
//    for(int i=0; i < length;i++)
//        v.push_back(i);
//    do {
//        int index = rand() % v.size() + 0;//pick numbers from array
//        list.push_back(v[index]);//copy to output vector
//        v.erase(v.begin()+index);//erase
//    } while(!v.empty());
//    
//    return list;
//}

class Urn{
public:
    
    Urn(int _length):length(_length){};
    ~Urn(){
        cout<<"urn deleted"<<endl;
    }
    vector<int> urn(){
        srand (time(NULL));
        //create an array.
        vector<int>v;
        for(int i=0; i < length;i++)
            v.push_back(i);
        do {
            int index = rand() % v.size() + 0;//pick numbers from array
            list.push_back(v[index]);//copy to output vector
            v.erase(v.begin()+index);//erase
        } while(!v.empty());
        cout<<"[List created]"<<endl;
        
        return list;
    }
    int length;
    vector<int>list;
};

class INF_Utils{
public:
    
    
};

#endif /* INF_Utils_h */
