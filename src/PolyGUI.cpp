//
//  PolyGUI.cpp
//  InfinityMachine-ALPHA
//
//  Created by Heewon Oh on 4/18/16.
//
//

#include "PolyGUI.h"

PolyGUI::PolyGUI(float _radius, ofVec3f &_pos, string &_typeTag):
    radius(_radius), pos(_pos), typeTag(_typeTag)
{
    point.setMode(OF_PRIMITIVE_POINTS);
    innerPoly.setMode(OF_PRIMITIVE_LINE_LOOP);
    outerPoly.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    //delete slash from typeTag.
    char chars[] = "/";
    for (unsigned int i = 0; i < strlen(chars); ++i)
    {
        typeTag.erase (std::remove(typeTag.begin(), typeTag.end(), chars[i]), typeTag.end());
    }
    
    
    //translation + getPosition (ofNode, ofMatrix4x4)
    setGlobalPosition(pos);
    m.translate(pos);
    createMesh();
    cout<<"[PolyGUI initialized] "<<ofGetElapsedTimef()<<endl;
}
//--------------------------------------------------------------
void PolyGUI::mouseOver(){
    //****has error.
    float disX = pos.x - ofGetMouseX();
    float disY = pos.y - ofGetMouseY();
    (sqrt(pow(disX, 2) + pow(disY,2)) < radius * 2 ) ? isFloat = 1 : isFloat = 0;
}
//--------------------------------------------------------------
void PolyGUI::createPoly(int seq_len){
    if(!step_Arr.empty())
        step_Arr.clear();
    innerPoly.clearVertices();
    outerPoly.clearVertices();
    
    int length = seq_len;
    float angle = 360.f / length;
    
    //iterate all position
    steps.clear();
    for(int i = 0; i < length; i++){
        steps.insert(steps.begin()+i, ofVec3f(radius * cos(angle*i*PI/180), radius * sin(angle*i*PI/180), 0));
    }
    
    //Inner Polygon - Polyline
    try{
        for(int i=0; i < length;i++){
            Step *s;
            outerPoly.addVertex(steps.at(i));
//            s = new Step(steps[i], 0);
//            step_Arr.insert(step_Arr.begin()+i,s);
        }
    }catch(out_of_range){
        cerr<<"[PolyGUI !!Sequence is out of range!!]"<<endl;
    }catch(exception& e){
        cerr<<"[PolyGUI: Exception is catched]"<<endl;
        cout<<e.what()<<endl;
    }
    
}
//--------------------------------------------------------------
void PolyGUI::createPoly(vector<bool>&seq){
    
    if(!step_Arr.empty())
        step_Arr.clear();
    innerPoly.clearVertices();
    outerPoly.clearVertices();

    int length = seq.size();
    float angle = 360.f / length;
    
    //iterate all position
    steps.clear();
    for(int i = 0; i < length; i++){
        steps.insert(steps.begin()+i, ofVec3f(radius * cos(angle*i*PI/180), radius * sin(angle*i*PI/180), 0));
    }
    
    
    //Inner Polygon - Polyline
    try{
        if(seq.size() > 0){
            for(int i=0; i < length;i++){
//                Step *s;
                outerPoly.addVertex(steps.at(i));
                if(seq[i] == true){
                
                    //updating vertex for polyline
                    innerPoly.addVertex(steps.at(i)); //front vertices
//                    s = new Step(steps[i],1);
                }else{
//                    s = new Step(steps[i],0);
                }
//                step_Arr.insert(step_Arr.begin()+i,s);
            }
        }
    }catch(out_of_range){
        cerr<<"[PolyGUI !!Sequence is out of range!!]"<<endl;
        for(auto x: seq)
            cout<<x;
    }catch(exception& e){
        cerr<<"[PolyGUI: Exception is catched]"<<endl;
        cout<<e.what()<<endl;
    }
}
//--------------------------------------------------------------
void PolyGUI::createMesh(){

    float x,y;
    float circlepts = 200;
    float innerRadius = radius + 50;
    float outerRadius = innerRadius + 1.2;
    
    //cFrame
    vector<ofVec3f>innerCircleMeshOutline;
    //Front Face.
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    meshOutline.setMode(OF_PRIMITIVE_LINE_LOOP);
    for(int i = 0; i <= circlepts; i++){
        
        float angle = i * TWO_PI  / circlepts;
        x = outerRadius * cos(angle);
        y = outerRadius * sin(angle);
        mesh.addVertex(ofVec3f(x, y, 0));
        meshOutline.addVertex(ofVec3f(x, y, 0));
        mesh.addColor(ofFloatColor(1,1,1));
        
        x = innerRadius * cos(angle);
        y = innerRadius * sin(angle);
        
        mesh.addVertex(ofVec3f(x,y,0));
        mesh.addColor(ofFloatColor(1,1,1));
        // adding the inner circle points to a vector because they need to be in reverse order.
        innerCircleMeshOutline.push_back(ofVec3f(x,y,0));
    }
    std::reverse(innerCircleMeshOutline.begin(), innerCircleMeshOutline.end());
    meshOutline.addVertices(innerCircleMeshOutline);
    meshOutline.addColor(ofFloatColor(1,1,1));
}
//--------------------------------------------------------------
void PolyGUI::draw(){
    
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    ofPushMatrix();
    ofMultMatrix(m);
    
    //Circle Frame
    ofSetLineWidth(1);
        meshOutline.draw();
        meshOutline.clear();
    ofSetLineWidth(0);
        mesh.draw();
    
    //outer polyline
    ofSetLineWidth(2);
    ofSetColor(255,255,120);
    
        outerPoly.draw();
    ofSetColor(ofColor::red);
    ofSetLineWidth(3);
    
        innerPoly.drawFaces();
    

    for(int i=0; i < step_Arr.size();i++){
        //draw all steps
        step_Arr[i]->render();
    }
    
    ofPopMatrix();
}
