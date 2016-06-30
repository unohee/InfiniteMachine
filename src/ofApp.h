#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "INF_Utils.h"
#include "INF_MIDI.h"

#include "Sequencer.h"
#include "NetOSC.h"
#include "PolyGUI.h"
#include "Note.h"

//GUI
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

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button){};
    void mouseEntered(int x, int y){};
    void mouseExited(int x, int y){};
    void windowResized(int w, int h){};
    void dragEvent(ofDragInfo dragInfo){};
    void gotMessage(ofMessage msg){};
        void exit();

    void deviceSelected(int &eventArgs);
    void MIDI_ch_changed(int &eventArgs);
    
    void setGui(){
        //maximum length of sequence
        //GUI-------------------------------------------
        //ofParameter initial value.
        seq_len = 16;
        seq_pulse = 4;
        bpm_slider = 130;
        //setup
        gui.setup();
        gui.add(seq_len.setup("Length of SEQ",16,2,max_len)); //max length needs to be dynamic.
        gui.add(seq_pulse.setup("Beats in SEQ", 3,2,max_len)); //this too.
        //    gui.add(offset.setup("Offset", 0, 0, max_len));
        seq_len.addListener(this, &ofApp::lengthChanged);
        seq_pulse.addListener(this, &ofApp::beatChanged);
        //----------------------------------------------
    }
    
    void lengthChanged(int &seq_len){
        //new iteration for euclidean rhythm
        if(seq_len < seq_pulse){
            seq_len = seq_pulse;
        }
//        cout<<"[Sequence::"<<seq_pulse<<"/"<<seq_len<<"]"<<endl;
        for(int i=0;i!=INF_seq.size();++i){
            INF_seq[i]->seq_change(seq_len, seq_pulse);
            INF_gui[i]->createPoly(INF_seq[i]->seq);
        }
        
    }
    void beatChanged(int &seq_pulse){
        if(seq_pulse > seq_len){
            seq_pulse = seq_len;
        }
//        cout<<"[Sequence::"<<seq_pulse<<"/"<<seq_len<<"]"<<endl;
        for(int i=0;i!=INF_seq.size();++i){
            INF_seq[i]->seq_change(seq_len, seq_pulse);
            INF_gui[i]->createPoly(INF_seq[i]->seq);
        }
    }
    string ip_adrs, port_adrs;
    

    vector<Sequencer*>INF_seq;
    vector<PolyGUI*>INF_gui;
    vector<ofxDatGuiComponent*>docker;
    INF_Clock clock;
    bool trigger;
    bool mouseClick;
    
    
    //Network component
    NetOSC *network;
    Note *n;
    INF_MIDI *midi; //MIDI OUTPUT
    string notes[127];
    
    
    //ofxDatGui
    Dat_Docker *docks;
    
    
    ofxIntSlider seq_len;
    ofxIntSlider bpm_slider;
    ofxIntSlider seq_pulse;
    ofxIntSlider offset;
    ofParameter<string> fps;
    ofxPanel gui;
    ofxToggle start;
    ofxToggle random;
    int max_len;
    int numPulse;
    
    

    
};
