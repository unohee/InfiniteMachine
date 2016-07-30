//
//  Dat_Docker.cpp
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#include "Dat_Docker.h"

Dat_Docker::Dat_Docker(vector<string>&deviceList):list(deviceList), deviceNum(0){
    
    int gWidth = 200; //gui Width
    
    //MIDI DEVICE
    shared_ptr<ofxDatGuiDropdown> drop = shared_ptr<ofxDatGuiDropdown>(new ofxDatGuiDropdown("DEVICE", list));
    drop->onDropdownEvent(this, &Dat_Docker::selectDevice);
    drop->setWidth(gWidth);
    drop->setPosition(pos.x, pos.y);
    deviceGUI.push_back(drop);
    
    //MIDI Channel
    pos.x += drop->getWidth();
    for(int i=1;i <= 16;i++)//populate string
        ch.push_back(to_string(i));
    
    drop = shared_ptr<ofxDatGuiDropdown>(new ofxDatGuiDropdown("MIDI Channel", ch));
    drop->onDropdownEvent(this, &Dat_Docker::selectChannel);
    drop->setWidth(gWidth);
    drop->setPosition(pos.x, pos.y);
    deviceGUI.push_back(drop);
    
    pos.x += drop->getWidth();
    static vector<string> mode = {"Master", "Slave"};
    drop = shared_ptr<ofxDatGuiDropdown>(new ofxDatGuiDropdown("Mode", mode));
    drop->onDropdownEvent(this, &Dat_Docker::modeChanged);
    drop->setWidth(gWidth);
    drop->setPosition(pos.x, pos.y);
    deviceGUI.push_back(drop);

    //Module pages
    pos.x += drop->getWidth();
    ofxDatGuiLabel *label = new ofxDatGuiLabel("Pages :");
    height = label->getHeight();
    label->setPosition(pos.x, pos.y);
    label->setWidth(240);
    components.push_back(label);

    pos.x += label->getWidth();
    browser = new DatIndex(pos.x,0);
    browser->setup();
    width += browser->getWidth()+210;
    
}
//--------------------------------------------------------------
void Dat_Docker::update(){
    browser->update();
    for(auto &x:deviceGUI) x->update();
    //ofxDatGui Components
    for(auto x:components) x->update();
}
//--------------------------------------------------------------
void Dat_Docker::draw(){
    browser->render();
    for(auto &x:deviceGUI) x->draw();
    //ofxDatGui Components
    for(auto &x:components) x->draw();
}
//--------------------------------------------------------------
void Dat_Docker::getDeviceList(vector<string> &v){
    list = v;
    //call the index number of vector and call callbacks to take it.
}
//--------------------------------------------------------------
void Dat_Docker::selectDevice(ofxDatGuiDropdownEvent e){
    //eventArgs sender
    cout<<"Midi Devices"<<endl;
    midiParam.device = e.child;
    ofNotifyEvent(deviceState, midiParam, this);
}
//--------------------------------------------------------------
void Dat_Docker::selectChannel(ofxDatGuiDropdownEvent e){
    midiParam.channel = e.child;
    ofNotifyEvent(deviceState, midiParam, this);
}
//--------------------------------------------------------------
void Dat_Docker::pageAdded(ofxDatGuiButtonEvent e){
    cout<<e.target->getLabel()<<endl;
}
