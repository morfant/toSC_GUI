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

typedef enum { ACTIVE, DEACTIVE } BUTTON_STATE;

class Button{
protected:
    int posX = 0;
    int posY = 0;
    int width = 20;
    int height = 20;
    ofColor bColor = ofColor(255);
    ofColor fColorOn = ofColor(0);
    ofColor fColorOff = ofColor(0, 100, 50);
    
    BUTTON_STATE butState = DEACTIVE;
    
    bool bisMouseOn;
    
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
    
    void setState(BUTTON_STATE state);
    BUTTON_STATE getState();
    
    bool isMouseOn(int mouseX,int mouseY);
    virtual void draw(int posX, int posY);
};


// Real Buttons
class Button_PLAY : public Button{
protected:
    
public:
    Button_PLAY();
    ~Button_PLAY();
    
    void draw(int posX, int posY);
};


