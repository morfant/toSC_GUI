//
//  PianoRollBlock.cpp
//  toSC
//
//  Created by giy on 2/17/14.
//
//

#include "PianoRollBlock.h"

Block::Block(int x, int y){
    posX = x;
    posY = y;
    
    blockColor = ofColor(50, 100, 20);
    lineColor = ofColor(150, 10, 20);
}


Block::~Block(){
    
}

void
Block::setPos(int x, int y){
    posX = x;
    posY = y;
}


void
Block::setPos(ofPoint arg_pos){
    posX = arg_pos.x;
    posY = arg_pos.y;
}


ofPoint
Block::getPos(){
    return ofPoint(posX, posY);
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

// Color
void
Block::setBlockColor(ofColor arg_blockColor){
    blockColor = arg_blockColor;
}


void
Block::setLineColor(ofColor arg_lineColor){
    lineColor = arg_lineColor;
}

ofColor
Block::getBlockColor(){
    return blockColor;
}

ofColor
Block::getLineColor(){
    return lineColor;
}





