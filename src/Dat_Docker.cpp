//
//  Dat_Docker.cpp
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#include "Dat_Docker.h"

ofEvent<int> Dat_Docker::deviceFocusGlobal = ofEvent<int>();
ofEvent<int> Dat_Docker::midiChGlobal = ofEvent<int>();

Dat_Docker::Dat_Docker(vector<string>&deviceList):list(deviceList), width(0), deviceNum(0){
    
    //MODE Selecter
    vector<string> mode = {"MIDI", "OSC"};
    DatDropdown *d;
    d = new DatDropdown("MODE", width, 0, mode);
    d->menus->onDropdownEvent(this, &Dat_Docker::modeChanged);
    d->setWidth(75);
    midi_lists.push_back(d);
    
    //MIDI Device list
    width += d->getWidth();
    d = new DatDropdown("MIDI Devices", width, 0, list);
    d->menus->onDropdownEvent(this, &Dat_Docker::selectDevice);
    midi_lists.push_back(d);
    
    //MIDI Channel
    width += d->getWidth();
    for(int i=1;i <= 16;i++)//populate string
        ch.push_back(to_string(i));
    
    d = new DatDropdown("Ch.", width, 0, ch);
    d->menus->onDropdownEvent(this, &Dat_Docker::selectChannel);
    d->setWidth(50);
    midi_lists.push_back(d);
    
    //MIDI STATUS REFRESH
    width += d->getWidth();
    ofxDatGuiButton *refresh = new ofxDatGuiButton("Refresh");
    refresh->setPosition(width, 0);
    refresh->setWidth(74);
    refresh->onButtonEvent(this, &Dat_Docker::deviceRefresh);
    components.push_back(refresh);
    
    width += refresh->getWidth();
    ofxDatGuiLabel *label = new ofxDatGuiLabel("Pages :");
    label->setPosition(width, 0);
    label->setWidth(68);
    components.push_back(label);
    
    width += label->getWidth();
    browser = new DatIndex(width,0);
    browser->setup();
    
    //BPM SLIDER
    width += browser->getWidth()+210;
    ofxDatGuiSlider* bpmSlider = new ofxDatGuiSlider("BPM", 40, 240);
    bpmSlider->setPosition(width, 0);
    bpmSlider->setWidth(200, 50);
    bpmSlider->setPrecision(0);
    bpmSlider->setValue(130);
    bpmSlider->onSliderEvent(this, &Dat_Docker::bpmChanged);
    components.push_back(bpmSlider);
    
    //STOP Button
    width += bpmSlider->getWidth();
    ImageButton *b = new ImageButton("stop.png", "Stop");
    b->setPosition(width, 0);
    b->setSize(25);
    ofAddListener(b->buttonClicked, this, &Dat_Docker::customButtonEvent);
    
    buttons.push_back(b);
    
    width += b->getWidth();
    b = new ImageButton("play.png", "Play");
    b->setPosition(width, 0);
    b->setSize(25);
    ofAddListener(b->buttonClicked, this, &Dat_Docker::customButtonEvent);
    buttons.push_back(b);

        width += b->getWidth();
}
void Dat_Docker::update(){
    browser->update();
    //component search
    for(auto x:midi_lists) x->update();
    //ofxDatGui Components
    for(auto x:components) x->update();
}
void Dat_Docker::draw(){
    browser->render();
    for(auto x:buttons) x->render();
    for(auto x:midi_lists) x->render();
    //ofxDatGui Components
    for(auto x:components) x->draw();
}
void Dat_Docker::getDeviceList(vector<string> &v){
    list = v;
    //call the index number of vector and call callbacks to take it.
}
void Dat_Docker::selectDevice(ofxDatGuiDropdownEvent e){
    //eventArgs sender
    deviceNum = e.child;
    ofNotifyEvent(deviceFocus, deviceNum, this);//notify event to ofApp
    ofNotifyEvent(deviceFocusGlobal, deviceNum);
};
void Dat_Docker::selectChannel(ofxDatGuiDropdownEvent e){
    int midiCh = e.child;
    ofNotifyEvent(channelChanged, midiCh, this);
    ofNotifyEvent(midiChGlobal, midiCh);
}
void Dat_Docker::deviceRefresh(ofxDatGuiButtonEvent e){
    cout<<e.target->getLabel()<<endl;
    bool t = false;
    if(e.target->getLabel() == "REFRESH")
        t = true;
    ofNotifyEvent(deviceRefreshed, t, this);
}
void Dat_Docker::customButtonEvent(customEvent &e){
    cout<<e.label<<endl;

}
void Dat_Docker::pageAdded(ofxDatGuiButtonEvent e){
    cout<<e.target->getLabel()<<endl;
}
