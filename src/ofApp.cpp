

#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    cout<<"[Infinite Machine ALPHA.v02]"<<endl;
    ofBackground(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("Infinite Machine");
    
    //Upper dock
    docks = new Dat_Docker(midi->midiOut.getPortList());
    ofAddListener(docks->deviceState, this, &ofApp::MIDICallback);//add EventListener.
    ofAddListener(docks->modeChange, this, &ofApp::setMode);
    //Lower Transport dock Init
    transport = unique_ptr<INF_Transport>(new INF_Transport());
    transport->pos = ofPoint(0,754);
    transport->setup();
    transport->setTimeSignature(4, 4);
    timeSignature = "4/4";
    ofAddListener(transport->ClockCallback, this, &ofApp::globalState);
    bHost = false; //add GUI for this parameter.
    isPlay = false;
    if(bHost){
        transport->tempoSlider->setEnabled(true);
        transport->text->setEnabled(true);
        transport->tempoSlider->setValue(120);
        setTempo(120); //as long as it works as master mode. the initial tempo is 120. or it takes Tempo from Master(Ableton Live)
        tempo = 120;
    }else{
        transport->tempoSlider->setEnabled(false);
        transport->text->setEnabled(false);
    }

    //MIDI Initialization
    midi = new INF_MIDI();
    
    //Sequencer
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

    //Audio Setup
    ofSoundStreamSetup(2, 0, this, SRATE, BUFFER_SIZE, 4);
}
//--------------------------------------------------------------
void ofApp::update(){
    if(bHost)
        oscListener.update(); //Listening OSC...
    
    
    accents.resize(playHeadAmt);
    for(int i=0; i != playHeadAmt; i++){
        if(i % divisor == 0){//find strong beat and weak beats
            accents.at(i) = 1;
        }else{
            accents.at(i) = 0;
        }
    }
    
    module->update();
    docks->update();
    transport->update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    module->draw();
    transport->draw();
    
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
    
    
    ofSetColor(255);
    stringstream text2;
    text2 << "Tempo " << tempo <<endl
    << "is playing?: " << isPlay << endl << endl
    << "Time Signature :"<< timeSignature << endl << endl
    << "Current Beat " << currentBeat << "/"<< currentBar << endl
    << "Beatgrid : " << beatGrid<<endl;
    ofDrawBitmapString(text2.str(), 20, 240);
    
    
    
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
    for(int i = 0; i < bufferSize; i++){
        
        if(isPlay)
            currentCount=(int)timer.phasor(bps);
        
        if (lastCount!=currentCount) {
            //iterate the playhead
            if(playHead <playHeadAmt-1)
                playHead++;
            else
                playHead = 0;
            
            for(auto &x: module->tracks){
                //Create Note ON/OFF Pair
                if(x->pattern.at(playHead%playHeadAmt) == true){
                    unique_ptr<Note> n = unique_ptr<Note>(new Note());
                    n->status = KEY_ON;
                    n->pitch = x->pitch;
                    n->velocity = 127;
                    midi->sendNote(*n);
                }else{
                    unique_ptr<Note> n = unique_ptr<Note>(new Note());
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
    tempo = eventArgs.tempo;
    currentBar = eventArgs.bar;
    currentBeat = eventArgs.beat;
    isPlay = eventArgs.isPlay;
    
    timeSignature = to_string(eventArgs.meter.beatPerBar) + "/" + to_string(eventArgs.meter.beatResolution);
    if(isPlay)
        transport->setTimeSignature(eventArgs.meter.beatResolution, eventArgs.meter.beatPerBar);
    
    divisor = eventArgs.meter.beatResolution;
    if(eventArgs.meter.beatResolution == 4){
        playHeadAmt = eventArgs.meter.beatPerBar * 4; //calculate the amount of semi-crochet per bar.
    }else if(eventArgs.meter.beatResolution == 8){
        playHeadAmt = eventArgs.meter.beatPerBar * 2;
    }else if(eventArgs.meter.beatResolution == 16){
        playHeadAmt = eventArgs.meter.beatPerBar;
    }
}
//--------------------------------------------------------------
void ofApp::MIDICallback(MidiState &eventArgs){
    //receive list index from GUI
    midi->setDevice(eventArgs.device);
    midi->channel = eventArgs.channel+1;
    cout<<"Bam"<<endl;
}
//--------------------------------------------------------------
void ofApp::globalState(TransportMessage &eventArgs){
    
}
//--------------------------------------------------------------
void ofApp::setMode(bool &eventArgs){
    if(eventArgs){
        bHost = false;
        cout<<"[Slave Mode is Activated]"<<endl;
    }else{
        bHost = true;
        
        cout<<"[Master Mode is Activated]"<<endl;
    }
    transport->tempoSlider->setEnabled(bHost);
    transport->components[0]->setEnabled(bHost);
}
//--------------------------------------------------------------
void ofApp::tempoChange(int &eventArgs){
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    //delete raw pointers
    delete midi;
    delete docks;
    //and smart pointers
    module.reset();
    transport.release();

    cout<<"[Infinite Machine : Goodbye.]"<<endl;
}
