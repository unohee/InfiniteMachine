//
//  INF_Module.cpp
//
//  Created by Heewon Oh on 03/07/2016.
//
//

#include "INF_Module.h"

INF_Module::INF_Module(int _index):index(_index), radius(300), gap(30),seqAmt(0){
    //constructor
}
//--------------------------------------------------------------
INF_Module::~INF_Module(){
    if(!stepGui.empty())stepGui.clear();
    if(!components.empty())components.clear();
    cout<<"[Module "<<index<<" is Deleted]"<<endl;
}
//--------------------------------------------------------------
void INF_Module::setup(){
    rect_ptr= unique_ptr<ofRectangle>(new ofRectangle());
    rect_ptr->setFromCenter(pos, radius*2, radius*2);
    setGui();
    
    //enhanced, simplified Modern C++ version
    CyclicSeq seq = CyclicSeq(new circleStep(rect_ptr->getCenter(), radius));
    seq->setup();
    stepGui.push_back(seq);
    ofAddListener(stepGui[0]->sequenceUpdate, this, &INF_Module::sequenceCallback);
}
//--------------------------------------------------------------
void INF_Module::setGui(){
    //ofxDatGui Components
    
    //RANDOMIZATION Button
    int x0 = rect_ptr->getTopLeft().x;
    int y0 = rect_ptr->getTopLeft().y-40;
    ofPoint p = ofPoint(x0,y0);
    random = unique_ptr<RoundedButton>(new RoundedButton());
    random->setFontSize(10);
    random->setLabel("RANDOMIZE!");
    random->setColor(ofColor(60), ofColor(255));
    random->set(p);
    ofAddListener(random->onButtonEvent, this, &INF_Module::customButtonEvent);

    //DatGUIs
    x0 += random->getWidth();
    vector<string> mode = {"Manual", "Euclid"};
    shared_ptr<ofxDatGuiDropdown> d = make_shared<ofxDatGuiDropdown>("Mode", mode);
    d->setWidth(110);
    d->setPosition(x0, y0);
    d->onDropdownEvent(this, &INF_Module::onDropdownEvent);
    components.push_back(d);
    
    //SEQ MODIFIERS
    int x1 = rect_ptr->getRight()-40;
    shared_ptr<ofxDatGuiButton> b = make_shared<ofxDatGuiButton>("+");
    b->setPosition(x1, y0);
    b->setWidth(40);
    b->onButtonEvent(this, &INF_Module::onButtonEvent);
    components.push_back(b);
    
    x1 += b->getWidth();
    b = make_shared<ofxDatGuiButton>("-");
    b->setPosition(x1, y0);
    b->setWidth(40);
    b->onButtonEvent(this, &INF_Module::onButtonEvent);
    components.push_back(b);
}
//--------------------------------------------------------------
void INF_Module::update(){
    for(auto x: components)//DatGui update
        x->update();
    
    //copy sequence from StepGUI.
    for(int i=0; i < stepGui[0]->getSize();i++){
        loop.insert(loop.begin()+i, stepGui[0]->step_seq[i]);
    }
}
//--------------------------------------------------------------
void INF_Module::draw(){
    random->draw();
    for(auto &x: stepGui)
        x->draw();
    for(auto &x: components)
        x->draw();
}
//--------------------------------------------------------------
void INF_Module::onButtonEvent(ofxDatGuiButtonEvent e){
    //ADD SEQUENCE
    if(e.target->getLabel() == "+"){
        if(seqAmt <8){
            seqAmt ++;
            radius -= gap;
            CyclicSeq seq = CyclicSeq(new circleStep(rect_ptr->getCenter(), radius));
            seq->index = seqAmt;
            seq->setup();
            seq->setLength(16);
            stepGui.push_back(seq);
            ofAddListener(stepGui[seqAmt]->sequenceUpdate, this, &INF_Module::sequenceCallback);
        }
    //ERASE SEQUENCE
    }else if(e.target->getLabel() == "-"){
        if(seqAmt > 0 && stepGui.size() > 1){
            seqAmt --;
            radius += gap;
            stepGui.pop_back();
            if(seqAmt > 1)
                ofRemoveListener(stepGui[seqAmt]->sequenceUpdate, this, &INF_Module::sequenceCallback);
        }
        //RANDOMIZED
    }else if(e.target->getLabel() == "RANDOMIZE!"){
        for(auto x:stepGui){
            int rand = (int)ofRandom(16);
            int newStepAmt = (rand > 4) ? rand : 4;
            loop.resize(newStepAmt);
            x->stepAmt = newStepAmt;
            x->setSequence(loop);
            x->setup();
        }
    }
}
//--------------------------------------------------------------
void INF_Module::customButtonEvent(ButtonEvent &e){
    if(e.label=="RANDOMIZE!"){
        for(auto &x:stepGui){
            int rand = (int)ofRandom(16);
            int newStepAmt = (rand > 4) ? rand : 4;
            loop.resize(newStepAmt);
            x->stepAmt = newStepAmt;
            x->setSequence(loop);
            x->setup();
        }
    }
}
//--------------------------------------------------------------
void INF_Module::onDropdownEvent(ofxDatGuiDropdownEvent e){
    cout<<e.child<<endl;
    
}
//--------------------------------------------------------------
void INF_Module::sequenceCallback(SequenceEvent &e){
    loop = e.seq;
    
    for(sequenceIterator = loop.begin(); sequenceIterator != loop.end(); sequenceIterator++){
        cout<<*sequenceIterator;
    }
    cout<<'\n'<<"##"<<e.index<<"## Length : "<<e.seq.size()<<endl;
    cout<<"loop "<<loop.size()<<endl;
    
};
//--------------------------------------------------------------