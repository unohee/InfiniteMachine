//
//  INF_MIDI.h
//
//  Created by Heewon Oh on 25/06/2016.
//
//

#ifndef INF_MIDI_h
#define INF_MIDI_h

#include "ofxMidi.h"
#include "ofxDatGui.h"
#include "Note.h"

class INF_MIDI{

public:

    ofxMidiMessage midiMessage;
    ofxMidiOut midiOut;
    int channel;
    unsigned int currentPgm;
    int voice;
    int note;
    int velocity;
    bool isPlayed[108];
    string notes[108];
    
    INF_MIDI();
    ~INF_MIDI(){
        //destructor
        midiOut.closePort();
    }
    void setup();
    void sendNote(Note &n);
    void setDevice(int &device){
        midiOut.openPort(device); // by number
        midiOut.getPort();
    };
    void setDevice(string &name){
        midiOut.openPort(name);
        midiOut.getPort();
    };
    void deviceSelected(ofxDatGuiDropdownEvent e){
        midiOut.openPort(e.child);
        midiOut.getPort();
    };
    void exit(){
        midiOut.closePort();
    };
    

    
    
};

#endif /* INF_MIDI_h */
