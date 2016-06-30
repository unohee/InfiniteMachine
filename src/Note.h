//
//  Note.h
//  GuiTest
//
//  Created by Heewon Oh on 27/06/2016.
//
//

#ifndef Note_h
#define Note_h
enum NOTE_STATUS {KEY_ON, KEY_OFF};

struct Note{
    
    Note():pitch(0), velocity(0), status(KEY_OFF){
    };
    ~Note(){
        
    };
    NOTE_STATUS status;
    int pitch;
    int velocity;
    
};

#endif /* Note_h */
