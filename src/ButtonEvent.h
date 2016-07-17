//
//  ButtonEvent.h
//  CircleTest
//
//  Created by Heewon Oh on 17/07/2016.
//
//

#ifndef ButtonEvent_h
#define ButtonEvent_h

struct ButtonEvent {

public:
    int index;
    string label;
    bool bClicked;
    
    ButtonEvent():index(0),bClicked(false){};
};

#endif /* ButtonEvent_h */
