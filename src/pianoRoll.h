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


typedef enum { NORMAL = '1', WRITE, ERASE } MODE_STATE;
//typedef enum { STOP, PLAYING } PLAYBUTTON_STATE;

class PianoRoll{
protected:
    
    int posX, posY;
    int rollPanelPosX, rollPanelPosY;
    int rollPanelWidth, rollPanelHeight;
    int keyPanelWidth, keyPanelHeight;
    int teum;
    int numOfBlock = 0;
    ofColor fBoxCol, fStrokeCol, bBoxCol, bStrokeCol;
    ofRectangle keyPanel, rollPanel;
    
    vector<Block*> blocks;
    vector<int> selIdx;
    
    MODE_STATE keyMode = NORMAL;
    
    // Bar
    Bar playBar;
    int curPos;
    int playSpeed;
    
    // Buttons
    Button_PLAY playButton;
    BUTTON_STATE pState = DEACTIVE;
    
    // Control
    bool isOnRollPanel;
    bool isOnKeyPanel;
    
public:
    
    // constructor & destructor
    PianoRoll(int x, int y);
    ~PianoRoll();
    
    // Block
    void selectBlock(int blockIdx);
    void unSelectAllBlocks();
    
    void makeBlock(int x, int y);
    void eraseBlock(int blockIdx);
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
//    BUTTON_STATE getPlayButtonState();
    
    // Control
    bool getMouseIsOnRollPanel(ofPoint testPoint);
    bool getMouseIsOnKeyPanel(ofPoint testPoint);
    void sortBlockPos(vector<Block*>* vec);
    void playButtonAction();

    
    
    
    // update & draw
    void update();
    void draw();
    
};