//
//  Button.cpp
//  toSC
//
//  Created by giy on 2/18/14.
//
//

#include "Button.h"

Button::~Button(){
    posX = ofGetWidth()/2;
    posY = ofGetHeight()/2;
    width = 20;
    height = 20;
    ofColor bColor = ofColor(255);
    ofColor fColorOn = ofColor(255, 0, 0);
    ofColor fColorOff = ofColor(0);
    
    BUTTON_STATE butState = DEACTIVE;
    bisMouseOn = FALSE;
}

Button::Button(int x, int y){
    posX = x;
    posY = y;
    width = 20;
    height = 20;
    ofColor bColor = ofColor(255);
    ofColor fColorOn = ofColor(0);
    ofColor fColorOff = ofColor(0, 100, 50);
    
    BUTTON_STATE butState = DEACTIVE;
}

void
Button::setPos(int  x, int y){
    posX = x;
    posY = y;
}

int
Button::getPosX(){
    return posX;
}

int
Button::getPosY(){
    return posY;
}

void
Button::setWidth(int arg_width){
    width = arg_width;
}

void
Button::setHeight(int arg_height){
    height = arg_height;
}

int
Button::getWidth(){
    return width;
}

int
Button::getHeight(){
    return height;
}

void
Button::setColor(ofColor bCol, ofColor fColOn, ofColor fColOff){
    bColor = bCol;
    fColorOn = fColOn;
    fColorOff = fColOff;
}

ofColor
Button::getBgColor(){
    return bColor;
}

ofColor
Button::getFColorOn(){
    return fColorOn;
}

ofColor
Button::getFColorOff(){
    return fColorOff;
}

void
Button::setState(BUTTON_STATE state){
    butState = state;
}

BUTTON_STATE
Button::getState(){
    return butState;
}

void
Button::draw(int posX, int posY){
    
}

bool
Button::isMouseOn(int x, int y){
    
    ofPoint tPoint = ofPoint(x, y);
    ofRectangle tRect = ofRectangle(posX, posY, width, height);
    
    if(isInsideRect(tPoint, tRect)){
//        cout << "Mouse is on button." << endl;
        return TRUE;
    }else{
//        cout << "No mouse is on button." << endl;
        return FALSE;
    }
}

// Real Buttons
//---------------- PlayButton ----------------
Button_PLAY::Button_PLAY() : Button(0, 0){
}

Button_PLAY::~Button_PLAY(){
}

void
Button_PLAY::draw(int _posX, int _posY){
    posX = _posX;
    posY = _posY;
    
    ofPushStyle();
    ofSetColor(bColor);
    ofFill();
    ofRect(posX, posY, width, height);

    if(butState == ACTIVE) ofSetColor(fColorOn);
    else ofSetColor(fColorOff);
    ofTriangle(posX+5, posY+5, posX+15, posY+10, posX+5, posY+15);
    ofPopStyle();
}









