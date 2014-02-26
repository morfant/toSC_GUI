//
//  PianoRoll.h
//  toSC
//
//  Created by giy on 2/3/14.
//
//

#pragma once

#include <iostream>
#include "ofMain.h"
#include "ofEvents.h"
#include "PianoRollBlock.h"
#include "Bar.h"
#include "Button.h"
#include "Osc.h"


typedef enum { NORMAL = '1', WRITE, ERASE } MODE_STATE;
//typedef enum { STOP, PLAYING } PLAYBUTTON_STATE;

class PianoRoll{
protected:
    
    int             posX, posY;
    int             rollPanelPosX, rollPanelPosY;
    int             rollPanelWidth, rollPanelHeight;
    int             keyPanelWidth, keyPanelHeight;
    int             teum;
    int             numOfBlock = 0;
    ofColor         fBoxCol, fStrokeCol, bBoxCol, bStrokeCol;
    ofRectangle     keyPanel, rollPanel;
    
    vector<Block*>  blocks;
    vector<int>     selIdx;
    
    MODE_STATE      keyMode = NORMAL;
    
    // Bar
    Bar             playBar;
    int             curPos;
    int             playSpeed;
    bool            atEnd;
    
    // Buttons
    Button_PLAY     playButton;
    BUTTON_STATE    pState = DEACTIVE;
    
    // Control
    bool            isOnRollPanel;
    bool            isOnKeyPanel;
    int             lastBlockNum;
    bool            triggered;

    

    
public:
    
    // constructor & destructor
    PianoRoll();
    ~PianoRoll();
    
    void init();
    
    // Block
    void selectBlock(int blockIdx);
    void unSelectAllBlocks();
    
    void makeBlock(int x, int y);
    void eraseBlock(int blockIdx);
    void drawBlocks();
    int getBlockNum();
    
    // getter & setter
    int getPosX();
    int getPosY();
    void setPosX(int x);
    void setPosY(int y);
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
    void	keyPressed(int key);
	void	keyPressedEvent(ofKeyEventArgs &a);
    void mousePressedEvent(ofMouseEventArgs &m);
    void mousePressed(int x, int y, int button);
    
    bool getMouseIsOnRollPanel(ofPoint testPoint);
    bool getMouseIsOnKeyPanel(ofPoint testPoint);
    void sortBlockPos(vector<Block*>* vec);
    void playButtonAction();
    void isHit();
    void setCurPos(int pos);
    void findLastBlockNum(int x);

    
    
    // OSC
    Osc*    pOsc;
    
    // update & draw
    void update();
    void draw();
    
};