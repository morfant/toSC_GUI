//
//  TextInput.h
//  oscSenderExample
//
//  Created by giy on 1/1/14.
//
//

#pragma once

#include <iostream>
#include "ofMain.h"
#include "ofEvents.h"
#include "Functions.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 57120


typedef enum {
    FORCUS, NOT_FORCUS
} MODE_FORCUS;

typedef enum {
    NONE, ROUND_BRACKET, SQUARE_BRACKET, BRACE
} TYPE_BRACKET;

typedef struct {
    int pos;
    TYPE_BRACKET bracketType = NONE;
} BRACKET;

class TextInput{
protected:
    
    int posX, posY;
    int width = 290;
    int height = 100;
    
    ofRectangle textPanel;
    ofColor sel_boxCol, nsel_boxCol, strokeCol, txtCol,
            bgBlockCol, bgBlockCol_warn;

    MODE_FORCUS isForcus = NOT_FORCUS;

    string text;
    
    int padT = 5;
    int padL = 5;
    int cursorThickness = 2;
    
    float fontHeight = 13.55f;
    int fontWidth = 8;
    
    int cursorX = 0;
    int textPos = 0;
    int lineNum = 0;
    int posInLine = 0;
    int linePos = 0;
    int bottomOver = 0;
    int lineLimit = 100;
    vector<int> cNumOfLines;
    
    int blockBegin = 0;
    int blockEnd = 0;


    
public:

    
    // constructor & destructor
    TextInput(int x, int y);    
    TextInput(int x, int y, int width, int height);
    ~TextInput();
    
    void    init();
    
    // getter & setter
    int     getX();
    int     getY();
    void    setX(int x);
    void    setY(int y);
    void    setColor(
            ofColor sel_bc, ofColor nsel_bc, ofColor sc);
    
    bool    getIsMouseOver(ofPoint testPoint);
    void    setFocus(MODE_FORCUS fState);
    MODE_FORCUS getFocus();
    
    int     getTextPos();
    void    setTextPos(int x);
    string* getText();
    void    clear();
    void	keyPressed(int key);
	void	keyPressedEvent(ofKeyEventArgs &a);
    void    mousePressed(int x, int y, int button);
    void    mousePressedEvent(ofMouseEventArgs &m);
    
    int     getCharNumOfLine(int lineNum, string text);
    int     getFirstPos(int lineNum, string text);
    void    viewStringInChar(string text);
    bool    chkBracketsOpen(int key);
    bool    chkBracketsClose(int key);
    void    chkBracketMatching();
    int     isSameShapeBracket();
    vector<BRACKET> openBrackets;
    vector<BRACKET> closeBrackets;
    int     nTab = 0;
    bool    nTabBool = false;
    void    insertIndention(int nTab);
    void    keyUP();
    void    keyDOWN();
    void    keyLEFT();
    void    keyRIGHT();
    void    keyRETURN();
    void    keyBACKSPACE();
    void    keyDEL();
    void    makeBgBlock(int textPos);
    void    makeBgBlockRange(int bPos, int ePos);
    
    ofPoint textPosToPixel(int textPos);
    vector<int> blockPos;
    

    
    
    
    
    // update & draw
    void    update();
    void    draw();

    
    // OSC
    ofxOscSender sender;
    void    sendOSC(string destAddr, string cmd);
    

    
    
    
    
};