#pragma once
#include "ofMain.h"
#include "ImageButton.h"

class ImgButtonEvent {
public:

    
    ImgButtonEvent(ImageButton *t) {
        target = t;
    }

    ImageButton *target;
};