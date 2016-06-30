#pragma once
#include "ofMain.h"
#include "ImageButton.h"

class ButtonEvent {
public:

    
    ButtonEvent(ImageButton *t) {
        target = t;
    }

    ImageButton *target;
};