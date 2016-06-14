

#include "ofApp.h"

#define SRATE 44100 //SAMPLE RATE
#define BUFFER_SIZE 512 // BUFFERSIZE
#define HOST "localhost" //default address
#define PORT 8080 //default port.

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);

    max_len = 64; numPulse = 4;
    
  
    //default IP:PORT Address
    string netAddress;
    stringstream convert;
    convert << " : " <<PORT;
    netAddress = HOST + convert.str();
    ip_adrs = HOST;
    port_adrs = PORT;

    
    
    //Sequencer test
    seq = new Sequencer();
    //PolyGUI
    p = new PolyGUI(200,ofVec2f(ofGetWidth()/2, ofGetHeight()/2), "/test");
    p->createPoly(seq->seq);
    
    setGui();
    //Audio Setup
    ofSoundStreamSetup(2, 0, this, SRATE, BUFFER_SIZE, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    //FPS update on GUI parameter
    fps = ofToString(ofGetFrameRate());

}

//--------------------------------------------------------------
void ofApp::draw(){
//    p->draw();
    
    
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioOut(float *output, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        
//        seq->play(start);
//        trigger = seq->trigger();
        //THIS DOES NOT SEND ANY AUDIO SIGNAL.
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------
void ofApp::exit(){
    //delete objects
    delete p;
    delete seq;
}
