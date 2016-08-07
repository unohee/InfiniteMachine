

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
    transport->tempoVal = 120;
    timeSignature = "4/4";
    ofAddListener(transport->ClockCallback, this, &ofApp::globalState);
    ofAddListener(activated, this, &ofApp::clockStarted);
    
    bHost = true; //add GUI for this parameter.
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
    midi->midiOut.listPorts();
    oscListener.setup();
    ofAddListener(oscListener.AbletonPlayed, this, &ofApp::AbletonPlayed);


    //Audio Setup
    ofSoundStreamSetup(2, 0, this, SRATE, BUFFER_SIZE, 4);
    ofAddListener(globalPlayHead, this, &ofApp::clockPlayed); //add listener that maxiClock's variable
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
    
    seq = module->tracks[0]->pattern;
    
    
    stringstream newStatus;
    newStatus <<"connected to "<<midi->midiOut.getName()<<" "<<
    "Channel : "<< midi->channel;
    string status = newStatus.str();
    transport->status->setLabel(status);
}
//--------------------------------------------------------------
void ofApp::draw(){
    module->draw();
    transport->draw();
    
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
void ofApp::setTempo(float BPM){
    bps = BPM / 60.f * 4;
};
//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    for(int i = 0; i < bufferSize; i++){
//        currentCount=(int)timer.phasor(8);
        
        if(isPlay){
            currentCount=(int)floor(transport->getClock());
            
        }
        
        if (lastCount!=currentCount) {
            //iterate the playhead
            playHead++;
            if(seq[playHead-1%16] == true && isPlay == true){
                cout<<"X";
//                cout<<"Bam."<<" "<<playHead<<endl;
                Note *n = new Note();
                n->status = KEY_ON;
                n->pitch = 32;
                n->velocity = 80;
                midi->sendNote(*n);
            }else if(seq[playHead-1%16] == false && isPlay == true){
                cout<<".";
                Note *n = new Note();
                n->status = KEY_OFF;
                n->pitch = 0;
                n->velocity = 0;
                midi->sendNote(*n);
            }
            if(playHead > 15){
                playHead = 0;
            }
            lastCount=0;//reset the metrotest
//
        }
        //THIS DOES NOT SEND ANY AUDIO SIGNAL.
    }
}
//--------------------------------------------------------------
void ofApp::clockPlayed(int &eventArgs){
    int playHeadIn = eventArgs;
//    cout<<"Playhead"<<eventArgs<<endl;
//    for(auto &x: module->tracks){
//        //Create Note ON/OFF Pair
//        if(x->pattern.at(playHeadIn%playHeadAmt) == true){
//            Note *n = new Note();
//            n->status = KEY_ON;
//            n->pitch = x->pitch;
//            n->velocity = 127;
//            midi->sendNote(*n);
//        }else{
//            unique_ptr<Note> n = unique_ptr<Note>(new Note());
//            n->status = KEY_OFF;
//            n->pitch = 36;
//            n->velocity = 0;
//            midi->sendNote(*n);
//        }
//    }

}
//--------------------------------------------------------------
void ofApp::AbletonPlayed(Ableton &eventArgs){
    tempo = eventArgs.tempo;
    currentBar = eventArgs.bar;
    currentBeat = eventArgs.beat;
    
    if(!bHost){
        isPlay = eventArgs.isPlay;
        transport->start->setChecked(isPlay);
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
    midi->setDevice(eventArgs.device);
    midi->channel = eventArgs.channel+1;
}
//--------------------------------------------------------------
void ofApp::globalState(TransportMessage &eventArgs){
    
    if(bHost)
        isPlay = eventArgs.play;
//        ofNotifyEvent(activated, isPlay, this);
    
    string tempoIn = eventArgs.timeSignature;
    
    tempoIn.erase(std::remove(tempoIn.begin(),tempoIn.end(),'/'),tempoIn.end());
}
//--------------------------------------------------------------
void ofApp::setMode(bool &eventArgs){
    if(eventArgs){
        bHost = false;
        cout<<"[Slave Mode is Activated]"<<endl
        <<"[Now Listening Ableton Live...]"<<endl;
        midi->midiOut.openVirtualPort("Infinite Machine");
        midi->enableVirtual();
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
void ofApp::clockStarted(bool &eventArgs){
//    for(auto &x: module->tracks){
//        //Create Note ON/OFF Pair
//        if(x->pattern.at(0) == true){
//            unique_ptr<Note> n = unique_ptr<Note>(new Note());
//            n->status = KEY_ON;
//            n->pitch = x->pitch;
//            n->velocity = 127;
//            midi->sendNote(*n);
//        }else{
//            unique_ptr<Note> n = unique_ptr<Note>(new Note());
//            n->status = KEY_OFF;
//            n->pitch = x->pitch;
//            n->velocity = 0;
//            midi->sendNote(*n);
//        }
//    }
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
