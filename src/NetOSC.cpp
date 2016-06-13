

#include "NetOSC.h"

NetOSC::NetOSC(string HOST, string PORT, string oscTypeTag):
ip_adrs(HOST), port_adrs(PORT), oscID(oscTypeTag)
{
    sender.setup(ip_adrs, stoi(port_adrs));
    //add slashes
    if(!oscTypeTag.empty()){
        string::iterator it;
        it = oscID.insert(oscID.begin(), '/');
        it = oscID.insert(oscID.end(), '/');
    }
}
//--------------------------------------------------------------
void NetOSC::makeNote(Note &note){
    
    msg->addIntArg(note.pitch);
    msg->addIntArg(note.velocity);
    msg->addFloatArg(note.duration);
    msg->setAddress(typeTag);
    
}
//--------------------------------------------------------------
void NetOSC::sendOSC(bool isOn){
    sender.sendMessage(*msg);
}
//--------------------------------------------------------------