#pragma once

#include "ofxDatGui.h"
#include "ofMain.h"
using namespace std;

struct Controls{
    
    int index, length, pulse, pitch, velocity, offset;
    Controls():index(0){
        
    };
    
};

typedef shared_ptr<ofxDatGuiComponent> DatGuiPtr;
typedef shared_ptr<ofxDatGuiSlider> DatSliderPtr;
//typedef unique_ptr<ofxDatGuiComponent> DatGuiPtr_;
class INF_Controls{
public:
    
    ofEvent<Controls>GuiCallback;
    
    ofPoint pos;
    bool bEuclid;
    int index, seq_len, seq_pulse;
    int noteIndex;
    int width, heightSum;
    
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
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void setEuclid(int length, int pulse);
    void setLength(int length);
    int getWidth(){return width;};
    int getHeight(){return heightSum;};
};