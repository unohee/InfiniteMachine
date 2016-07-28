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

class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
        void audioOut(float * output, int bufferSize, int nChannels);
        void exit();

    
    //Events
    void keyPressed(int key);
    void keyReleased(int key);
    void deviceSelected(int &eventArgs);
    void MIDI_ch_changed(int &eventArgs);
    void tempoChange(int &eventArgs);
    void seqStart(bool &eventArgs){};
    void AbletonPlayed(Ableton &eventArgs);
    
    //unused events
    void mouseMoved(int x, int y ){};
    void mouseDragged(int x, int y, int button){};
    void mousePressed(int x, int y, int button){};
    void mouseReleased(int x, int y, int button){};
    void mouseEntered(int x, int y){};
    void mouseExited(int x, int y){};
    void windowResized(int w, int h){};
    void dragEvent(ofDragInfo dragInfo){};
    void gotMessage(ofMessage msg){};
    
    string ip_adrs, port_adrs;
    
    //GUIs
    vector<ofxDatGuiComponent*>docker;
    Dat_Docker *docks;
    unique_ptr<INF_Module> module;
    unique_ptr<INF_Transport> transport;
    
    ofxIntSlider s;
    

    //Network component
    INF_MIDI *midi; //MIDI OUTPUT
    OSC_Receive oscListener; //OSC Receiver (from Ableton)
    string notes[127];


    //Sequencing
    bool bHost;
    
    float tempo;
    int currentBar, currentBeat;
    //Maximilian for Timing
    int currentCount, lastCount;
    int playHead;
    double bps;
    bool isPlay;
    maxiOsc timer;
    void setTempo(float BPM);
    
    
    string timeSignature;
    int divisor, playHeadAmt;
    vector<bool>accents;
    string beatGrid;
    
};
