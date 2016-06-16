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
    
    //loadFont
    gui_id.loadFont("verdana.ttf", 18);
    gui_adrs.loadFont("verdana.ttf", 14);
    
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
void PolyGUI::createPoly(vector<bool>&seq){
    
    //for Euclidean Rhythm notation..
    if(!step_Arr.empty())
        step_Arr.clear();
    
    innerPoly.clearVertices();
    outerPoly.clearVertices();

    int length = seq.size();
    float angle = 360.f / length;
    ofColor c;
    c.set(122, 122, 122);
    
    //iterate all position
    steps.clear();
    for(int i = 0; i < length; i++){
        steps.insert(steps.begin()+i, ofVec3f(radius * cos(angle*i*PI/180), radius * sin(angle*i*PI/180), 0));
    }
    //Inner Polygon - Polyline
        glPointSize(15);
    
    try{
        if(seq.size() > 0){
            for(int i=0; i < length;i++){
                Step *s;
                outerPoly.addVertex(steps.at(i));
                if(seq[i] == true){
                
                    //updating vertex for polyline
                    innerPoly.addVertex(steps.at(i)); //front vertices
//                    point.addVertex(steps.at(i));
//                    point.addColor(ofFloatColor(1,0,0));
                    s = new Step(steps[i],1);
                }else{
                    s = new Step(steps[i],0);
                }
                step_Arr.insert(step_Arr.begin()+i,s);
//                step_Arr.push_back(s);
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
    float circlepts = 100;
    float innerRadius = radius + 7.5;
    float outerRadius = innerRadius + radius /8;
    
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

    //rectFrame
    ofVec3f rects[4];
    width = outerRadius;
    rects[0]=ofVec3f(-width,width, 0);
    rects[1]=ofVec3f(width, width, 0);
    rects[2]=ofVec3f(width,-width, 0);
    rects[3]=ofVec3f(-width,-width,0);
    vector<ofVec3f>frameOutline;

    //Polyline
    polyLine.setMode(OF_PRIMITIVE_LINE_LOOP);
    for(int i=0; i < 4;i++){
        polyLine.addVertex(rects[i]);
        polyLine.addColor(ofColor::red);
        polyLine.addIndex(i);
        frameOutline.push_back(rects[i]);
    }
    std::reverse(frameOutline.begin(), frameOutline.end());
    polyLine.addVertices(frameOutline);

//    //----------------------------------------------------------
//    //FONT RENDERING
//    gui_id.setGlobalDpi(96);
//    gui_id.createNewString(typeTag); //typeTag
//    gui_id.position = ofVec3f(-30, -20, 0);
//    
//    gui_adrs.position = ofVec3f(-90,-70,0);
//    gui_adrs.createNewString(address); //network address
////    fonts.push_back(*newFont);
////    fonts.push_back(*newFont);
//
////    //Display Sequence size
////    stringstream seq;
////    seq << pulses<< " / "<<length;
////    newFont->createNewString(seq.str());
////    newFont->position = rects[3];
////    fonts.push_back(*newFont);
//    cout<<"Mesh is generated."<<endl;
}
//--------------------------------------------------------------
void PolyGUI::draw(){
    
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
    ofPushMatrix();
    ofMultMatrix(m);
    ofSetLineWidth(lineWidth);
    
    if(isFloat)
        polyLine.draw();
    
    //TEXT DISPLAYS----
//    stringstream elapsedTime;
//    if(trigger){
//        elapsedTime << ofGetElapsedTimef();
//    }else{
//        elapsedTime << "0.00000";
//    }
//    font->createNewString(elapsedTime.str());
//    ofSetColor(255, 0, 15);
//    font->position = rects[0];
//    font->drawAsMesh();
    //-----------------
    
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
//        point.draw();
    ofPopMatrix();
    
    
    


//    if(isFloat){//rectFrame is only visible when mouse is floating onto GUI
//        //Rectangle Frame
//        //    }

    //Cyclical Polygon

    
//    ofPushMatrix();
//    ofRotateY(180);
//    gui_id.drawAsMesh();
//    gui_adrs.drawAsMesh();
//    for(int i=0;i < fonts.size();i++){
//        fonts[i].drawAsMesh();
//    }
//    for(auto fonts:fonts)fonts.drawAsMesh();
//    ofPopMatrix();
//    ofPopMatrix();
}
