//
//  INF_MIDI.cpp
//
//  Created by Heewon Oh on 25/06/2016.
//
//

#include "INF_MIDI.h"


INF_MIDI::INF_MIDI():channel(1), currentPgm(0){
    // print the available output ports to the console
    midiOut.listPorts(); // via instance
    midiOut.openVirtualPort();
    midiOut.openVirtualPort("Infinite Machine"); // open a virtual port for sending midi to other device..
}
void INF_MIDI::sendNote(Note &n){
    if(n.status==KEY_ON){
        midiOut.sendNoteOn(channel, n.pitch, n.velocity);
        ofLogNotice() << "note: " << n.pitch
        << " freq: " << ofxMidi::mtof(n.pitch) << " Hz";
    }else if(n.status==KEY_OFF){
        midiOut.sendNoteOff(channel, n.pitch);
    }
}