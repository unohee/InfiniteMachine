//
//  DatBox.h
//  GuiTest
//
//  Created by Heewon Oh on 23/06/2016.
//
//

#ifndef DatBox_h
#define DatBox_h

#include "ofxDatGui.h"

class DatButton{
    
public:
    ofPoint pos;
    float size;
    int label;
    int *index;
    ofxDatGuiButton *b;
    string nb_index;
    bool call_this;

    DatButton(): b(NULL){};
    //note that I changed fontsize in ofxDatGuiTheme.h
    DatButton(ofPoint p, int *_ind): pos(p), index(_ind){
        if(index != NULL)
            nb_index = to_string(*index);
        
        b = new ofxDatGuiButton(nb_index);
        b->setStripe(ofColor(0), 0);
        b->setPosition(pos.x, pos.y);
        b->onButtonEvent(this, &DatButton::onButtonEvent);
        b->setWidth(30);
        
        if(index != NULL)
            cout<<"[DatButton created:: "<< *index<<"]"<<endl;
    }
    ~DatButton(){
        try {
            if(b !=NULL)delete b;
            
            cout<<"[DatButton deleted:: "<< *index<<"]"<<endl;
        } catch (exception e) {
            cout<<e.what()<<endl;
        }
        
    }
    void update(){
        b->update();
    }
    
    void render(){
        b->draw();
    }
    void onButtonEvent(ofxDatGuiButtonEvent e){
        if (e.target == b){
            call_this = true;
            string label_str = e.target->getLabel();
            label = std::stoi(label_str);
            cout<<label-1<<endl;
        }else{
            call_this = false;
        }
    };
    
    ofPoint getPos(){
        ofPoint p_this(b->getX(), b->getY());
        return p_this;
    }
    float getWidth(){return 30;}
    int getIndex(){return label-1;};
    
    
};

#endif /* DatBox_h */
