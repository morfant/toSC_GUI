//
//  Bar.h
//  toSC
//
//  Created by giy on 2/18/14.
//
//

#pragma once
#include <iostream>
#include "ofMain.h"

class Bar{

protected:
    int posX;
    ofColor color;
    
    
public:
    Bar();
    Bar(int x);
    ~Bar();
    
    void setPos(int x);
    int getPos();

    void setColor(ofColor barColor);
    ofColor getColor();

    void draw();
};
