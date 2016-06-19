

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    cout<<"[Infinite Machine ALPHA.v02]"<<endl;
    ofBackground(0, 0, 0);

    vector<int>v;
    Urn u = Urn(10);
    v = u.urn();
    
    for(int i=0;i<v.size();i++)
        cout<<v[i]<<" ";
    
    max_len = 16; numPulse = 4;
    
  
    //default IP:PORT Address
    string netAddress;
    stringstream convert;
    convert << " : " <<PORT;
    netAddress = HOST + convert.str();
    ip_adrs = HOST;
    port_adrs = PORT;

    int a = 8;
    int b = 3;
    string typeTag = "/test/";
    
    
    
    
    //Sequencer init
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
    
    //PolyGUI init
    ofVec3f n(ofGetWidth()/2,ofGetHeight()/2,0);
    for(int i=0;i!=INF_seq.size();i++){
        try{
            PolyGUI *p = new PolyGUI(200, n, typeTag);
            p->createPoly(14);
            INF_gui.push_back(p);
        }catch(exception e){
            cerr<<"exception occur"<<endl;
            cout<<e.what()<<endl;
        }
    }

    setGui();
    
    //OSC Network
    network = new NetOSC(HOST,PORT);
    
    t.setup();
//    ofxDatGuiComponent * component;
//    component = new ofxDatGuiFRM();
//    docker.push_back(component);
//    
//    float gap = ofGetWidth() / docker.size();
//    for(int i=0;i < docker.size();++i){
//        if(i <= 2){
//            docker[i]->setWidth(gap, 0.45);
//        }else{
//            docker[i]->setWidth(gap, 0.2);
//        }
//        docker[i]->setPosition(gap*i, ofGetHeight() - docker[i]->getHeight());
//    }
//    
    //Audio Setup
    ofSoundStreamSetup(2, 0, this, SRATE, BUFFER_SIZE, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
    //FPS update on GUI parameter
    fps = ofToString(ofGetFrameRate());
    
    for(int i=0;i < INF_gui.size();++i){
        INF_gui[i]->mouseOver();
    }
    for(int i=0;i<docker.size();i++){
        docker[i]->update();
    }
    t.update(ofGetWidth());
//    network->receive(notes, trigger);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0;i < INF_seq.size();++i){
        INF_gui[i]->draw();
    }
    
    
    gui.draw();
    t.draw();
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
    
    if(button == 0)
        mouseClick = true;
    else
        mouseClick = !mouseClick;
        
    cout<<mouseClick<<endl;

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
    delete network;
    for_each(INF_seq.begin(), INF_seq.end(), DeleteVector<Sequencer*>());
    for_each(INF_gui.begin(), INF_gui.end(), DeleteVector<PolyGUI*>());
    cout<<"[Infinite Machine : Goodbye.]"<<endl;
}
