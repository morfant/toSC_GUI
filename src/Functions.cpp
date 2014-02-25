//
//  Functions.cpp
//  toSC
//
//  Created by giy on 2/18/14.
//
//

#include "Functions.h"


bool
isInsideRect(ofPoint testPoint, ofPoint leftTop, int width, int height){
    if(testPoint.x >= leftTop.x && testPoint.x <= leftTop.x+width){
        if(testPoint.y >= leftTop.y && testPoint.y <= leftTop.y+height){
            return TRUE;
        }
    }
}


bool
isInsideRect(int x, int y, int left, int top, int width, int height){
    if(x >= left && x <= left+width){
        if(y >= top && y <= top+height){
            return TRUE;
        }
    }
}

bool
isInsideRect(int x, int y, ofRectangle rect){
    if(x >= rect.x && x <= rect.x+rect.width){
        if(y >= rect.y && y <= rect.y+rect.height){
            return TRUE;
        }
    }
}

bool
isInsideRect(ofPoint point, ofRectangle rect){
    if(point.x >= rect.x && point.x <= rect.x+rect.width){
        if(point.y >= rect.y && point.y <= rect.y+rect.height){
            return TRUE;
        }
    }
}


int
sum(int targetIdx, vector<int>* arr){
    int sumRslt = 0;
    vector<int>::iterator it = arr->begin();
    
    for (size_t i = 0; i <= targetIdx; ++i) {
        sumRslt += *(it + i);
    }
    return sumRslt;
}