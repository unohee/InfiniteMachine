//
//  ImageButton.cpp
//  GuiTest
//
//  Created by Heewon Oh on 29/06/2016.
//
//

#include "ImageButton.h"

ImageButton::ImageButton(string path, string _label):isClicked(false), label(_label){
    img.load(path);
    ofRegisterMouseEvents(this);
}
void ImageButton::setPosition(int x, int y){
    pos.x = x;
    pos.y = y;
    this->pos.x = x;
    this->pos.y = y;
}
void ImageButton::setSize(int _size){
    this->size = _size;
}
void ImageButton::render(){
    img.draw(pos, size, size);
}
void ImageButton::mouseReleased(ofMouseEventArgs & args){
    if (inside(args.x, args.y)) {
        isClicked = !isClicked;
        customEvent * e = new customEvent();
        e->label = label;
        e->toggle = isClicked;
        // if the mouse is pressed over the circle an event will be notified (broadcasted)
        // the circleEvent object will contain the mouse position, so this values are accesible to any class that is listening.
        ofNotifyEvent(buttonClicked, *e, this);
    }
}
bool ImageButton::inside(float _x, float _y ){
    return (ofVec2f(_x, _y).distance(ofVec2f(pos.x, pos.y)) < size);
}