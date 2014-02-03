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


class MyTextInput{
protected:
    
    int posX, posY;
    int width, height;
    ofColor boxCol, strokeCol;

    bool isMouseOver;

    string text;
    
    int cursorX, cursorY;
    int fontHeight, fontWidth;
    int cursorThickness;
    int textPos;
    
    
public:
    
    // constructor & destructor
    MyTextInput(int x, int y);
    ~MyTextInput();
    
    
    // getter & setter
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setColor(ofColor boxCol, ofColor strokeCol);
    bool getIsMouseOver();
    int getTextPos();
    void setTextPos(int x);
    int getCursorPos();
    string* getText();
    
    
    // update & draw
    void update();
    void draw();
    
    
    void isFocus(int x, int y);
    
};