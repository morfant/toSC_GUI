//
//  pianoRoll.cpp
//  toSC
//
//  Created by giy on 2/3/14.
//
//

#include "pianoRoll.h"

PianoRoll::PianoRoll(int x, int y){

//    //Test
//    for(int i = 0; i < 10; i++){
//        static int t = ofRandom(10);
//        iVec.push_back(&t);
//        cout<< "i : " << t << endl;
//    }
    
    posX = x;
    posY = y;
    teum = 11;
    keyPanelWidth = 300;
    
    rollPanelWidth = ofGetWindowWidth() - (keyPanelWidth + teum);
    rollPanelHeight = keyPanelHeight = ofGetWindowHeight();

    rollPanelPosX = ofGetWindowWidth() - rollPanelWidth;
    rollPanelPosY = 0;
    
    rollPanel = ofRectangle(x + teum + keyPanelWidth, y, rollPanelWidth, rollPanelHeight);
    keyPanel = ofRectangle(x, y, keyPanelWidth, keyPanelHeight);
    

    fBoxCol = ofColor(255, 0, 0);
    fStrokeCol = ofColor(0);

    bBoxCol = ofColor(255);
    bStrokeCol = ofColor(255, 0, 100);
    
    // Blocks
    numOfBlock = 0;
    
    // Bar
    playSpeed = 2;
    curPos = rollPanelPosX;
    playBar = Bar(curPos);
    
    // Buttons
    pState = DEACTIVE;
}

PianoRoll::~PianoRoll(){
    
}

void
PianoRoll::setKeyMode(MODE_STATE mode){
    keyMode = mode;
};

MODE_STATE
PianoRoll::getKeyMode(){
    return keyMode;
};

// PlayBar
void
PianoRoll::setPlaySpeed(int speedX){
    playSpeed = speedX;
}

int
PianoRoll::getPlaySpeed(){
    return playSpeed;
}


// Blocks
int
PianoRoll::getBlockNum(){
    return numOfBlock = blocks.size();
}

void
PianoRoll::selectBlock(int blockIdx){

    // for vector
    if(blocks.size() > 0 && blockIdx != -1){
        if(blocks[blockIdx]->getState() != SELECTED){
            blocks[blockIdx]->setState(SELECTED);
        }
    }

    /*
    // for list
    if(blocks.size() > 0 && blockIdx != -1){
        iter = blocks.begin();
        if(*(iter+blockIdx).getState() != SELECTED){
            iter->setState(SELECTED);
        }
    }
    */
}

void
PianoRoll::unSelectAllBlocks(){
    if(blocks.size() > 0){
//        for (vector<Block*>::iterator it = blocks.end() ; it != blocks.begin()-1; it--){
//            (*it)->setState(NOT_SELECTED);
//        }
        for (size_t i = blocks.size()-1; i != -1; i--){
            blocks[i]->setState(NOT_SELECTED);
        }
    }
}

void
PianoRoll::makeBlock(int x, int y){
    Block* aBlock = new Block(x, y);
//    Block aBlock = Block(x, y);
//    cout << "addr of block at make: " << aBlock << endl;
    blocks.push_back(aBlock);
}

void
PianoRoll::eraseBlock(int blockIdx){
    if(blocks.size() > 0 && blockIdx != -1){
        blocks.erase(blocks.begin()+blockIdx);
    }
}

int
PianoRoll::blockAtMousePos(int x, int y){
    if(blocks.size() > 0){
        for (int i = blocks.size()-1; i >= 0; i--) {

            int posX = blocks[i]->getPos().x;
            int width = blocks[i]->getWidth();
            int posY = blocks[i]->getPos().y;
            int height = blocks[i]->getHeight();
            
            ofRectangle tRect = ofRectangle(posX, posY, width, height);
            ofPoint tPoint = ofPoint(x, y);

            if(isInsideRect(tPoint, tRect)){
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

// Buttons
Button_PLAY*
PianoRoll::getPlayButton(){
    return &playButton;
}

void
PianoRoll::setPlayButtonState(BUTTON_STATE state){
    playButton.setState(state);
}

//BUTTON_STATE
//PianoRoll::getPlayButtonState(){
//    return playButton.getState();
//}


// Control
bool
PianoRoll::getMouseIsOnRollPanel(ofPoint testPoint){
    return isInsideRect(testPoint, rollPanel);
}

bool
PianoRoll::getMouseIsOnKeyPanel(ofPoint testPoint){
    return isInsideRect(testPoint, keyPanel);
}

// - sort blocks
void
PianoRoll::sortBlockPos(vector<Block*>* vec){
    
    vector<Block*>::iterator iter = vec->begin();

    // access with vec[1] test
//    cout <<
//    (*(iter + 1))->getBeginX()
//    << endl;
    
    size_t size = vec->size();
    
    for(int i = 1; i < size; i++){
        // printf("%c\n", temp);
        for(int j = i - 1; j >= 0; j--){
            if((*(iter+j+1))->getBeginX() < (*(iter+j))->getBeginX()){
//                cout << j+1 << " / " << j << endl;
                swap((*(iter+j+1)), (*(iter+j)));
            }
        }
    }
}

void
PianoRoll::playButtonAction(){
    if (pState == DEACTIVE){
        
        // SORT FIRST BLOCKS WITH BEGINX
        sortBlockPos(&blocks);
        
//        for(size_t i = 0; i < blocks.size(); i++){
//            cout << i << " : " <<
//            blocks[i]->getBeginX()
//            << endl;
//        }
        
        pState = ACTIVE;
        playButton.setState(ACTIVE);
    }
    else{
        pState = DEACTIVE;
        playButton.setState(DEACTIVE);
    }
}

void
PianoRoll::drawBlocks(){
    if(blocks.size() > 0){
//    cout << "addr of block at draw: " << &blocks[0] << endl;
        for (int i = blocks.size()-1; i >= 0; i--) {
            // Get block point and make some shape
            ofPushStyle();
            ofFill();
            ofSetColor(blocks[i]->getBlockColor());
            ofRect(blocks[i]->getPos(), blocks[i]->getWidth(), blocks[i]->getHeight());
            ofNoFill();
            ofSetColor(blocks[i]->getLineColor());
            ofRect(blocks[i]->getPos(), blocks[i]->getWidth(), blocks[i]->getHeight());
            ofPopStyle();
        }
    }
}

void
PianoRoll::update(){
    if(pState == ACTIVE){
        curPos = curPos + playSpeed;
        if(curPos >= ofGetWindowWidth()){
            curPos = rollPanelPosX;
        }
        playBar.setPos(curPos);
    }
}

void
PianoRoll::draw(){
    
    // Back panel - moving
    ofPushStyle();
    ofFill();
    ofSetColor(bBoxCol);
    ofRect(rollPanel);
    ofNoFill();
    ofSetColor(bStrokeCol);
    ofRect(rollPanel);
    ofPopStyle();
    
    // Front panel - static
    ofPushStyle();
    ofFill();
    ofSetColor(fBoxCol);
    ofRect(keyPanel);
    ofNoFill();
    ofSetColor(fStrokeCol);
    ofRect(keyPanel);
    ofPopStyle();
    
    drawBlocks();
    playBar.draw();
    
    playButton.draw(200, 200);
    
}



















