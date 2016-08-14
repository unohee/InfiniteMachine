

#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    cout<<"[Infinite Machine ALPHA.v02]"<<endl;
    ofBackground(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetWindowTitle("Infinite Machine");
    
    //variables for transport and maxiOsc
    timeSignature = "4/4";
    beatResolution = 4;
    beatAmount = 4;
    tempo = 120;
    //my metronome will ticks 4 times per beat (16th note)
    ticksPerBeat = beatAmount;
    
    
    //Upper dock
    docks = new Dat_Docker(midi.midiOut->getPortList());
    ofAddListener(docks->deviceState, this, &ofApp::MIDICallback);//add EventListener.
    ofAddListener(docks->modeChange, this, &ofApp::setMode);
    
    //Sequencer
    module = unique_ptr<INF_Module>(new INF_Module(0));
    module->pos = ofPoint(0, docks->getHeight());
    module->setMeter(beatAmount, beatResolution);
    module->setup();
    
    //Transport Control..
    transport = unique_ptr<INF_Transport>(new INF_Transport());
    transport->pos = ofPoint(0,754);
    transport->setup();
    transport->setTimeSignature(beatResolution, ticksPerBeat);
    
    //Transport counts the bar length and playHead's position
    bps = (tempo / 60.) * 1; //thus it ticks once per beat
    currentBar = 0; currentBeat = 0;
    ofAddListener(transport->tempoChange, this, &ofApp::tempoChange);
    ofAddListener(transport->MeterChanged, this, &ofApp::onMeterChange);
    ofAddListener(transport->TransportCallback, this, &ofApp::globalState);
    
    
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
    
    //individual clocks (for each track) and its trigger
    for(int i=0; i < 8;i++){
        Metro *m = new Metro();
        m->index = i;
        m->setTicks(ticksPerBeat); //by default, it is 4.
        m->setTempo(tempo);
        clockGroup.push_back(m);
        //Add Eventlistener
        ofAddListener(clockGroup[i]->individualPlayHead, this, &ofApp::multipleClocks);
        ofAddListener(module->controls[i]->tickChange, this, &ofApp::tickChanged);
    }
    //triggers
    triggers.reserve(module->tracks.size());
    for(int i=0;i < module->tracks.size();i++){
        triggers.push_back(0);
    }

    
    //updating beatgrid
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
    ofAddListener(globalPlayHead, this, &ofApp::onGlobalClock); //add listener that maxiClock's variable
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
    newStatus <<"connected to "<<midi.midiOut->getName()<<" "<<
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
    << "Time Signature :"<< transport->meter << endl << endl
    << "Current Beat " << currentBeat+1 << " / "<<"Current Bar "<< currentBar << endl
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
        
        for(auto &x:clockGroup)
            x->ticker();
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
void ofApp::multipleClocks(ClockOut &e){
    
    for(auto &x:module->tracks){
        int length = x->pattern.size();
        if(x->pattern.size() > 0 && x->index == e.index){
            triggers[e.index] = x->pattern[e.playHead%length];
        }
    }
    
    for(int i=0; i < module->tracks.size();i++){
        if(triggers[i] == 1 && i == e.index && module->tracks[i]->pattern.size() > 0){
            Note* n = new Note();
            n->status = KEY_ON;
            n->pitch = module->tracks[i]->pitch;
            n->velocity = 80;
            ofLogNotice()<<"NOTE ON:"<<module->tracks[i]->pitch<<" "<<"Track"<<e.index<<" "<<ofGetElapsedTimef();
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
void ofApp::tickChanged(Ticks &eventArgs){

    cout<<"Track"<<eventArgs.index<<" "<<"Ticks:"<<eventArgs.ticksPerBeat<<endl;
    
    for(int i=0; i< clockGroup.size();i++){
        if(clockGroup[i]->index == eventArgs.index){
            clockGroup[i]->setTicks(eventArgs.ticksPerBeat);
        }
        
        if(i > 0){
            clockGroup[i]->playHead = clockGroup[i-1]->playHead;
        }
        
    }
    
    for(auto &x:clockGroup){
        if(x->index == eventArgs.index){
//            x->setTicks(eventArgs.ticksPerBeat);
//            if(currentBeat == 0){
//                x->playHead = 0; //retriggering
//            }else{
//                x->playHead = currentBeat*2;
//            }
            
        }
    }

}
//--------------------------------------------------------------
void ofApp::onGlobalClock(int &eventArgs){
    int beatsPerBar = 4;
    int beat = eventArgs;
    currentBeat ++;
    
    if(beat % beatAmount == 0){
        currentBar ++;
        currentBeat = 0;
    }
    
    
    /*
    for(int i=0;i < module->tracks.size();i++){
        int length = module->tracks[i]->pattern.size();
        
        //matching pattern into trigger by indices
        if(module->tracks[i]->pattern.size() >0 && module->tracks[i]){
            triggers[i] = module->tracks[i]->pattern[playHeadIn%length];
        }
    }
    
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
     */
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
        for(auto &x:clockGroup)
            x->playHead = 0;
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
void ofApp::onMeterChange(currentMeter &e){
    beatAmount = e.beats;
    beatResolution = e.beatResolution;
    module->setMeter(beatAmount, beatResolution);
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
        midi.midiOut->openVirtualPort("Infinite Machine");
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
    
    for(auto &x:clockGroup)
        x->setTempo(tempo);
    
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
