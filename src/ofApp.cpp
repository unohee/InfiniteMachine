

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
    //Sequencer GUI
    module = unique_ptr<INF_Module>(new INF_Module(0));
    module->pos = ofPoint(0, docks->getHeight());
    module->setup();
    
    
    //default IP:PORT Address
    string netAddress;
    stringstream convert;
    convert << " : " <<PORT;
    netAddress = HOST + convert.str();
    ip_adrs = HOST;
    port_adrs = PORT;
    
    //Networking components
    midi->midiOut.listPorts();
    oscListener.setup();
    ofAddListener(oscListener.AbletonPlayed, this, &ofApp::AbletonPlayed);

    isPlay = true;
    setTempo(120); //as long as it works as master mode. the initial tempo is 120.
    
    //Audio Setup
    ofSoundStreamSetup(2, 0, this, SRATE, BUFFER_SIZE, 4);
}
//--------------------------------------------------------------
void ofApp::update(){
//    ofSetWindowShape(module->getWidth()*2, 768);
    for(int i=0;i<docker.size();i++){
        docker[i]->update();
    }
    module->update();
    docks->update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    module->draw();
    
    /*
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
    */
    
    //ofxDatGui components
    ofPushStyle();
    ofSetColor(255, 255, 255);
    docks->draw();
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::setTempo(float BPM){
    bps = BPM / 60.f * 4;
};
//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    int index = INF_seq.size();
    for(int i = 0; i < bufferSize; i++){
        
        if(isPlay)
            currentCount=(int)timer.phasor(bps);
        
        if (lastCount!=currentCount) {//if we have a new timer int this sample, play the sound
            
            
            //iterate the playhead
            if(playHead <15)
                playHead++;
            else
                playHead = 0;
            
            int step_arr[]={1,0,0,0,1,0,0};
            
            for(auto &x: module->tracks){
                unique_ptr<Note> n = unique_ptr<Note>(new Note());
                if(x->pattern.at(playHead%16) == true){
                    n->status = KEY_ON;
                    n->pitch = 36;
                    n->velocity = 127;
                    midi->sendNote(*n);
                }else{
                    n->status = KEY_OFF;
                    n->pitch = 36;
                    n->velocity = 0;
                    midi->sendNote(*n);
                }
            }

            lastCount=0;//reset the metrotest
            
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
        
//        n = new Note();
//        n->status = KEY_ON;
//        n->pitch =_note;
//        n->velocity = _velocity;
//        midi->sendNote(*n);
    }

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(isalnum((unsigned char) key)) {
        // scale the ascii values to midi velocity range 0-127
        // see an ascii table: http://www.asciitable.com/
        int _note = ofMap(key, 48, 122, 0, 127);
        int _velocity = 0;
        
//        n = new Note();
//        n->status = KEY_OFF;
//        n->pitch =_note;
//        n->velocity = 0;
//        midi->sendNote(*n);
    }

}
//--------------------------------------------------------------
void ofApp::AbletonPlayed(Ableton &eventArgs){
    //Add something more here
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
