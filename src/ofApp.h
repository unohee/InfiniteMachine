#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "INF_Utils.h"
#include "INF_MIDI.h"
#include "Sequencer.h"
//#include "NetOSC.h" //DEPRECATED
#include "INF_OSC.h"
#include "Note.h"
#include "Dat_Docker.h"


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
    

    
    vector<Sequencer*>INF_seq;
    
    //GUIs
    vector<ofxDatGuiComponent*>docker;
    Dat_Docker *docks;
    
    //Sequencing
    INF_Clock clock;
    int tempo, currentBar, currentBeat;
    bool trigger;
    bool mouseClick;
    bool start;
    
    
    
    //Network component
    Note *n;
    INF_MIDI *midi; //MIDI OUTPUT
    OSC_Receive oscListener; //OSC Receiver (from Ableton)
    string notes[127];

    
};
