//
//  Bar.cpp
//  toSC
//
//  Created by giy on 2/18/14.
//
//

#include "Bar.h"

Bar::Bar(){
}

Bar::Bar(int x){
    posX = x;
    color = ofColor(0);
}

Bar::~Bar(){
}

void
Bar::setPos(int x){
    posX = x;
}

int
Bar::getPos(){
    return posX;
}

void
Bar::setColor(ofColor barColor){
    color = barColor;
}

ofColor
Bar::getColor(){
    return color;
}

void
Bar::draw(){
    ofPushStyle();
    ofSetColor(color);
    ofNoFill();
    ofLine(posX, 0, posX, ofGetHeight());
    ofPopStyle();
}