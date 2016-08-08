

#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    cout<<"[Infinite Machine ALPHA.v02]"<<endl;
    ofBackground(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("Infinite Machine");
    
    //Upper dock
    docks = new Dat_Docker(midi.midiOut.getPortList());
    ofAddListener(docks->deviceState, this, &ofApp::MIDICallback);//add EventListener.
    ofAddListener(docks->modeChange, this, &ofApp::setMode);
    
    
    //Transport Control..
    transport = unique_ptr<INF_Transport>(new INF_Transport());
    transport->pos = ofPoint(0,754);
    transport->setup();
    transport->setTimeSignature(4, 4);
    timeSignature = "4/4";
    ticksPerBeat = 4;
    tempo = 120;
    bps = (tempo / 60.) * ticksPerBeat;
    ofAddListener(transport->tempoChange, this, &ofApp::tempoChange);
    ofAddListener(transport->ClockCallback, this, &ofApp::globalState);
    
    bHost = true; //add GUI for this parameter.
    
    
    if(bHost){
        transport->tempoSlider->setEnabled(true);
        transport->text->setEnabled(true);
        transport->tempoSlider->setValue(120);
        transport->setTimeSignature(4, 4);
    }else{
        transport->tempoSlider->setEnabled(false);
        transport->text->setEnabled(false);
    }
    
    //Sequencer
    module = unique_ptr<INF_Module>(new INF_Module(0));
    module->pos = ofPoint(0, docks->getHeight());
    module->setup();
    
    triggers.reserve(module->tracks.size());
    for(int i=0;i < module->tracks.size();i++){
        triggers.push_back(0);
    }
    
    playHeadAmt = 16;
    divisor = 4;
    
    //default IP:PORT Address
    string netAddress;
    stringstream convert;
    convert << " : " <<PORT;
    netAddress = HOST + convert.str();
    ip_adrs = HOST;
    port_adrs = PORT;
    
    //Networking components
    oscListener.setup();
    ofAddListener(oscListener.AbletonPlayed, this, &ofApp::AbletonPlayed);

    //Audio Setup
    ofSoundStreamSetup(2, 0, this, SRATE, BUFFER_SIZE, 4);
    ofAddListener(globalPlayHead, this, &ofApp::clockPlayed); //add listener that maxiClock's variable
    ofSoundStreamStop(); //in initial state, soundstream is stopped.
    isPlay = false; //and its boolean
}
//--------------------------------------------------------------
void ofApp::update(){
    if(!bHost && playHeadAmt != NULL && divisor != NULL){
        oscListener.update(); //Listening OSC...
        accents.resize(playHeadAmt);
        for(int i=0; i != playHeadAmt; i++){
            if(i % divisor == 0){//find strong beat and weak beats
                accents.at(i) = 1;
            }else{
                accents.at(i) = 0;
            }
        }
    }
    module->update();
    docks->update();
    transport->update();
 
    stringstream newStatus;
    newStatus <<"connected to "<<midi.midiOut.getName()<<" "<<
    "Channel : "<< midi.channel;
    string status = newStatus.str();
    transport->status->setLabel(status);
    unique_lock<mutex> lock(audioMutex);
}
//--------------------------------------------------------------
void ofApp::draw(){
    module->draw();
    transport->draw();

    ofSetColor(255);
    stringstream text2;
    text2 << "Tempo " << tempo <<endl
    << "is playing?: " << isPlay << endl << endl
    << "Time Signature :"<< timeSignature << endl << endl
    << "Current Beat " << currentBeat << "/"<< currentBar << endl
    << "Beatgrid : " << beatGrid<<endl;
    ofDrawBitmapString(text2.str(), 20, 60);
    
    //ofxDatGui components
    ofPushStyle();
    ofSetColor(255, 255, 255);
    docks->draw();
    ofPopStyle();
}
//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
        currentCount=(int)clock.phasor(bps);
        
        if (lastCount!=currentCount){
            ofNotifyEvent(globalPlayHead, playHead, this);
            playHead++;//iterate the playhead
            lastCount=0;//reset the metrotest
        }
        //THIS DOES NOT SEND ANY AUDIO SIGNAL.
    }
    unique_lock<mutex> lock(audioMutex);
}
//--------------------------------------------------------------
void ofApp::clockPlayed(int &eventArgs){
    int playHeadIn = eventArgs;
    
    for(int i=0;i < module->tracks.size();i++){
        int length = module->tracks[i]->pattern.size();
//        
//        if(module->tracks[0]->pattern.size() >0 && module->tracks[0]){
//            triggers[0] = module->tracks[0]->pattern[playHeadIn%16];
//        }
//        if(module->tracks[1]->pattern.size() >0 && module->tracks[1]){
//            triggers[1] = module->tracks[1]->pattern[playHeadIn%16];
//        }
        if(module->tracks[i]->pattern.size() >0 && module->tracks[i]){
            triggers[i] = module->tracks[i]->pattern[playHeadIn%length];
        }
    }
    
    /*
    //STUPID TEST
    if(triggers[0] == 1){
        Note* n = new Note();
        n->status = KEY_ON;
        n->pitch = module->tracks[0]->pitch;
        n->velocity = 80;
        midi.sendNote(*n);
        delete n;
    }else{
        Note* n = new Note();
        n->status = KEY_OFF;
        n->pitch = module->tracks[0]->pitch;
        n->velocity = 0;
        midi.sendNote(*n);
        delete n;
    }
     */
    
    
    for(int i=0; i < module->tracks.size();i++){
        if(triggers[i] == 1){
            Note* n = new Note();
            n->status = KEY_ON;
            n->pitch = module->tracks[i]->pitch;
            n->velocity = 80;
            midi.sendNote(*n);
            delete n;
        }else{
            Note* n = new Note();
            n->status = KEY_OFF;
            n->pitch = module->tracks[i]->pitch;
            n->velocity = 0;
            midi.sendNote(*n);
            delete n;
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key ==32){
        isPlay = !isPlay;
        transport->start->setChecked(isPlay);
    }
    if(isPlay == true){
        ofSoundStreamStart();
    }
    else{
        ofSoundStreamStop();
        playHead = 0;
    }
}
//--------------------------------------------------------------
void ofApp::AbletonPlayed(Ableton &eventArgs){
    tempo = eventArgs.tempo;
    currentBar = eventArgs.bar;
    currentBeat = eventArgs.beat;
    
    if(!bHost){
        isPlay = eventArgs.isPlay;
        transport->start->setChecked(isPlay);
        
        if(isPlay == true){
            ofSoundStreamStart();
        }
        else{
            ofSoundStreamStop();
            playHead = 0;
        }
    }

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
    midi.setDevice(eventArgs.device);
    midi.channel = eventArgs.channel+1;
}
//--------------------------------------------------------------
void ofApp::globalState(TransportMessage &eventArgs){
    
    if(bHost){
        isPlay = eventArgs.play;
        
        if(isPlay == true){
            ofSoundStreamStart();
        }
        else{
            ofSoundStreamStop();
            playHead = 0;
        }
    }
    string tempoIn = eventArgs.timeSignature;
    
    tempoIn.erase(std::remove(tempoIn.begin(),tempoIn.end(),'/'),tempoIn.end());
}
//--------------------------------------------------------------
void ofApp::setMode(bool &eventArgs){
    if(eventArgs){
        bHost = false;
        cout<<"[Slave Mode is Activated]"<<endl
        <<"[Now Listening Ableton Live...]"<<endl;
        midi.midiOut.openVirtualPort("Infinite Machine");
        midi.enableVirtual();
    }else{
        bHost = true;
        
        cout<<"[Master Mode is Activated]"<<endl;
       
    }
    transport->text->setEnabled(bHost);
    transport->tempoSlider->setEnabled(bHost);
    transport->start->setEnabled(bHost);
    docks->deviceGUI[0]->setEnabled(bHost);
}
//--------------------------------------------------------------
void ofApp::tempoChange(int &eventArgs){
    tempo = eventArgs;
    bps = (tempo / 60.) * ticksPerBeat;
    ofLogNotice()<<"Current BPM ::"<<eventArgs<<" "<<"BPS ::"<<bps;
}
//--------------------------------------------------------------
void ofApp::exit(){
    midi.exit();
    ofSoundStreamClose();
    //delete raw pointers
    delete docks;
    //and smart pointers
    module.reset();
    transport.release();
    
    ofLogNotice()<<"[Infinite Machine : Goodbye.]";
}
