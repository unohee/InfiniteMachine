//
//  INF_Module.cpp
//
//  Created by Heewon Oh on 03/07/2016.
//
//

#include "INF_Module.h"

INF_Module::INF_Module(int _index):index(_index), radius(300), gap(24),seqAmt(0){
    //constructor
}
//--------------------------------------------------------------
INF_Module::~INF_Module(){
    if(!stepGui.empty()){
        for(auto &x:stepGui){
            x.reset();
        }
        stepGui.clear();
    }
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
    cyclic->beatsPerBar = beatAmt * beatResolution;
    cyclic->bEuclid = true;
    
    Track t = Track(new Sequence());//Actual Sequence data
    t->index = seqAmt;
    
        if(cyclic->bEuclid == true){//if euclidean mode is enabled in initial state..
            //Add Euclidean Rhythm  (4:16)
            auto_ptr<Bjorklund>euclid = auto_ptr<Bjorklund>(new Bjorklund(16,4));
            euclid->init();
            t->setPattern(euclid->LoadSequence());
            cyclic->setSequence(t->pattern);
            euclid.reset();
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
    c->bEnabled = true;
    c->pos = guiLoc;
    c->setup();
    controls.push_back(c);
    ofAddListener(c->GuiCallback, this, &INF_Module::seqParamChanged);
    ofAddListener(c->sendPitch, this, &INF_Module::onNoteChange);
    ofAddListener(c->vectorRotated, this, &INF_Module::seqRotate);
    if(index ==0){
        //Add rest of objects
        for(int i=1; i < 8; i ++){
            seqAmt ++;
            cycleRad -= gap;
            
            CyclicSeq seq = CyclicSeq(new circleStep(rect_ptr->getCenter(), cycleRad));//Cyclic GUI
            Track t = Track(new Sequence());//Actual Sequence data
            
            //assigning index
            seq->bEuclid = true;
            seq->index = seqAmt;
            t->index = seqAmt;
            
            //controller setup
            GuiPtr c = GuiPtr(new INF_Controls());
            guiLoc.y += (26*7);
            if(seqAmt == 4 || seqAmt == 8){
                guiLoc.x += 270; //default width is 270;
                guiLoc.y = rect_ptr->getTopLeft().y;
            }
            c->pos = guiLoc;
            c->index = seqAmt;
            c->bEuclid = true;
            c->bEnabled = false;
            c->setup();
            controls.push_back(c);
            ofAddListener(c->GuiCallback, this, &INF_Module::seqParamChanged);
            ofAddListener(c->sendPitch, this, &INF_Module::onNoteChange);
            ofAddListener(c->vectorRotated, this, &INF_Module::seqRotate);
            
            //Cyclic Gui Setup
            seq->isEnabled = false;
            if(controls[seqAmt]->bEnabled == true){
                seq->stepAmt = controls[seqAmt]->seq_len;
            }else{
                seq->stepAmt = 0;
            }
            seq->setup();
            stepGui.push_back(seq);
            tracks.push_back(move(t));
            ofAddListener(seq->stepUpdated, this, &INF_Module::sequenceCallback);
        }
    }

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
    rb->setLabel("COMPSET");
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
void INF_Module::setMeter(int _amount, int _beatResolution){
    beatAmt = _amount;
    beatResolution = _beatResolution;
    
    if(stepGui.size() > 0 && controls.size() > 0){
        for(auto &x:stepGui){
            if(beatResolution ==4){
                x->beatsPerBar = beatAmt * beatResolution;
            }else if(beatResolution == 8){
                x->beatsPerBar = beatAmt * 2;
                cout<<beatAmt<<"/8"<<" "<<beatAmt*2<<endl;
            }else if(beatResolution == 16){
                x->beatsPerBar = beatAmt;
            }
            x->setup();
        }
        
        for(auto &x:controls){
            if(beatResolution ==4){
                int max =beatAmt * beatResolution;
                x->sliders[0]->setMax(max);
                x->sliders[0]->setValue(max);
                x->sliders[1]->setMax(max);
            }else if(beatResolution == 8){
                int max =beatAmt * 2;
                x->sliders[0]->setMax(max);
                x->sliders[0]->setValue(max);
                x->sliders[1]->setMax(max);
            }else if(beatResolution == 16){
                x->sliders[0]->setMax(beatAmt);
                x->sliders[0]->setValue(beatAmt);
                x->sliders[1]->setMax(beatAmt);
            }
        }
        
    }
}
//--------------------------------------------------------------
void INF_Module::onButtonEvent(ofxDatGuiButtonEvent e){
    //ADD SEQUENCE
    if(e.target->getLabel() == "+"){
        if(seqAmt <7){
            
            seqAmt ++;
            cycleRad -= gap;

            CyclicSeq seq = CyclicSeq(new circleStep(rect_ptr->getCenter(), cycleRad));//Cyclic GUI
            Track t = Track(new Sequence());//Actual Sequence data
            
            //assigning index
            seq->bEuclid = true;
            seq->index = seqAmt;
            t->index = seqAmt;
            
            //controller setup
            GuiPtr c = GuiPtr(new INF_Controls());
            guiLoc.y += (26*7);
            if(seqAmt == 4 || seqAmt == 8){
                guiLoc.x += 270; //default width is 270;
                guiLoc.y = rect_ptr->getTopLeft().y;
            }
            c->pos = guiLoc;
            c->index = seqAmt;
            c->bEuclid = true;
            c->bEnabled = false;
            c->setup();
            controls.push_back(c);
            ofAddListener(c->GuiCallback, this, &INF_Module::seqParamChanged);

            //Cyclic Gui Setup
            seq->isEnabled = false;
            if(controls[seqAmt]->bEnabled == true){
                seq->stepAmt = controls[seqAmt]->seq_len;
            }else{
                seq->stepAmt = 0;
            }
            seq->setup();
            stepGui.push_back(seq);
            tracks.push_back(move(t));
            ofAddListener(seq->stepUpdated, this, &INF_Module::sequenceCallback);
            
        }
        //ERASE SEQUENCE
    }else if(e.target->getLabel() == "-"){
        if(seqAmt > 0 && stepGui.size() > 1 && controls.size() > 1){
            stepGui[seqAmt].reset();
            tracks[seqAmt].reset();
            seqAmt --;
            cycleRad += gap;
            guiLoc.y -= (26*7);
            if(seqAmt == 4 || seqAmt == 8){
                guiLoc.x -= 270;
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
            SeqAgent = auto_ptr<INF_Sequencer>(new INF_Sequencer());
            
            if(controls[x->index]->bEuclid == true && x->isEnabled == true){
                if(x->index == 0){
                    do{
                        rand = (int)ofRandom(16);
                        if(rand > 1){
                            break;
                        }
                    }while(rand == 0 || rand == 1);
                    
                    SeqAgent->setup(16, rand, 4);
                    SeqAgent->generate(); //generate Euclidean Sequence
                    x->stepAmt = 16;
                    tracks[x->index]->setPattern(SeqAgent->getPattern());
                    x->setSequence(tracks[x->index]->pattern);
                    x->setup();
                    controls[x->index]->setSliders(16, rand);
                    
                }else{
                    int rand1 = (int)ofRandom(newStepAmt);
                    
                    do{
                        rand1 = (int)ofRandom(newStepAmt);
                        if(rand1 > 1){
                            break;
                        }
                    }while(rand1 == 0 || rand1 == 1);
                    SeqAgent->setup(newStepAmt, rand1, 4);
                    SeqAgent->generate(); //generate Euclidean Sequence
                    
                    x->stepAmt = newStepAmt;
                    tracks[x->index]->setPattern(SeqAgent->getPattern());
                    x->setSequence(tracks[x->index]->pattern);
                    x->setup();
                    controls[x->index]->setSliders(newStepAmt, rand1);
                }
            }
        }
    }else if(e.label == "COMPSET"){
        for(auto &x:stepGui){
            if(controls[x->index]->bComp == true && x->isEnabled == true){
                if(x->index >0){
                    int length, pulses;
                    SeqAgent = auto_ptr<INF_Sequencer>(new INF_Sequencer());
                    SeqAgent->makeComp(tracks[0]->getPattern());
                    tracks[x->index]->setPattern(SeqAgent->getPattern());
                    x->stepAmt = tracks[x->index]->length;
                    x->setSequence(tracks[x->index]->pattern);
                    x->setup();
                    controls[x->index]->setSliders(tracks[x->index]->length, tracks[x->index]->onset);
                }
            }
        
        }
        
    }
}
//--------------------------------------------------------------
void INF_Module::onDropdownEvent(ofxDatGuiDropdownEvent e){
    cout<<e.child<<endl;
}
//--------------------------------------------------------------
void INF_Module::sequenceCallback(SequenceEvent &e){
    if(e.index <= tracks.size())
        tracks[e.index]->pattern = e.seq;
};
//--------------------------------------------------------------
void INF_Module::onNoteChange(noteOut &n){
    ofLogNotice()<<n.index<<" "<<n.pitch<<endl;
//    tracks[n.index]->pitch = n.pitch;
    for(auto &x:tracks){
        if(x->index == n.index){
            x->pitch = n.pitch;
        }
    }
    
}
//--------------------------------------------------------------
void INF_Module::seqRotate(vOffset &e){
    int offset = e.offset;
    if(tracks[e.index]->pattern.size() > 1){
        rotate(tracks[e.index]->pattern.begin(), tracks[e.index]->pattern.end()-offset,tracks[e.index]->pattern.end());
        stepGui[e.index]->setSequence(tracks[e.index]->pattern);
    }
}
//--------------------------------------------------------------
void INF_Module::seqParamChanged(Controls &e){
    
    //this is the function which generates Euclidean Rhythm in various conditions
    vector<bool>output;
    vector<bool>::iterator outputIterator;
    Algorithms al;
    ofParameter<int> offset = 0;
    int seq_len, seq_pulse, target;
    
    seq_len = e.length;
    seq_pulse = e.pulse;
    offset = e.offset;
    target = e.target - 1;
    
    if(e.index < stepGui.size() && e.index < tracks.size()){
        stepGui[e.index]->stepAmt = e.length;
        stepGui[e.index]->isEnabled = e.isOn;
        
        if(seq_len != 0 && seq_pulse != 0){
            for(auto &x:controls){
                if(x->bEuclid == true && x->bEnabled == true){
                    SeqAgent = auto_ptr<INF_Sequencer>(new INF_Sequencer());
                    SeqAgent->setup(seq_len, seq_pulse, 4);
                    SeqAgent->generate();
                    tracks[e.index]->setPattern(SeqAgent->getPattern());
                    stepGui[e.index]->setSequence(tracks[e.index]->pattern);
                }else if(x->bComp == true && x->bEnabled == true){
//                    if(x->index != target){
//
//                    }
                }
            }
        }

        stepGui[e.index]->setup();
    }
}
//--------------------------------------------------------------
