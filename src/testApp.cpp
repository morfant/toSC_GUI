#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(40, 100, 40);

	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
    
    
    // TextInput
}

//--------------------------------------------------------------
void testApp::update(){
    textInput.getIsMouseOver();
    pianoRoll.update();

}

//--------------------------------------------------------------
void testApp::draw(){
	// display instructions
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
	ofDrawBitmapString("move the mouse to send osc message [/mouse/position <x> <y>]", 10, 50);
	ofDrawBitmapString("click to send osc message [/mouse/button <button> <\"up\"|\"down\">]", 10, 65);
    
    // TextInput
    textInput.draw();
    
    // PianoRoll
    pianoRoll.draw();
    
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
    
//    cout << key << endl;
        
    string* text = textInput.getText();
    int textPos = textInput.getTextPos();
    
    if (key >=32 && key <=126) {
        text->insert(text->begin() + textPos, key);
        textInput.setTextPos(textPos + 1);
//        cout << *(textInput.getText()) << endl;
    }
    
    // PlayBar speed
    if (key == '{' && playSpeed >= 0) {
        playSpeed--;
        pianoRoll.setPlaySpeed(playSpeed);
    }

    if (key == '}'&& playSpeed <= 100) {
        playSpeed++;
        pianoRoll.setPlaySpeed(playSpeed);
    }
    
    
    if (key==OF_KEY_BACKSPACE){
        if (textPos>0){
            text->erase(text->begin() + textPos - 1);
            textInput.setTextPos(textPos - 1);
        }
    }
    
    if (key==OF_KEY_DEL){
        if (text->size() > textPos){
            text->erase(text->begin() + textPos);
        }
    }
    
    if (key==OF_KEY_LEFT){
        if (textPos>0){
            textInput.setTextPos(textPos - 1);
        }
    }
    
    if (key==OF_KEY_RIGHT){
        if (textPos < text->size()){
            textInput.setTextPos(textPos + 1);
        }
    }
    
    
    // keyMode
    // 0 = normal, 1 = write, 2 = erase
    if ('0' <= key && key <= '2') {
        pianoRoll.setKeyMode(key);
        if (key == '1') {
            cout << "Write mode." << endl;
        }else if(key == '2'){
            cout << "Erase mode." << endl;
        }else if(key == '0'){
            cout << "Normal mode." << endl;
        }
    }
    
    // sendOSC
    if (key==OF_KEY_RETURN) {
        sendOSC("/test", *text);
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
    
    textInput.isFocus(x, y);
    
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("down");
	sender.sendMessage(m);
    
    
    //func int blockAtMousePos();
    switch (pianoRoll.getKeyMode()) {
            cout<<pianoRoll.getKeyMode()<<endl;
        case '0':
            cout << "Set Write or Erase mode first." << endl;
            break; //normal
        case '1':
            cout << "writing block" << endl;
            pianoRoll.makeBlock(x, y);
            break; //write
        case '2':
            cout << "erasing block" << endl;
            int delIdx = pianoRoll.blockAtMousePos(x, y);
            cout << "delIdx: " << delIdx << endl;
            pianoRoll.eraseBlock(delIdx);
            break; //erase
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

