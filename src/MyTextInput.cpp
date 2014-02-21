//
//  MyTextInput.cpp
//  oscSenderExample
//
//  Created by giy on 1/1/14.
//
//

#include "MyTextInput.h"

MyTextInput::MyTextInput(int x, int y, int w, int h){
    text = "";
    
    posX = x;
    posY = y;
    width = w;
    height = h;
    textPanel = ofRectangle(x, y, width, height);
    
    isForcus = NOT_FORCUS;
    
    sel_boxCol = ofColor(255);
    nsel_boxCol = ofColor(0, 100, 200);
    strokeCol = ofColor(0);
    
    fontHeight = 15;
    fontWidth = 8;
    
    cursorThickness = 2;
    
}

MyTextInput::~MyTextInput(){

}


// getter & setter
int
MyTextInput::getX(){
    return posX;
}

int
MyTextInput::getY(){
    return posY;
}

void
MyTextInput::setX(int x){
    posX = x;
}

void
MyTextInput::setY(int y){
    posY = y;
}

void
MyTextInput::setColor(ofColor sel_bc, ofColor nsel_bc, ofColor sc){
    sel_boxCol = sel_bc;
    nsel_boxCol = nsel_bc;
    strokeCol = sc;
}

void
MyTextInput::setFocus(MODE_FORCUS fState){
    isForcus = fState;
    cout << isForcus << endl;
}

MODE_FORCUS
MyTextInput::getFocus(){
    return isForcus;
}

bool
MyTextInput::getIsMouseOver(ofPoint testPoint){
    return isInsideRect(testPoint, textPanel);
}

int
MyTextInput::getTextPos(){
    return textPos;
}

void
MyTextInput::setTextPos(int x){
    textPos = x;
}

int
MyTextInput::getCursorPos(){
    return cursorX;
}

string*
MyTextInput::getText(){
    return &text;
}



//----------------LOOP----------------
void
MyTextInput::update(){
    
}

void
MyTextInput::draw(){
    
    ofPushStyle();
    //    ofFill();
    ofNoFill();
    
    if(isForcus == FORCUS){
        ofSetColor(sel_boxCol);
    }else{
        ofSetColor(nsel_boxCol);
    }
    
    ofRect(posX, posY, width, height);
    ofPopStyle();
    
    ofPushMatrix();
    ofTranslate(posX, posY);
    
    // cursor
    ofPushStyle();
    ofSetColor(255, 0, 0, 255);
    cursorX = textPos * fontWidth;
    ofLine(5 + cursorX, height - fontHeight, 5 + cursorX, fontHeight);
    ofPopStyle();
    
    ofDrawBitmapString(text, 5, fontHeight);
    ofPopMatrix();
}



