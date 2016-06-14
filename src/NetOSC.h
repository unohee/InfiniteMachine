

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
    
    NetOSC(){};
    NetOSC(string HOST, int PORT);
    ~NetOSC(){
//        if(msg)
//            delete[] msg;
        cout<<"[OSC Sender Deleted]"<<endl;
    }
    void receive(Note &note, bool trigger);
    
    string ip_adrs;
    int port_adrs;
    string typeTag;
    string oscID;
    
private:
    
    ofxOscMessage *msg;
    ofxOscSender sender;
};
#endif /* NetOSC_h*/