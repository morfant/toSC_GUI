//
//  Track.cpp
//  toSC
//
//  Created by giy on 2/21/14.
//
//

#include "Track.h"

Track::Track(){
    
    pPianoRoll = new PianoRoll();
    pTextInput = new TextInput(
        pPianoRoll->getPosX(),
        pPianoRoll->getPosY(), 200, 600);
    pPianoRoll->init();
    pTextInput->init();
    
    
}

Track::~Track(){
}


void
Track::update(){
    pPianoRoll->update();
    pTextInput->update();
}


void
Track::draw(){
    pPianoRoll->draw();
    pTextInput->draw();
    
	// display instructions
//	string buf;
//	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
//	ofDrawBitmapString(buf, 10, 20);
//	ofDrawBitmapString("move the mouse to send osc message [/mouse/position <x> <y>]", 10, 50);
//	ofDrawBitmapString("click to send osc message [/mouse/button <button> <\"up\"|\"down\">]", 10, 65);
    
}

