

//NetOSC
#ifndef NetOSC_h
#define NetOSC_h

#include <string>
#include <iostream>
#include "ofxOsc.h"
#include "Note.h"

using namespace std;

class NetOSC{
public:
    
    NetOSC(string HOST, string PORT, string oscTypeTag);
    ~NetOSC(){
        if(msg)
        delete[] msg;
    }
    void makeNote(Note &note);
    void sendOSC(bool isOn);
    
    string ip_adrs, port_adrs;
    string typeTag;
    string oscID;
    
private:
    
    ofxOscMessage *msg;
    ofxOscSender sender;
};
#endif /* NetOSC_h*/