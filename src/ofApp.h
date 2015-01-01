#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "INF_Utils.h"

#include "Sequencer.h"
#include "NetOSC.h"
#include "PolyGUI.h"
#include "Note.h"

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
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void exit();

    
    void setGui(){
        //maximum length of sequence
        //GUI-------------------------------------------
        //ofParameter initial value.
        seq_len = 16;
        seq_pulse = 4;
        bpm_slider = 130;
        //setup
        gui.setup();
        gui.add(fps.set("Framerate", ""));
        gui.add(bpm_slider.setup("BPM",130,20,240));
        gui.add(seq_len.setup("Length of SEQ",16,2,max_len)); //max length needs to be dynamic.
        gui.add(seq_pulse.setup("Beats in SEQ", 3,2,max_len)); //this too.
        //    gui.add(offset.setup("Offset", 0, 0, max_len));
        gui.add(random.setup("Randomize", false));
        gui.add(start.setup("PLAY", false));
        
        seq_len.addListener(this, &ofApp::lengthChanged);
        seq_pulse.addListener(this, &ofApp::beatChanged);
        bpm_slider.addListener(this, &ofApp::tempoChanged);
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
    void tempoChanged(int &bpm_slider){
        for(int i=0;i!=INF_seq.size();++i){
            INF_seq[i]->setClock(bpm_slider,4);
        }
//        cout<<"Tempo: "<<bpm_slider<<endl;
    }
    string ip_adrs, port_adrs;
    
    
//    Sequencer *seq;
    
    vector<Sequencer*>INF_seq;
    vector<PolyGUI*>INF_gui;
    INF_Clock clock;
    bool trigger;
    bool mouseClick;
    
    
    //Network
    NetOSC *network;
    Note notes;
    
    //GUI
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
