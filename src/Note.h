//
//  Note.h
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 13/06/2016.
//
//

#ifndef Note_h
#define Note_h

#include <stdio.h>

class Note{
    
public:
    
    Note();
    Note(int _pitch, int _velocity, float _duration):
    pitch(_pitch), velocity(_velocity), duration(_duration)
    { };
    int pitch;
    int velocity;
    float duration;
    
};

#endif /* Note_h */
