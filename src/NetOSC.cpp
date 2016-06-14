

#include "NetOSC.h"

NetOSC::NetOSC(string HOST, int PORT):
ip_adrs(HOST), port_adrs(PORT)
{
    
    string netAddress;
    stringstream convert;
    convert << ":" <<port_adrs;
    netAddress = ip_adrs + convert.str();
    
    sender.setup(ip_adrs, port_adrs);
    //add slashes
//    if(!oscTypeTag.empty()){
//        string::iterator it;
//        it = oscID.insert(oscID.begin(), '/');
//        it = oscID.insert(oscID.end(), '/');
//    }
    cout<<"[OSC connection is established :: "<<netAddress<<"]"<<endl;
}
//--------------------------------------------------------------
void NetOSC::receive(Note &note, bool trigger){
    
    if(trigger)
        sender.sendMessage(*msg);
}
//--------------------------------------------------------------