

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    cout<<"[Infinite Machine ALPHA.v02]"<<endl;
    ofBackground(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("Infinite Machine");
    
    //MIDI Initialization
    midi = new INF_MIDI();

    //Upper dock
    docks = new Dat_Docker(midi->midiOut.getPortList());
    //add EventListener.
    ofAddListener(docks->deviceFocus, this, &ofApp::deviceSelected);
    ofAddListener(docks->channelChanged, this, &ofApp::MIDI_ch_changed);
    ofAddListener(docks->tempoChange, this, &ofApp::tempoChange);
//    ofAddListener(docks->customButtonEvent, this, &ofApp::seqStart);
    
    //Networking components
    midi->midiOut.listPorts();
    oscListener.setup();
    ofAddListener(oscListener.AbletonPlayed, this, &ofApp::AbletonPlayed);
    
    //default IP:PORT Address
    string netAddress;
    stringstream convert;
    convert << " : " <<PORT;
    netAddress = HOST + convert.str();
    ip_adrs = HOST;
    port_adrs = PORT;
    
    //Sequencer init
    module = unique_ptr<INF_Module>(new INF_Module(0));
    module->pos = ofPoint(30, docks->getHeight()+12);
    module->setup();
    
    
    int a = 8; int b = 3;
    try {
        Sequencer *seq = new Sequencer(a,b);
        INF_seq.push_back(seq);
    } catch (exception e) {
        cerr<<"[Sequencer Initilization] Exception has been thrown "<<ofGetElapsedTimef()<<endl;
        cout<<e.what()<<endl;
    }
    vector<bool>seq;
    seq.resize(12);
    seq=
       {1,0,0,0,
        0,1,1,1,
        0,1,0,0};

    //Audio Setup
    ofSoundStreamSetup(2, 0, this, SRATE, BUFFER_SIZE, 4);
}
//--------------------------------------------------------------
void ofApp::update(){
//    ofSetWindowShape(docks->getWidth(), 768);

    for(int i=0;i<docker.size();i++){
        docker[i]->update();
    }
    module->update();
    docks->update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    module->draw();
    // let's see something
    ofSetColor(255);
    stringstream text;
    text << "connected to port " << midi->midiOut.getPort()
    << " \"" << midi->midiOut.getName() << "\"" << endl
    << "is virtual?: " << midi->midiOut.isVirtual() << endl << endl
    << "sending to channel " << midi->channel << endl << endl
    << "note: " << midi->note << endl
    << "velocity: " << midi->velocity << endl;
    ofDrawBitmapString(text.str(), 20, 60);
    
    
    module->draw();
    
    //ofxDatGui components
    ofPushStyle();
    ofSetColor(255, 255, 255);
    docks->draw();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    int index = INF_seq.size();
    for(int i = 0; i < bufferSize; i++){
        clock.ticker(start);
        for(int i=0;i < index;++i){
            
            try {
                INF_seq.at(i)->play(start);
                trigger = INF_seq.at(i)->trigger();
            } catch (exception e) {
                cout<<e.what()<<endl;
            }
            
        }
        //THIS DOES NOT SEND ANY AUDIO SIGNAL.
    }
}
//--------------------------------------------------------------
void ofApp::deviceSelected(int &eventArgs){
    //receive list index from GUI
    midi->setDevice(eventArgs);
}
//--------------------------------------------------------------
void ofApp::MIDI_ch_changed(int &eventArgs){
    midi->channel = eventArgs+1;
    cout<<"Channel : "<<eventArgs+1<<endl;
}
//--------------------------------------------------------------
void ofApp::tempoChange(int &eventArgs){
    clock.setTempo(eventArgs);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //MIDINOTE SENDER TEST
    
    // send a note on if the key is a letter or a number
    if(isalnum((unsigned char) key)) {
        
        // scale the ascii values to midi velocity range 0-127
        // see an ascii table: http://www.asciitable.com/
        int _note = ofMap(key, 48, 122, 0, 127);
        int _velocity = 127;
        
        n = new Note();
        n->status = KEY_ON;
        n->pitch =_note;
        n->velocity = _velocity;
        midi->sendNote(*n);
    }

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(isalnum((unsigned char) key)) {
        // scale the ascii values to midi velocity range 0-127
        // see an ascii table: http://www.asciitable.com/
        int _note = ofMap(key, 48, 122, 0, 127);
        int _velocity = 0;
        
        n = new Note();
        n->status = KEY_OFF;
        n->pitch =_note;
        n->velocity = 0;
        midi->sendNote(*n);
    }

}
//--------------------------------------------------------------
void ofApp::AbletonPlayed(Ableton &eventArgs){
    tempo = eventArgs.tempo;
    currentBar = eventArgs.bar;
    currentBeat = eventArgs.beat;
    start = eventArgs.isPlay;
}
//--------------------------------------------------------------
void ofApp::exit(){
    //delete raw pointers
    delete midi;
    delete docks;
    module.reset();
    
    for_each(INF_seq.begin(), INF_seq.end(), DeleteVector<Sequencer*>());
    cout<<"[Infinite Machine : Goodbye.]"<<endl;
}
