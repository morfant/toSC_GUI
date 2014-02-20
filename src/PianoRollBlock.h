//
//  PianoRollBlock.h
//  toSC
//
//  Created by giy on 2/17/14.
//
//

#pragma once
#include <iostream>
#include "ofMain.h"

typedef enum {SELECTED, NOT_SELECTED} BLOCK_STATE;

class Block{

protected:
    int beginX, beginY;
    int endX, endY;
    
    int width, height;
    
    ofColor sel_blockColor, nsel_blockColor;
    ofColor lineColor;
    BLOCK_STATE state;
    
    float freq, amp, env;

public:
    Block(int x, int y);
    ~Block();
    
    void setPos(int x, int y);
    void setPos(ofPoint pos);
    ofPoint getPos();
    int getBeginX();
    
    void setWidth(int width);
    int getWidth();
    int getHeight();
    BLOCK_STATE getState();
    void setState(BLOCK_STATE _state);
    
    
    void setBlockColor(ofColor _selblockColor, ofColor _nselblockColor);
    void setLineColor(ofColor arg_lineColor);
    
    ofColor getBlockColor();
    ofColor getLineColor();
    
    
};

