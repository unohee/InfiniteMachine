//
//  Note.h
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 13/06/2016.
//
//

#ifndef Note_h
#define Note_h

#include "ofxOsc.h"
#include <stdio.h>

class Note{
    
public:
    
    Note():
    pitch(60),
    velocity(127),
    duration(0.100),
    typeTag("/init/")
    {};
    Note(int _pitch, int _velocity, float _duration, string _typeTag):
    pitch(_pitch),
    velocity(_velocity),
    duration(_duration),
    typeTag(_typeTag)
    {
        msg->addIntArg(pitch);
        msg->addIntArg(velocity);
        msg->addFloatArg(duration);
        msg->setAddress(typeTag);
    };
    int pitch;
    int velocity;
    float duration;
    string typeTag;
    
    ofxOscMessage *msg;
};

#endif /* Note_h */
