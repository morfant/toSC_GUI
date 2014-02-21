//
//  MyTextInput.h
//  oscSenderExample
//
//  Created by giy on 1/1/14.
//
//

#pragma once

#include <iostream>
#include "ofMain.h"
#include "Functions.h"

typedef enum {FORCUS, NOT_FORCUS} MODE_FORCUS;

class MyTextInput{
protected:
    
    int posX, posY;
    int width, height;
    ofRectangle textPanel;
    ofColor sel_boxCol, nsel_boxCol, strokeCol;

    MODE_FORCUS isForcus;

    string text;
    
    int cursorX, cursorY;
    int fontHeight, fontWidth;
    int cursorThickness;
    int textPos;
    
    
public:
    
    // constructor & destructor
    MyTextInput(int x, int y, int width, int height);
    ~MyTextInput();
    
    
    // getter & setter
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setColor(ofColor sel_bc, ofColor nsel_bc, ofColor sc);
    
    bool getIsMouseOver(ofPoint testPoint);
    void setFocus(MODE_FORCUS fState);
    MODE_FORCUS getFocus();
    
    int getTextPos();
    void setTextPos(int x);
    int getCursorPos();
    string* getText();
    
    
    // update & draw
    void update();
    void draw();
    
    
    
    
};