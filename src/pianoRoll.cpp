//
//  pianoRoll.cpp
//  toSC
//
//  Created by giy on 2/3/14.
//
//

#include "pianoRoll.h"

PianoRoll::PianoRoll(int x, int y){

    posX = x;
    posY = y;
    teum = 11;
    frontWidth = 300;
    
    backWidth = ofGetWindowWidth() - (frontWidth + teum);
    backHeight = frontHeight = ofGetWindowHeight();

    movingPanel = ofRectangle(x + teum + frontWidth, y, backWidth, backHeight);
    frontPanel = ofRectangle(x, y, frontWidth, frontHeight);
    

    fBoxCol = ofColor(255, 0, 0);
    fStrokeCol = ofColor(0);

    bBoxCol = ofColor(255);
    bStrokeCol = ofColor(255, 0, 100);
    
    // Blocks
    numOfBlock = 0;
}

PianoRoll::~PianoRoll(){
    
}

void
PianoRoll::setKeyMode(int mode){
    keyMode = mode;
};

int
PianoRoll::getKeyMode(){
    return keyMode;
};

// Blocks
int
PianoRoll::getBlockNum(){
    return numOfBlock;
}

void
PianoRoll::makeBlock(int x, int y){
    Block aBlock = Block(x, y);
    blocks.push_back(aBlock);
}

void
PianoRoll::eraseBlock(int blockNum){
    if(blocks.size() > 0 && blockNum != -1){
        blocks.erase(blocks.begin()+blockNum);
    }
}

bool
PianoRoll::isInRange(int specNum, int min, int max){
    if (min <= specNum && specNum <= max) {
        return true;
    }else{
        return false;
    }
}

int
PianoRoll::blockAtMousePos(int x, int y){
    if(blocks.size() > 0){
        for (int i = blocks.size()-1; i >= 0; i--) {

            int posX = blocks[i].getPos().x;
            int width = blocks[i].getWidth();
            int posY = blocks[i].getPos().y;
            int height = blocks[i].getHeight();
            
            if (isInRange(x, posX, posX+width)
                && isInRange(y, posY, posY+height)){
                cout << "block on mouse: " << i << endl;
                return i;
            }else{
                if (i == 0) {
                    cout << "No block at mouse pos." << endl;
                    return -1;
                }
            }
        }
    }else{
        cout << "No blocks." << endl;
        return -2;
    }
}

void
PianoRoll::drawBlocks(){
    
    if(blocks.size() > 0){
        for (int i = blocks.size()-1; i >= 0; i--) {
            // Get block point and make some shape
            ofPushStyle();
            ofFill();
            ofSetColor(blocks[i].getBlockColor());
            ofRect(blocks[i].getPos(), blocks[i].getWidth(), blocks[i].getHeight());
            ofNoFill();
            ofSetColor(blocks[i].getLineColor());
            ofRect(blocks[i].getPos(), blocks[i].getWidth(), blocks[i].getHeight());
            ofPopStyle();
        }
    }
}

void
PianoRoll::update(){

}

void
PianoRoll::draw(){
    
    // Back panel - moving
    ofPushStyle();
    ofFill();
    ofSetColor(bBoxCol);
    ofRect(movingPanel);
    ofNoFill();
    ofSetColor(bStrokeCol);
    ofRect(movingPanel);
    ofPopStyle();
    
    // Front panel - static
    ofPushStyle();
    ofFill();
    ofSetColor(fBoxCol);
    ofRect(frontPanel);
    ofNoFill();
    ofSetColor(fStrokeCol);
    ofRect(frontPanel);
    ofPopStyle();
    
    drawBlocks();

}