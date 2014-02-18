//
//  Button.h
//  toSC
//
//  Created by giy on 2/18/14.
//
//

#pragma once
#include <iostream>
#include "ofMain.h"

typedef enum { ON, OFF } BUT_STATE;

class Button{
protected:
    int posX = 0;
    int posY = 0;
    int width = 20;
    int height = 20;
    ofColor bColor = ofColor(255);
    ofColor fColorOn = ofColor(0);
    ofColor fColorOff = ofColor(0, 100, 50);
    
    BUT_STATE butState = OFF;
    
public:
    
    Button();
    Button(int posX, int posY);
    ~Button();
    
    void setPos(int x, int y);
    int getPosX();
    int getPosY();
    
    void setWidth(int width);
    void setHeight(int height);
    int getWidth();
    int getHeight();
    
    void setColor(ofColor bCol, ofColor fColOn, ofColor fColOff);
    ofColor getBgColor();
    ofColor getFColorOn();
    ofColor getFColorOff();
    
    void setState(BUT_STATE state);
    BUT_STATE getState();
    
    virtual void draw(int posX, int posY);
};


// Real Buttons
class Button_PLAY : protected Button{
protected:
    
public:
    Button_PLAY();
    ~Button_PLAY();
    
    void draw(int posX, int posY);
};


