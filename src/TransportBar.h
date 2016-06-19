//
//  TransportBar.h
//  InfinityMachine-ALPHA
//
//  Created by Heewon Oh on 4/24/16.
//
//
#pragma once

#include "DatPanel.h"


class TransportBar : public DatPanel{
public:
    TransportBar():netAddress("localhost:8080"){
        
    };
    ~TransportBar(){
        
    }
    void setup();
    void update(float windowWidth);
    void draw();
    
    void bpmChanged(ofxDatGuiSliderEvent e){
        bpm = e.value;
    }
    void setNetwork(ofxDatGuiTextInputEvent e){
        bool isCorrect;
        string test = e.text;
        string regex = ":";
        std::size_t found = test.find(regex);
        if(found !=std::string::npos){
            vector<string> iter = ofSplitString(e.text, ":", true, true);
            for(int i=0; i < iter.size(); ++i){
                try{
                    ip_adrs = iter[0];
                    port_adrs = std::stoi(iter[1]);
                    isCorrect = true;
                }
                catch (const std::invalid_argument& ia){
                    ofSystemAlertDialog("PORT :: Invalid argument");
                    std::cerr << "PORT :: Invalid argument: " << ia.what() << '\n';
                    isCorrect = false;
                }
            }
            if(isCorrect){
                setIP(ip_adrs);
                setPort(port_adrs);
                cout<<"<Network established>"<<endl;
                cout<<"<"<<ip_adrs<<":"<<port_adrs<<">"<<endl;
            }
        }else{
            ofSystemAlertDialog("Error : \nType address by this convention:\n[address:port]");
            std::cerr<<"Error : type address by this convention-> address:port"<<endl;
        }

    };
    void setPlayback(ofxDatGuiButtonEvent e){
//        start = e.checked();
//        e.checked;
    }
    
    string setIP(string ip){
        s = ip;
    }
    int setPort(int port){
        p = port;
    }
    
    int getSize(){return components.size();}
    int getBPM(){return bpm;}
    string getIP(){return s;}
    int getPort(){return p;}
    string getAddress(){return netAddress;}
    bool play(){return start;}
    
    //ofxDatGUI
    bool start; // toggle for ofxdatgui / playback.
    int bpm; //global bpm paramter
    string ip_adrs; //ip
    int port_adrs; //port
    
    string s; int p;
    string netAddress;
    
};