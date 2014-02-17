//
//  MyTextInput.cpp
//  oscSenderExample
//
//  Created by giy on 1/1/14.
//
//

#include "MyTextInput.h"

MyTextInput::MyTextInput(int x, int y){
    text = "";
    posX = x;
    posY = y;
    width = 100;
    height = 20;
    boxCol = ofColor(255);
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
MyTextInput::setColor(ofColor boxC, ofColor strokeC){
    boxCol = boxC;
    strokeCol = strokeC;
}


void
MyTextInput::update(){

}

void
MyTextInput::draw(){
    
    ofPushStyle();
//    ofFill();
    ofNoFill();
    ofSetColor(boxCol);
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


void
MyTextInput::isFocus(int x, int y){

    if(x >= posX && x <= (posX + width) && y >= posY && y <= (posY + height)){
        cout << "ooo" << endl;
        isMouseOver = true;
        setColor(ofColor(255, 0, 0, 90), ofColor(255));
    }else{
        isMouseOver = false;
        setColor(ofColor(255), ofColor(0));
    }
}


bool
MyTextInput::getIsMouseOver(){
    return isMouseOver;
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


