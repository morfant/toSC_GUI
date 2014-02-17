//
//  pianoRoll.h
//  toSC
//
//  Created by giy on 2/3/14.
//
//

#pragma once

#include <iostream>
#include "ofMain.h"
#include "PianoRollBlock.h"

//enum keyMode {
//    NORMAL, WRITE, ERASE
//};

class PianoRoll{
protected:
    
    int posX, posY;
    int backWidth, backHeight;
    int frontWidth, frontHeight;
    int teum;
    int numOfBlock = 0;
    ofColor fBoxCol, fStrokeCol, bBoxCol, bStrokeCol;
    ofRectangle frontPanel, movingPanel;
    
    bool isMouseOver;
    
    vector<Block> blocks;
    
    int keyMode = 0;
    
    
public:
    
    // constructor & destructor
    PianoRoll(int x, int y);
    ~PianoRoll();
    
    // Block
    void makeBlock(int x, int y);
    void eraseBlock(int blockNum);
    void drawBlocks();
    int getBlockNum();
    
    // getter & setter
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setColor(ofColor boxCol, ofColor strokeCol);
    
    bool getIsMouseOver();
    
    void setKeyMode(int mode);
    int getKeyMode();
    
    bool isInRange(int specNum, int min, int max);
    int blockAtMousePos(int x, int y);
    
    // update & draw
    void update();
    void draw();
    
};