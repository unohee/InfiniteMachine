//
//  GCD.cpp
//  Gridview
//
//  Created by Heewon Oh on 04/08/2016.
//
//

#include "GCD.h"

int GCD::gen(int first, int second){
    //Euclid Algorithm : finding the greatest common divisor.
    
    //first, we need to figure out which number is the greatest common divisor.
    
    //Debug function : we can see values with this bool.
    bool print = true;
    
    int gcd;//create int for GCD.
    int iter;
    //first always should be greater than second.
    if(first>second){
        
        for(int i=1;i <= first && i <=second;i++){
            //Do the iteration to find a number which lower than two numbers.
            if(first%i==0 && second%i == 0 ){
                //we get common divisor i if i's remainder is 0 when it divides both number.
                gcd =i;
            }
        }
        //make set. i'm following Touissant instruction in his paper.
        if(second == 0){
            //if k(second, or pulse in our context) is 0. then we return first only.
            gcd = first;
            //printout sets.
            if(print){
                //printout sets.
                cout<<"E["<<first<<","<<second<<"]"<<endl;
                cout<<"Remainder : "<< gcd << endl;
                
            }
            return first;
            
        }else{
            //if it's greater than 0, return GCD.
            setAmt++;
//            subsets.reserve(setAmt);
            if(print){
                //printout sets.
                cout<<"E["<<first<<","<<second<<"]"<<endl;
                cout<<"Remainder : "<< gcd << endl;
            }
            //then it prints remainders in every iteration.
            //it's recursive function.
            unique_ptr<Euclid> e = unique_ptr<Euclid>(new Euclid());
            e->length = first;
            e->onset = second;
            subsets.push_back(move(e));
            
            return gen(second, first % second);
        }
        
    }else{
        //printout error and returns NaN.
        cout<<"Error. First integer has to be greater than Second."<<endl;
        //then it intentioannly returns NaN (to cause an error.)
        return std::numeric_limits<double>::quiet_NaN();
    }
    
    return gcd;
}