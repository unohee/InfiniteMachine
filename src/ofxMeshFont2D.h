
#pragma once
#include "ofMain.h"
#include "INF_Utils.h"
//2D Font Extrusion for the use of GUI in 3D Interaction..

class ofxMeshFont2D : public ofTrueTypeFont{
    
public:
    
    ofxMeshFont2D(string _path, int _size):path(_path), size(_size){
        ofTrueTypeFont::load(path, size,true,true,true);
    };
    ~ofxMeshFont2D(){
        
    };
    
    void createNewString(string input){
        if(!typeFaceMesh.empty())
            for(int i=0; i <typeFaceMesh.size();i++)
                typeFaceMesh[i].clearVertices();
        
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
        }
        ofPopMatrix();
    }
    string path;
    int size;
    vector<ofMesh>typeFaceMesh;
    ofRectangle bbox;
    ofVec3f position;

    vector<ofTTFCharacter> letterPaths;
    
    
};