//
//  INF_Controls.cpp
//  DatGui_Chunk
//
//  Created by Heewon Oh on 07/07/2016.
//
//

#include "INF_Controls.hpp"

INF_Controls::INF_Controls():bEuclid(1), bEnabled(false),name("Sequence"),index(0),seq_len(16),seq_pulse(4){
    //Create midi note array...
    int octave;//octave is 0 - 8;
    for(int noteNum=0; noteNum<=108;noteNum++){
        octave = noteNum /12;
        notes.push_back(note_substring[noteNum%12]+to_string(octave));
    }
    
}
//--------------------------------------------------------------
INF_Controls::~INF_Controls(){
    for(auto &x:components)
        x.reset();
    components.clear();
    for(auto &x:sliders)
        x.reset();
    sliders.clear();
    delete ptr;
}
//--------------------------------------------------------------
void INF_Controls::setup(){
    //Initialize Event Parameters
    seq_Params.index = index;
    seq_Params.mode = bEuclid;
    seq_Params.isOn = bEnabled;//checks whether Sequencer's mode is Euclidean or Step Sequencer...
    
    string label_ = name + " " +to_string(index+1);
    shared_ptr<ofxDatGuiLabel> label = shared_ptr<ofxDatGuiLabel>(new ofxDatGuiLabel(label_));
    label->setPosition(pos.x, pos.y);
    label->setWidth(210);
    width = label->getWidth();
    components.push_back(label);
    
    shared_ptr<ofxDatGuiToggle> on = shared_ptr<ofxDatGuiToggle>(new ofxDatGuiToggle("", bEnabled));
    on->setPosition(pos.x+label->getWidth(), pos.y);
    on->setStripeVisible(false);
    on->ofxDatGuiComponent::setWidth(60, 20);
    on->onToggleEvent(this, &INF_Controls::onToggleEvent);
    components.push_back(on);
    
    
    //Sequencer Mode
    pos.y += label->getHeight();
    shared_ptr<ofxDatGuiDropdown> d = shared_ptr<ofxDatGuiDropdown>(new ofxDatGuiDropdown("Mode", mode));
    d->setPosition(pos.x, pos.y);
    d->select(1);
    d->onDropdownEvent(this, &INF_Controls::onDropdownEvent);
    components.push_back(d);

    pos.y += d->getHeight();
    shared_ptr<ofxDatGuiSlider> s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("STEP", 4,16));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(seq_len);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    sliders.push_back(s);
    
    //PULSES
    pos.y += s->getHeight();
    s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("PULSES", 0,seq_len));
    if(bEuclid)
        s->setMin(1);
    else
        s->setMin(0);
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(seq_pulse);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    sliders.push_back(s);
    
    //OFFSET
    pos.y += s->getHeight();
    s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("OFFSET", 0, 15));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(0);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    sliders.push_back(s);
    
    //Timespan
    pos.y += s->getHeight();
    s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("TICKS", 2,4));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(4);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    sliders.push_back(s);
    
    //NOTE Selection.
    //instead of picking pitch from slider, I use dropdown.
    pos.y += s->getHeight();
    ptr = new ofxDatGui(pos.x, pos.y);
    ptr->addDropdown("MIDI NOTE", AbletonDrumMap);
    ptr->addBreak();
    ptr->onSliderEvent(this, &INF_Controls::onSliderEvent);
    ptr->onDropdownEvent(this, &INF_Controls::onNoteSelection);
    
    
        ofColor randC = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
        for(auto &x:components)
            x->setStripe(randC, 2);
        for(auto &x:sliders)
            x->setStripe(randC, 2);
        for(auto &x:compSet)
            x->setStripe(randC, 2);
}
//--------------------------------------------------------------
void INF_Controls::setComp(ofPoint p){
    ofPoint pos;
    pos = p;
    vector<string>target;
    target.reserve(8);
    for(int i=1;i <= 8;i++)//populate string
        target.push_back(to_string(i));
    shared_ptr<ofxDatGuiDropdown> d = shared_ptr<ofxDatGuiDropdown>(new ofxDatGuiDropdown("Target", target));
    d->setPosition(pos.x, pos.y);
    compSet.push_back(d);
    
    //MIDI NOTE
    pos.y += d->getHeight();
    shared_ptr<ofxDatGuiSlider> s = shared_ptr<ofxDatGuiSlider>(new ofxDatGuiSlider("MIDI NOTE", 12,108));
    s->setPrecision(0);
    s->setPosition(pos.x, pos.y);
    s->setValue(12);
    s->onSliderEvent(this, &INF_Controls::onSliderEvent);
    compSet.push_back(s);
}
//--------------------------------------------------------------
void INF_Controls::update(){
    if(!currentNote.empty()) components[3]->setLabel(currentNote);
    
    for(auto &x:components){
        x->update();
        if(x->getIsExpanded()){//avoiding clicking overlay. seems bit unorthodox but this is the only way out.
            for(auto &x: sliders)
                x->setEnabled(false);
        }
    }
    
    if(!bComp){
        for(auto &x:sliders){
            x->update();
            if(x->getLabel()=="PULSES"){
                if(x->getValue() >seq_len)
                    x->setValue(seq_len);
            }
        }
    }else{
        for(auto &x:compSet)
            x->update();
    }

}
//--------------------------------------------------------------
void INF_Controls::draw(){
    if(!bComp){
        
    }
    for(auto &x:sliders)
        x->draw();
    for(auto &x:components)
        x->draw();
    
//    if(bComp == true)
//        for(auto &x:compSet)
//            x->draw();
    ptr->draw();
}
//--------------------------------------------------------------
void INF_Controls::onToggleEvent(ofxDatGuiToggleEvent e){
    for(auto &x:sliders)
        x->setEnabled(e.checked);
    if(e.checked == false){
        seq_Params.index = index;
        seq_Params.length = 0;
        seq_Params.pulse = 0;
        seq_Params.isOn = e.checked;
        ofNotifyEvent(GuiCallback, seq_Params, this);
        
    }else{
        seq_Params.index = index;
        seq_Params.length = seq_len;
        seq_Params.pulse = seq_pulse;
        seq_Params.isOn = e.checked;
            sliders[0]->setValue(seq_len);
            sliders[1]->setValue(seq_pulse);
        ofNotifyEvent(GuiCallback, seq_Params, this);
    }
    //send Sequencer state
    seq_Params.index = index;
    seq_Params.isOn = e.checked;
    ofNotifyEvent(GuiCallback, seq_Params, this);
    bEnabled = e.checked;
}
//--------------------------------------------------------------
void INF_Controls::onDropdownEvent(ofxDatGuiDropdownEvent e){
    
    if(e.target->ofxDatGuiComponent::getIsExpanded()){
        cout<<"Expand!"<<endl;//this never be caught up
        
    }else{
        //avoiding clicking overlay.
        //somehow DatGuiDropdown checks this one.
        for(auto &x: sliders)
            x->setEnabled(true);
    }

    if(e.child ==0){
        //IF MODE is changed to Manual mode..
        bEuclid = false;
        bComp = false;
        sliders[1]->setMin(0);
        sliders[1]->setEnabled(false); //pulse slider is disabled.
        sliders[1]->setValue(0);
    }else if(e.child ==1){
        //Euclidean Mode
        bEuclid = true;
        bComp = false;
        sliders[1]->setEnabled(bEuclid);
        sliders[0]->setValue(seq_len);
        sliders[1]->setValue(seq_pulse);
        sliders[1]->setMin(1);
    }else if(e.child ==2){
        bComp = true;
        setComp(pos);
    }
    //send Sequencer mode
    seq_Params.index = index;
    seq_Params.mode = e.child;
    ofNotifyEvent(GuiCallback, seq_Params, this);
    
}
//--------------------------------------------------------------
void INF_Controls::onNoteSelection(ofxDatGuiDropdownEvent e){
    string selection = AbletonDrumMap.at(e.child);
    seq_Params.pitch = MIDI_NOTES[e.child];
    ofNotifyEvent(GuiCallback, seq_Params, this);
}
//--------------------------------------------------------------
void INF_Controls::onSliderEvent(ofxDatGuiSliderEvent e){
    
    if(e.target->getLabel() =="STEP"){
        seq_len = e.value;
        seq_Params.length = seq_len;
        sliders[1]->setMax(e.value);
        sliders[2]->setMax(e.value-1);
    }else if(e.target->getLabel() =="PULSES"){
        ofLogNotice()<<e.value;
        seq_pulse = e.value;
        seq_Params.pulse = seq_pulse;
    }else if(e.target->getLabel() =="OFFSET"){
        seq_Params.offset = e.value;
    }else if(e.target->getLabel() =="TICKS"){
        seq_Params.length = e.value * 4;
    }
    ofNotifyEvent(GuiCallback, seq_Params, this);
}
//--------------------------------------------------------------
void INF_Controls::setSliders(int length, int pulse){
    
    for(auto &x:sliders){
        if(x->getLabel() == "STEP"){
            x->setValue(length);
        }else if(x->getLabel() == "PULSES"){
            x->setValue(pulse);
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
//--------------------------------------------------------------
void INF_Controls::setMax(int max){
    max_len = max;
    for(auto &x:sliders){
        x->setMax(max_len);
    }
    seq_Params.length = max_len;
    ofNotifyEvent(GuiCallback, seq_Params, this);
}
//--------------------------------------------------------------
int INF_Controls::getWidth(){
    return width;
}
//--------------------------------------------------------------
int INF_Controls::getHeight(){
    int cHeight = components[0]->getHeight(); //components height (all datgui's size are same. so I borrow this
    
    int sum = (components.size()+sliders.size()) * cHeight;
    
    return sum;
}



