#pragma once

#include "ofMain.h"

#include "INF_Utils.h"
#include "INF_Module.h"
#include "INF_MIDI.h"
#include "INF_OSC.h"
#include "INF_Transport.h"

#include "Note.h"
#include "Dat_Docker.h"
#include "ofxGui.h"

#define SRATE 44100 //SAMPLE RATE
#define BUFFER_SIZE 512 // BUFFERSIZE
#define HOST "localhost" //default address
#define PORT 8080 //default port.

typedef INF_MIDI MidiOut;
typedef OSC_Receive oscIn;

class ofApp : public ofBaseApp {
public:
    
    //GUIs
    Dat_Docker *docks;
    unique_ptr<INF_Module> module;
    unique_ptr<INF_Transport> transport;
    
    //Network component
    MidiOut midi; //MIDI OUTPUT
    oscIn oscListener; //OSC Receiver (from Ableton)
    string notes[127];
    string ip_adrs, port_adrs;
    
    //Events
    ofEvent<int>globalPlayHead;
    ofEvent<bool>activated;
    
    //Sequencing
    vector<bool>triggers;
    bool triggerTest;
    vector<bool>seqTest;
    
    bool bHost;
    int currentBar, currentBeat;
    
    //member variables for Maximilian
    int currentCount, lastCount;
    int playHead, BPM, ticksPerBeat;
    double bps;
    bool isPlay;
    maxiOsc clock;
    maxiClock c;
    mutex audioMutex;

    //Transport informations
    ofParameter<int>tempo;
    string timeSignature;
    int divisor, playHeadAmt;
    int kicktrigger;
    vector<bool>accents;
    string beatGrid;
    

    void setup();
    void update();
    void draw();
    void audioOut(float * output, int bufferSize, int nChannels);
    void exit();
    
    //Events used
    void keyPressed(int key);
    //custom event callbacks
    void AbletonPlayed(Ableton &eventArgs);
    void MIDICallback(MidiState &eventArgs);
    void globalState(TransportMessage &eventArgs);
    void setMode(bool &eventArgs);
    void tempoChange(int &eventArgs);
    void clockPlayed(int &eventArgs);
    
    void seqStart(bool &eventArgs){};
    
    //unused events
    void keyReleased(int key){};
    void mouseMoved(int x, int y ){};
    void mouseDragged(int x, int y, int button){};
    void mousePressed(int x, int y, int button){};
    void mouseReleased(int x, int y, int button){};
    void mouseEntered(int x, int y){};
    void mouseExited(int x, int y){};
    void windowResized(int w, int h){};
    void dragEvent(ofDragInfo dragInfo){};
    void gotMessage(ofMessage msg){};
};
