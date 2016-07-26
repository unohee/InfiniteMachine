//
//  INF_Transport.h
//  Infinite_Machine_Alpha
//
//  Created by Heewon Oh on 26/07/2016.
//
//

#ifndef INF_Transport_h
#define INF_Transport_h

#include "ofxDatGui.h"
#include "ofMain.h"

typedef shared_ptr<ofxDatGuiComponent> DatGuiPtr;

struct Meter{
    int beat;
    int beatPerBar;
};

class INF_Transport{
public:
    vector<DatGuiPtr> components;
    ofPoint pos;
    INF_Transport();
    ~INF_Transport();

    int width;
    
    void setup();
    void update();
    void draw();
    void setTimeSignature(int beat, int amount);
    
};

#endif /* INF_Transport_h */
