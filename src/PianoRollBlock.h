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

class Block{

protected:
    int beginX, beginY;
    int endX, endY;
    
    int width, height;
    
    ofColor blockColor;
    ofColor lineColor;
    
    float freq, amp, env;

public:
    Block(int x, int y);
    ~Block();
    
    void setPos(int x, int y);
    void setPos(ofPoint pos);
    ofPoint getPos();
    
    void setWidth(int width);
    int getWidth();
    int getHeight();
    
    
    void setBlockColor(ofColor arg_blockColor);
    void setLineColor(ofColor arg_lineColor);
    
    ofColor getBlockColor();
    ofColor getLineColor();
    
    
};

