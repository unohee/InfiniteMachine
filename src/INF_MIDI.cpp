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
    
    
    //Create midi note array...
    const string note_substring[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    int octave;//octave is 0 - 8;
    for(int noteNum=0; noteNum<108;noteNum++){
        octave = noteNum /12;
        notes[noteNum] = note_substring[noteNum%12]+to_string(octave);
    }
    cout<<"MIDIOUT Initialized"<<endl;
}
void INF_MIDI::sendNote(Note &n){
    
    //note : Ableton Live's MIDI VALUE C1 is 36 (1 octave higher);
    if(n.status==KEY_ON){
        note = n.pitch;
        velocity = n.velocity;
        midiOut.sendNoteOn(channel, n.pitch, n.velocity);
        ofLogNotice() << "note: " << notes[n.pitch-24]
        << " freq: " << ofxMidi::mtof(n.pitch-12) << " Hz";
    }else if(n.status==KEY_OFF){
        note = n.pitch;
        velocity = n.velocity;
        midiOut.sendNoteOff(channel, n.pitch-12);
    }
}
void INF_MIDI::enableVirtual(){
    midiOut.openVirtualPort("Infinite Machine");
}