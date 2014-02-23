//
//  Track.h
//  toSC
//
//  Created by giy on 2/21/14.
//
//


#pragma once
#include <iostream>
#include "ofxOsc.h"
#include "TextInput.h"
#include "PianoRoll.h"


class Track{
protected:
    
    PianoRoll*      pPianoRoll;
    TextInput*      pTextInput;

    
public:
    Track();
    ~Track();
    
    PianoRoll*      getPianoRoll();
    TextInput*      getTextInput();
    
    void init();    
    void update();
    void draw();
    

    
};
