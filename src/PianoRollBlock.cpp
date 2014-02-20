//
//  PianoRollBlock.cpp
//  toSC
//
//  Created by giy on 2/17/14.
//
//

#include "PianoRollBlock.h"

Block::Block(int x, int y){
    beginX = x;
    beginY = y;
    
    width = 40;
    height = 10;

    sel_blockColor = ofColor(250, 100, 20);
    nsel_blockColor = ofColor(50, 100, 20);
    lineColor = ofColor(150, 10, 20);

    state = NOT_SELECTED;
    
    freq = 0.f;
    amp = 0.f;
    env = 0.f;

}


Block::~Block(){
    
}

void
Block::setPos(int x, int y){
    beginX = x;
    beginY = y;
}


void
Block::setPos(ofPoint arg_pos){
    beginX = arg_pos.x;
    beginY = arg_pos.y;
}


ofPoint
Block::getPos(){
    return ofPoint(beginX, beginY);
}

int
Block::getBeginX(){
    return beginX;
}

void
Block::setWidth(int arg_width){
    width = arg_width;
}


int
Block::getWidth(){
    return width;
}

int
Block::getHeight(){
    return height;
}

BLOCK_STATE
Block::getState(){
    return state;
}

void
Block::setState(BLOCK_STATE _state){
    state = _state;
}


// Color
void
Block::setBlockColor(ofColor _selblockColor, ofColor _nselblockColor){
    sel_blockColor = _selblockColor;
    nsel_blockColor = _nselblockColor;
}

void
Block::setLineColor(ofColor arg_lineColor){
    lineColor = arg_lineColor;
}

ofColor
Block::getBlockColor(){
    return (state == SELECTED) ?
    sel_blockColor : nsel_blockColor;
}

ofColor
Block::getLineColor(){
    return lineColor;
}





