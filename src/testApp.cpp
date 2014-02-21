#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(40, 100, 40);

	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
    
    textInput = new MyTextInput(10, 100, 250, 100);
    aPianoRoll = new PianoRoll(0, 0);
    // TextInput
}

//--------------------------------------------------------------
void testApp::update(){
    textInput->update();
    aPianoRoll->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    aPianoRoll->draw();
    textInput->draw();
    
	// display instructions
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
	ofDrawBitmapString("move the mouse to send osc message [/mouse/position <x> <y>]", 10, 50);
	ofDrawBitmapString("click to send osc message [/mouse/button <button> <\"up\"|\"down\">]", 10, 65);
    
    
}

//--------------------------------------------------------------
void testApp::sendOSC(string destAddr, string cmd){
    ofxOscMessage m;
    m.setAddress(destAddr);
    m.addStringArg(cmd);
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
//------------TEXT INPUT------------
    if(textInput->getFocus() == FORCUS){
        string* text = textInput->getText();
        int textPos = textInput->getTextPos();
        
        if (key >=32 && key <=126) {
            text->insert(text->begin() + textPos, key);
            textInput->setTextPos(textPos + 1);
    //        cout << *(textInput.getText()) << endl;
        }
        
        if (key==OF_KEY_BACKSPACE){
            if (textPos>0){
                text->erase(text->begin() + textPos - 1);
                textInput->setTextPos(textPos - 1);
            }
        }
        
        if (key==OF_KEY_DEL){
            if (text->size() > textPos){
                text->erase(text->begin() + textPos);
            }
        }
        
        if (key==OF_KEY_LEFT){
            if (textPos>0){
                textInput->setTextPos(textPos - 1);
            }
        }
        
        if (key==OF_KEY_RIGHT){
            if (textPos < text->size()){
                textInput->setTextPos(textPos + 1);
            }
        }
        
        
        // sendOSC
        if (key==OF_KEY_RETURN) {
            sendOSC("/test", *text);
        }
        
    }
    
    
//------------PIANO ROLL------------
    // PlayBar speed
    if (key == '{' && playSpeed > 0) {
        playSpeed--;
        aPianoRoll->setPlaySpeed(playSpeed);
    }

    if (key == '}'&& playSpeed < 100) {
        playSpeed++;
        aPianoRoll->setPlaySpeed(playSpeed);
    }
    
    
    // keyMode
    // '0' = normal, '1' = write, '2' = erase
    if (key == WRITE) {
        aPianoRoll->setKeyMode(WRITE);
        cout << "Write mode." << endl;
    }else if(key == ERASE){
        aPianoRoll->setKeyMode(ERASE);
        cout << "Erase mode." << endl;
    }else if(key == NORMAL){
        aPianoRoll->setKeyMode(NORMAL);
        cout << "Normal mode." << endl;
    }
    
    // Playbutton
    if (key == 'p' || key == 'P'){
        aPianoRoll->playButtonAction();
    }
    
    
    
    //for multiline:
//    cursorx = cursory = 0;
//    for (int i=0; i<textPos; ++i) {
//        if (*(text.begin()+i) == '\n') {
//            ++cursory;
//            cursorx = 0;
//        } else {
//            cursorx++;
//        }
//    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	ofxOscMessage m;
	m.setAddress("/mouse/position");
	m.addIntArg(x);
	m.addIntArg(y);
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    if(textInput->getIsMouseOver(ofPoint(x, y))){
        textInput->setFocus(FORCUS);
    }else{
        textInput->setFocus(NOT_FORCUS);
    }
    
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("down");
	sender.sendMessage(m);
    
    if(aPianoRoll->getMouseIsOnRollPanel(ofPoint(x, y))){
        switch (aPianoRoll->getKeyMode()) {
        case NORMAL:
            cout << "Select block." << endl;
            cout << "selected Idx: "
            << aPianoRoll->blockAtMousePos(x, y) << endl;
                
            aPianoRoll->selectBlock(aPianoRoll->blockAtMousePos(x, y));
            if(aPianoRoll->blockAtMousePos(x, y) == -1){
                aPianoRoll->unSelectAllBlocks();
                aPianoRoll->setCurPos(x);
                aPianoRoll->findLastBlockNum(x);
            }else if(aPianoRoll->blockAtMousePos(x, y) == -2){
                aPianoRoll->setCurPos(x);
                aPianoRoll->findLastBlockNum(x);
            }
            
            
            break; //normal
        case WRITE:
            cout << "writing block: "
            << aPianoRoll->getBlockNum() << endl;
            aPianoRoll->makeBlock(x, y);
            break; //write

        case ERASE:
            cout << "erasing block: "
            << aPianoRoll->getBlockNum() << endl;
            cout << "delIdx: "
            << aPianoRoll->blockAtMousePos(x, y) << endl;
            aPianoRoll->eraseBlock(aPianoRoll->blockAtMousePos(x, y));
            break; //erase
            
        default:
            break;
        }
    }
    
    //Buttons
    if (aPianoRoll->getPlayButton()->isMouseOn(x, y)) {
        aPianoRoll->playButtonAction();
    }
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("up");
	sender.sendMessage(m);

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

