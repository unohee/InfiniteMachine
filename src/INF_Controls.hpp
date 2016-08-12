#pragma once

#include "ofxDatGui.h"
#include "ofMain.h"
#include "Sequence.h"
using namespace std;

struct Controls{
    
    int index, length, pulse, pitch, velocity, offset;
    bool mode, isOn;
    Controls():index(0),length(16),offset(0){
        
    };
    
};

typedef shared_ptr<ofxDatGuiComponent> DatGuiPtr;
typedef shared_ptr<ofxDatGuiSlider> DatSliderPtr;

class INF_Controls{
public:
    
    const string note_substring[12] = {
        "C","C#","D","D#",
        "E","F","F#","G",
        "G#","A","A#","B"};
    
    const vector<string> AbletonDrumMap ={
        "Kick", "Rim", "Snare", "Clap",
        "Clave", "Tom Low", "Hihat Closed", "Tom Mid",
        "Maracas", "Tom Hi", "Hihat Open", "Conga Low",
        "Conga Mid", "Cymbal", "Conga Hi", "Cowbell"
    };//I know this is kinda weird, but ofxDatGuiDropdown only gets vector.
    
    const vector<string> MachineDrum = {
        "BD", "SD", "HT", "MT",
        "LT", "CP", "RS", "CB",
        "CH", "OH", "RC", "CC",
        "M1", "M2", "M3", "M4"
    };
    
    const int MIDI_NOTES [16] = {
        36,37,38,39,
        40,41,42,43,
        44,45,46,47,
        48,49,50,51
    };
    
    const vector<string> mode = {
        "Mode : Manual",
        "Mode : EUCLID",
        "Mode : COMP"};
    const vector<string> note = {
        "Quaver", "Triplets", "Semi-Quaver","Quintuplet","Sextuplet","Septuplet"
    };
    
    ofEvent<Controls>GuiCallback;
    ofEvent<int>sendPitch;
    
    ofxDatGui *ptr;
    Controls seq_Params;

    ofPoint pos;
    bool bEuclid, bEnabled, bComp;
    int index, seq_len, seq_pulse, beatPerBar;
    int max_len;
    int width;
    
    string currentNote;
    vector<string>notes;
    string name;
    
    vector<DatGuiPtr>components;
    vector<DatGuiPtr>compSet;
    vector<DatSliderPtr>sliders;
    INF_Controls();
    ~INF_Controls();
    void setup();
    void setComp(ofPoint p);
    void update();
    void draw();
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onNoteSelection(ofxDatGuiDropdownEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void setSliders(int length, int pulse);
    void setLength(int length);
    void setMax(int max);
    int getWidth();
    int getHeight();
};