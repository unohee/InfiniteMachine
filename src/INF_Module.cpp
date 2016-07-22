//
//  INF_Module.cpp
//
//  Created by Heewon Oh on 03/07/2016.
//
//

#include "INF_Module.h"

INF_Module::INF_Module(int _index):index(_index), radius(300), gap(24),seqAmt(0), bEuclid(true){
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
    rect_ptr->set(pos.x, pos.y, radius*2, radius*2);

    setGui();
    //Cyclic Sequencer init
    cycleRad = radius - 12;
    CyclicSeq cyclic = CyclicSeq(new circleStep(rect_ptr->getCenter(), cycleRad)); //GUI
    
    
    Track t = Track(new Sequence());//Actual Sequence data
    t->index = seqAmt;
    
        if(bEuclid){//if euclidean mode is enabled in initial state..
            //Add Euclidean Rhythm  (4:16)
            unique_ptr<Bjorklund>euclid = unique_ptr<Bjorklund>(new Bjorklund(16,4, false));
            euclid->init();
            vector<bool> seq = euclid->sequence;
            t->pattern = seq;
            cyclic->setSequence(t->pattern);
        }else{
            for(int i=0; i < 16;i++)
                t->pattern.push_back(0);
            cyclic->setSequence(t->pattern);
        }
    
    cyclic->setup();
    stepGui.push_back(move(cyclic));
    tracks.push_back(move(t));
    ofAddListener(stepGui[0]->stepUpdated, this, &INF_Module::sequenceCallback);
    
    //and Add its controller
    guiLoc = ofPoint(rect_ptr->getTopRight());
    GuiPtr c = GuiPtr(new INF_Controls());
    c->pos = guiLoc;
    c->setup();
    controls.push_back(c);
    ofAddListener(c->GuiCallback, this, &INF_Module::seqParamChanged);
}
//--------------------------------------------------------------
void INF_Module::setGui(){
    //ofxDatGui Components
    
    //RANDOMIZATION Button
    int x0 = rect_ptr->getBottomLeft().x;
    int y0 = rect_ptr->getBottomLeft().y;
    ofPoint p = ofPoint(x0,y0);
    RButtonPtr rb = RButtonPtr(new RoundedButton());
    rb->setFontSize(10);
    rb->setLabel("RANDOMIZE!");
    rb->setColor(ofColor(60), ofColor(255));
    rb->set(p);
    rButtons.push_back(rb);
    ofAddListener(rb->onButtonEvent, this, &INF_Module::customButtonEvent);
    
    x0 += rb->getWidth();
    p = ofPoint(x0,y0);
    rb = RButtonPtr(new RoundedButton());
    rb->setFontSize(10);
    rb->setLabel("VELOCITY");
    rb->setColor(ofColor(60), ofColor(255));
    rb->set(p);
    rButtons.push_back(rb);
    ofAddListener(rb->onButtonEvent, this, &INF_Module::customButtonEvent);
    
    //SEQ MODIFIERS
    int x1 = rect_ptr->getBottomRight().x-80;
    int y1 = rect_ptr->getBottomRight().y;
    shared_ptr<ofxDatGuiButton> b = make_shared<ofxDatGuiButton>("+");
    b->setPosition(x1, y1);
    b->setWidth(40);
    b->onButtonEvent(this, &INF_Module::onButtonEvent);
    components.push_back(b);
    
    x1 += b->getWidth();
    b = make_shared<ofxDatGuiButton>("-");
    b->setPosition(x1, y1);
    b->setWidth(40);
    b->onButtonEvent(this, &INF_Module::onButtonEvent);
    components.push_back(b);
}
//--------------------------------------------------------------
void INF_Module::update(){
    for(auto &x: components)//DatGui update
        x->update();
    for(auto &x: controls)
        x->update();
}
//--------------------------------------------------------------
void INF_Module::draw(){
    for(auto &x: rButtons)
        x->draw();
    for(auto &x: controls)
        x->draw();
    for(auto &x: stepGui)
        x->draw();
    for(auto &x: components)
        x->draw();
}
//--------------------------------------------------------------
void INF_Module::onButtonEvent(ofxDatGuiButtonEvent e){
    //ADD SEQUENCE
    if(e.target->getLabel() == "+"){
        if(seqAmt <7){
            
            seqAmt ++;
            cycleRad -= gap;
            
            //new Cyclic GUI
            CyclicSeq seq = CyclicSeq(new circleStep(rect_ptr->getCenter(), cycleRad));
            Track t = Track(new Sequence());//Actual Sequence data
            
            seq->index = seqAmt;
            t->index = seqAmt;
            
            for(int i=0; i < 16;i++)
                t->pattern.push_back(0);

            seq->setSequence(t->pattern);
            seq->setup();
            stepGui.push_back(seq);
            tracks.push_back(move(t));
            ofAddListener(seq->stepUpdated, this, &INF_Module::sequenceCallback);
            
            //and its controller
            GuiPtr c = GuiPtr(new INF_Controls());
            guiLoc.y += (26*6);
            if(seqAmt == 4 || seqAmt == 8){
                guiLoc.x += controls[0]->getWidth();
                guiLoc.y = rect_ptr->getTopLeft().y;
            }
            c->pos = guiLoc;
            c->index = seqAmt;
            c->setup();
            controls.push_back(c);
            ofAddListener(c->GuiCallback, this, &INF_Module::seqParamChanged);
        }
        //ERASE SEQUENCE
    }else if(e.target->getLabel() == "-"){
        if(seqAmt > 0 && stepGui.size() > 1 && controls.size() > 1){
            seqAmt --;
            cycleRad += gap;
            guiLoc.y -= 160;
            if(seqAmt == 4 || seqAmt == 8){
                guiLoc.x -= controls[0]->getWidth();
            }
            guiLoc.y = rect_ptr->getTopLeft().y;
            stepGui.pop_back();
            controls.pop_back();
            tracks.pop_back();
            if(seqAmt > 1){
                ofRemoveListener(stepGui[seqAmt]->stepUpdated, this, &INF_Module::sequenceCallback);
                ofRemoveListener(controls[seqAmt]->GuiCallback, this, &INF_Module::seqParamChanged);
            }
        }
    }
}
//--------------------------------------------------------------
void INF_Module::customButtonEvent(ButtonEvent &e){
    if(e.label=="RANDOMIZE!"){

        for(auto &x:stepGui){
            int rand = (int)ofRandom(16);
            int newStepAmt = (rand > 4) ? rand : 4;
            int rand1 = (int)ofRandom(16);
            int newPulse = (rand > rand1) ? rand1 : rand;
            
            if(bEuclid){
                if(x->index == 0){
                    unique_ptr<Bjorklund>euclid = unique_ptr<Bjorklund>(new Bjorklund(16,newPulse, false));
                    euclid->init();
                    x->stepAmt = 16;
                    tracks[x->index]->pattern = euclid->sequence;
                    x->setSequence(tracks[x->index]->pattern);
                    x->setup();
                    controls[x->index]->setEuclid(16, newPulse);
                    
                }else{
                    unique_ptr<Bjorklund>euclid = unique_ptr<Bjorklund>(new Bjorklund(newStepAmt,newPulse, false));
                    euclid->init();
                    x->stepAmt = newStepAmt;
                    tracks[x->index]->pattern = euclid->sequence;
                    x->setSequence(tracks[x->index]->pattern);
                    x->setup();
                    controls[x->index]->setEuclid(newStepAmt, newPulse);
                }
            }else{
                x->stepAmt = newStepAmt;
                x->setSequence(tracks[x->index]->pattern);
                x->setup();
                controls[x->index]->setLength(newStepAmt);
            }
        }
    }
}
//--------------------------------------------------------------
void INF_Module::onDropdownEvent(ofxDatGuiDropdownEvent e){
    cout<<e.child<<endl;
}
//--------------------------------------------------------------
void INF_Module::seqParamChanged(Controls &e){
    
    
    if(e.index < stepGui.size() && e.index < tracks.size()){
        for(auto &x: stepGui){
            x->stepAmt = e.length;
            
            if(bEuclid){
                euclid = unique_ptr<Bjorklund>(new Bjorklund(e.length,e.pulse, false));
                euclid->init();
                tracks[e.index]->pattern = euclid->sequence;
            }
            
            stepGui[e.index]->setSequence(tracks[e.index]->pattern);
            stepGui[e.index]->setup();
            tracks[e.index]->pitch = e.pitch;
            tracks[e.index]->velocity = e.velocity;
        }
    }
    
    /*
    for(auto &x:stepGui){
        if(x->index == e.index){
            euclid = unique_ptr<Bjorklund>(new Bjorklund(e.length,e.pulse, false));
            euclid->init();
            
            x->stepAmt = e.length;
            x->setSequence(tracks[x->index]->pattern);
            x->setup();
        }
    }
    */
}
//--------------------------------------------------------------
void INF_Module::sequenceCallback(SequenceEvent &e){
    
    if(e.index <= tracks.size())
        tracks[e.index]->pattern = e.seq;

    cout<<'\n'<<"##"<<e.index<<"## Length : "<<e.seq.size()<<endl;
};
//--------------------------------------------------------------