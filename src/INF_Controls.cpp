//
//  INF_Controls.cpp
//  DatGui_Chunk
//
//  Created by Heewon Oh on 07/07/2016.
//
//

#include "INF_Controls.hpp"

INF_Controls::INF_Controls():bEuclid(1),name("Sequence"),index(0),seq_len(16),seq_pulse(4){
    //Create midi note array...
    const string note_substring[] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    int octave;//octave is 0 - 8;
    for(int noteNum=0; noteNum<=108;noteNum++){
        octave = noteNum /12;
        notes.push_back(note_substring[noteNum%12]+to_string(octave));
    }
}
//--------------------------------------------------------------
INF_Controls::~INF_Controls(){
    components.clear();
}
//--------------------------------------------------------------
void INF_Controls::setup(){
    
    string label_ = name + " " +to_string(index+1);
    shared_ptr<ofxDatGuiLabel> label = shared_ptr<ofxDatGuiLabel>(new ofxDatGuiLabel(label_));
    label->setPosition(pos.x, pos.y);
    width = label->getWidth();
    heightSum += label->getHeight();
    components.push_back(label);
    
    //STEP
    pos.y += label->getHeight();
    shared_ptr<ofxDatGuiSlider> s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("Step", 4,16));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(seq_len);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    heightSum += s->getHeight();
    sliders.push_back(s);
    
    //PULSES
    pos.y += s->getHeight();
    s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("Pulses", 1,seq_len));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(seq_pulse);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    heightSum += s->getHeight();
    sliders.push_back(s);
    
    //OFFSET
    pos.y += s->getHeight();
    s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("OFFSET", 0, 16));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(0);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    heightSum += s->getHeight();
    sliders.push_back(s);
    
    //MIDI NOTE
    pos.y += s->getHeight();
    s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("MIDI NOTE", 12,108));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(12);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    heightSum += s->getHeight();
    sliders.push_back(s);

    
    //VELOCITY
    pos.y += s->getHeight();
    s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("Velocity", 1,127));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(80);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    heightSum += s->getHeight();
    sliders.push_back(s);
    
    //Current NOTE in string
    pos.y += s->getHeight();
    label = shared_ptr<ofxDatGuiLabel>(new ofxDatGuiLabel("Current Note :: C1"));
    label->setPosition(pos.x, pos.y);
    heightSum += label->getHeight();
    components.push_back(label);
    
//    pos.y += s->getHeight();
//    vector<string>mode = {"STEP", "EUCLID"};
//    shared_ptr<ofxDatGuiDropdown> d = shared_ptr<ofxDatGuiDropdown>(new ofxDatGuiDropdown("Mode", mode));
//    d->setPosition(pos.x, pos.y);
//    d->onDropdownEvent(this, &INF_Controls::onDropdownEvent);
//    heightSum += d->getHeight();
//    components.push_back(d);
    
        ofColor randC = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
        for(auto &x:components)
            x->setStripe(randC, 2);
        for(auto &x:sliders)
            x->setStripe(randC, 2);

}
//--------------------------------------------------------------
void INF_Controls::update(){
    if(!currentNote.empty()) components[1]->setLabel(currentNote);
    
    for(auto &x:components)
        x->update();
    for(auto &x:sliders){
        x->update();
        if(x->getLabel()=="PULSES"){
            if(x->getValue() >seq_len)
                x->setValue(seq_len);
        }
    }
    
}
//--------------------------------------------------------------
void INF_Controls::draw(){
    for(auto &x:components)
        x->draw();
    for(auto &x:sliders)
        x->draw();
    
}
//--------------------------------------------------------------
void INF_Controls::onDropdownEvent(ofxDatGuiDropdownEvent e){
    if(e.child ==0){
        bEuclid = false;

    }else if(e.child ==1){
        bEuclid = true;
    }
    sliders[1]->setEnabled(bEuclid);

}
//--------------------------------------------------------------
void INF_Controls::onSliderEvent(ofxDatGuiSliderEvent e){
    Controls newSeq;
    newSeq.index = index;
    
    if(e.target->getLabel() == "MIDI NOTE"){
        string msg = "Current Note :: ";
        currentNote = msg +notes[e.value];
        newSeq.pitch =e.value+24;
        newSeq.pulse = seq_pulse;
        newSeq.length = seq_len;
    }else if(e.target->getLabel() == "VELOCITY"){
        newSeq.index = index;
        newSeq.pulse = seq_pulse;
        newSeq.length = seq_len;
        newSeq.velocity = e.value;
    }else if(e.target->getLabel() =="STEP"){
        seq_len = e.value;
        newSeq.length = e.value;
        newSeq.pulse = seq_pulse;
    }else if(e.target->getLabel() =="PULSES"){
        seq_pulse = e.value;
        newSeq.length = seq_len;
        newSeq.pulse = e.value;
    }else if(e.target->getLabel() =="OFFSET"){
        newSeq.offset = e.value;
        newSeq.pulse = seq_pulse;
        newSeq.length = seq_len;
    }
    ofNotifyEvent(GuiCallback, newSeq, this);
    
}
//--------------------------------------------------------------
void INF_Controls::setEuclid(int length, int pulse){
    if(length > seq_pulse){
        seq_len = length;
    }else{
        seq_len = seq_pulse;
    }
    for(auto &x:sliders){
        if(x->getLabel() == "STEP"){
            x->setValue(seq_len);
        }
    }
    if(pulse < seq_len){
        seq_pulse = pulse;
    }else{
        seq_pulse = seq_len;
    }
    for(auto &x:sliders){
        if(x->getLabel() == "PULSES"){
            x->setValue(seq_pulse);
        }
    }
}
//--------------------------------------------------------------
void INF_Controls::setLength(int length){
    seq_len = length;
    for(auto &x:sliders){
        if(x->getLabel() == "STEP"){
            x->setValue(seq_len);
        }
    }
}




