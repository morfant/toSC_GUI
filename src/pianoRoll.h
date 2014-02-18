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
#include "Bar.h"
#include "Button.h"

typedef enum { NORMAL = '0', WRITE, ERASE } MODE_STATE;
//typedef enum { STOP, PLAYING } PLAYBUTTON_STATE;

class PianoRoll{
protected:
    
    int posX, posY;
    int fposX, fposY;
    int backWidth, backHeight;
    int frontWidth, frontHeight;
    int teum;
    int numOfBlock = 0;
    ofColor fBoxCol, fStrokeCol, bBoxCol, bStrokeCol;
    ofRectangle frontPanel, movingPanel;
    
    vector<Block> blocks;
    MODE_STATE keyMode = NORMAL;
    
    // Bar
    Bar playBar;
    int curPos;
    int playSpeed;
    
    // Buttons
    Button_PLAY playButton;
    BUTTON_STATE pState = DEACTIVE;
    
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
    
    void setKeyMode(MODE_STATE mode);
    MODE_STATE getKeyMode();
    
    void setPlaySpeed(int speedX);
    int getPlaySpeed();
    
    int blockAtMousePos(int x, int y);
    
    Button_PLAY* getPlayButton();
    void setPlayButtonState(BUTTON_STATE state);
    BUTTON_STATE getPlayButtonState();
    
    
    
    
    // update & draw
    void update();
    void draw();
    
};