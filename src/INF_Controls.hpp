#pragma once

#include "ofxDatGui.h"
#include "ofMain.h"
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
    
    ofEvent<Controls>GuiCallback;    
    Controls seq_Params;

    ofPoint pos;
    bool bEuclid, bEnabled;
    int index, seq_len, seq_pulse;
    int width;
    
    string currentNote;
    vector<string>notes;
    string name;
    
    vector<DatGuiPtr>components;
    vector<DatSliderPtr>sliders;
    INF_Controls();
    ~INF_Controls();
    void setup();
    void update();
    void draw();
    void onToggleEvent(ofxDatGuiToggleEvent e);
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void setSliders(int length, int pulse);
    void setLength(int length);
    int getWidth();
    int getHeight();
};