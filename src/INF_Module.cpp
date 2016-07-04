//
//  INF_Module.cpp
//
//  Created by Heewon Oh on 03/07/2016.
//
//

#include "INF_Module.h"

INF_Module::INF_Module(int _index):index(_index), radius(200), gap(20),seqAmt(0){
    //constructor
    
}
//--------------------------------------------------------------
INF_Module::~INF_Module(){
    cout<<"Page "<<index<<" is Deleted"<<endl;
}
//--------------------------------------------------------------
void INF_Module::setup(){
    rect = new ofRectangle();
    rect->setFromCenter(pos, radius*2, radius*2);
    setGui();
    
    //Cyclic Step Sequencer
    circleStep *seq;
    seq = new circleStep(rect->getCenter(), radius);
    seq->setup();
    ofAddListener(seq->sequenceUpdate, this, &INF_Module::sequenceCallback);
    stepGui.push_back(seq);
}
//--------------------------------------------------------------
void INF_Module::setGui(){
    //ofxDatGui Components

    //RANDOMIZATION Button
    int x0 = rect->getLeft();
    ofxDatGuiButton* b = new ofxDatGuiButton("RANDOMIZE!");
    b->setPosition(x0,0);
    b->setWidth(100);
    b->onButtonEvent(this, &INF_Module::onButtonEvent);
    components.push_back(b);

    x0 += b->getWidth();
    vector<string> mode = {"Manual", "Euclid"};
    ofxDatGuiDropdown* d = new ofxDatGuiDropdown("Mode", mode);
    d->setWidth(110);
    d->setPosition(x0, 0);
    d->onDropdownEvent(this, &INF_Module::onDropdownEvent);
    components.push_back(d);
    
    //SEQ MODIFIERS
    int x1 = rect->getRight()-40;
    b = new ofxDatGuiButton("+");
    b->setPosition(x1, 0);
    b->setWidth(40);
    b->onButtonEvent(this, &INF_Module::onButtonEvent);
    components.push_back(b);
    
    x1 += b->getWidth();
    b = new ofxDatGuiButton("-");
    b->setPosition(x1, 0);
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
    
    for(auto x: stepGui)
        x->draw();
    
    for(auto x: components)
        x->draw();
}
//--------------------------------------------------------------
void INF_Module::onButtonEvent(ofxDatGuiButtonEvent e){
        //ADD SEQUENCE
    if(e.target->getLabel() == "+"){
        if(seqAmt <8){
            circleStep *seq;
            seqAmt ++;
            cout<<seqAmt<<endl;
            radius -= gap;
            seq = new circleStep(rect->getCenter(), radius);
            seq->index = seqAmt;
            seq->setup();
            seq->setLength(16);
            ofAddListener(seq->sequenceUpdate, this, &INF_Module::sequenceCallback);
            stepGui.push_back(seq);
        }
        
        //ERASE SEQUENCE
    }else if(e.target->getLabel() == "-"){
        if(seqAmt > 0 && stepGui.size() > 1){
            seqAmt --;
            cout<<seqAmt<<endl;
            radius += gap;
            //garbage collection
            stepGui.pop_back();
            ofRemoveListener(stepGui[seqAmt]->sequenceUpdate, this, &INF_Module::sequenceCallback);
            delete stepGui[stepGui.size()];
            
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
void INF_Module::onDropdownEvent(ofxDatGuiDropdownEvent e){
    cout<<e.child<<endl;
    
}
//--------------------------------------------------------------
void INF_Module::sequenceCallback(Sequence &e){
    loop = e.seq;
    
    for(sequenceIterator = loop.begin(); sequenceIterator != loop.end(); sequenceIterator++){
        cout<<*sequenceIterator;
    }
    cout<<'\n'<<"##"<<e.index<<"## Length : "<<e.seq.size()<<endl;
    cout<<"loop "<<loop.size()<<endl;

};
//--------------------------------------------------------------
void INF_Module::exit(){
    delete rect;
}