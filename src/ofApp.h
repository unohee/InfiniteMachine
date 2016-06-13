#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "Sequencer.h"
#include "NetOSC.h"


class ofApp : public ofBaseApp{

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

    
    void setGui(){
        //maximum length of sequence
        //GUI-------------------------------------------
        //add Listeners first.
        seq_len.addListener(this, &ofApp::lengthChanged);
        seq_pulse.addListener(this, &ofApp::beatChanged);
        bpm_slider.addListener(this, &ofApp::tempoChanged);
        
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
        //----------------------------------------------
        
    }
    
    void lengthChanged(int &seq_len){
        //new iteration for euclidean rhythm
        if(seq_len < seq_pulse){
            seq_len = seq_pulse;
        }
        seq.seq_change(seq_len, seq_pulse);
//        //re-popluating Infinity Series
//        matrix.init(0,7,seq_len);
//        matrix.generate();
    }
    void beatChanged(int &seq_pulse){
        if(seq_pulse < seq_len){
            
        }
        else{
            seq_pulse = seq_len;
        }
        seq.seq_change(seq_len, seq_pulse);
    }
    void tempoChanged(int &bpm_slider){
        seq.setClock(bpm_slider,4);
    }
    
    
    string ip_adrs, port_adrs;
    
    Sequencer seq;
    bool trigger;
    
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
