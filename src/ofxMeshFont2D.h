
#pragma once
#include "ofMain.h"
using namespace std;
//2D Font Extrusion for the use of GUI in 3D Interaction..

class ofxMeshFont2D : public ofTrueTypeFont{
    
public:
    
    ofxMeshFont2D(){
        
    };
    virtual ~ofxMeshFont2D(){
        
    };
    void loadFont(string file, int size){
        //this should be executed only once..
        ofTrueTypeFont::load(file, size,true,true,true);

    }
    void createNewString(string input){
        letterPaths = getStringAsPoints(input);
        bbox = getStringBoundingBox(input, 0, 0);
        for(int i=0; i<letterPaths.size(); i++)
        {
            ofMesh front = letterPaths[i].getTessellation();
            typeFaceMesh.insert(typeFaceMesh.begin()+i, front);
        }
    }
    void drawAsMesh() {
        ofPushMatrix();
        ofTranslate(position);
        ofTranslate(0, bbox.height/2.0);
        ofRotateX(180);
        for(int i=0; i<typeFaceMesh.size(); i++)
        {
            typeFaceMesh[i].draw();
            typeFaceMesh[i].clear();
        }
        ofPopMatrix();
    }
    vector<ofMesh>typeFaceMesh;
    ofRectangle bbox;
    ofVec3f position;

    vector<ofTTFCharacter> letterPaths;
    
    
};