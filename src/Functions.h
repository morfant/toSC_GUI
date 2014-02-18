//
//  Functions.h
//  toSC
//
//  Created by giy on 2/18/14.
//
//

#pragma once

#include <iostream>
#include "ofMain.h"

bool isInsideRect(ofPoint testPoint, ofPoint leftTop, int width, int height);
bool isInsideRect(int x, int y, int left, int top, int width, int height);
bool isInsideRect(int x, int y, ofRectangle rect);
bool isInsideRect(ofPoint point, ofRectangle rect);