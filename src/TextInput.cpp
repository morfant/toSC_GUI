//
//  TextInput.cpp
//  oscSenderExample
//
//  Created by giy on 1/1/14.
//
//

#include "TextInput.h"

TextInput::TextInput(int x, int y){
    text = "";
    
    posX = x;
    posY = y;
    
    textPanel = ofRectangle(x, y, width, height);
    
    txtCol = ofColor(0);
    sel_boxCol = ofColor(255);
    nsel_boxCol = ofColor(0, 100, 200, 50);
    strokeCol = ofColor(0);
    
}


TextInput::TextInput(int x, int y, int w, int h){
    text = "";
    
    posX = x;
    posY = y;
    width = w;
    height = h;
    
    textPanel = ofRectangle(x, y, width, height);
    
    sel_boxCol = ofColor(255);
    nsel_boxCol = ofColor(0, 100, 200);
    strokeCol = ofColor(0);
    
}

TextInput::~TextInput(){

}


void
TextInput::init() {
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
    
    // Don't forget to use "ofEvents()".
	ofAddListener(ofEvents().keyPressed, this, &TextInput::keyPressedEvent);
	ofAddListener(ofEvents().mousePressed, this, &TextInput::mousePressedEvent);
    
    // set vector with '-1'
    for (int i = 0; i < lineLimit; ++i) {
        cNumOfLines.push_back(-1);
    }

}


// getter & setter
int
TextInput::getX(){
    return posX;
}

int
TextInput::getY(){
    return posY;
}

void
TextInput::setX(int x){
    posX = x;
}

void
TextInput::setY(int y){
    posY = y;
}

void
TextInput::setColor(ofColor sel_bc, ofColor nsel_bc, ofColor sc){
    sel_boxCol = sel_bc;
    nsel_boxCol = nsel_bc;
    strokeCol = sc;
}

void
TextInput::setFocus(MODE_FORCUS fState){
    isForcus = fState;
    cout << isForcus << endl;
}

MODE_FORCUS
TextInput::getFocus(){
    return isForcus;
}

bool
TextInput::getIsMouseOver(ofPoint testPoint){
    return isInsideRect(testPoint, textPanel);
}

int
TextInput::getTextPos(){
    return textPos;
}

void
TextInput::setTextPos(int x){
    textPos = x;
}

string*
TextInput::getText(){
    return &text;
}



//----------------LOOP----------------
void
TextInput::update(){
    
}

void
TextInput::draw(){
    
    ofPushStyle();
    ofFill();
//    ofNoFill();
    
    if(isForcus == FORCUS){
        ofSetColor(sel_boxCol);
    }else{
        ofSetColor(nsel_boxCol);
    }
    
    ofRect(posX, posY, width, height);
    ofPopStyle();
    
    ofPushMatrix();
        ofTranslate(posX, posY - bottomOver);
    
        // Cursor
        ofPushStyle();
        ofSetColor(0, 0, 0, 255);

        cursorX = padL + (fontWidth * posInLine);
        linePos = padT + (lineNum * fontHeight);
    
        if(linePos > height){
            bottomOver = (linePos - height);
        }

        ofRect(cursorX, linePos, cursorThickness, fontHeight);
    //    ofLine(cursorX, linePos, cursorX, linePos + fontHeight);
        ofPopStyle();
    
        // Text
        //x=left, y=bottom of a letter.
        ofSetColor(txtCol);
        ofDrawBitmapString(text, padL, fontHeight);
    ofPopMatrix();
}


//----------------Key event----------------
void
TextInput::keyPressedEvent(ofKeyEventArgs &a) {
	keyPressed(a.key);
}

void
TextInput::keyPressed(int key) {
    if(isForcus == FORCUS){
        if (key >=32 && key <=126) {
            text.insert(text.begin()+textPos, key);
            ++textPos;
            ++posInLine;
            cNumOfLines[lineNum] = getCharNumOfLine(lineNum, text); //include '\n'
        }
        
        if (key==OF_KEY_RETURN) {
            keyRETURN();
            sendOSC("/test", text);
        }
        
        if (key==OF_KEY_BACKSPACE) {
            keyBACKSPACE();
        }
        
        if (key==OF_KEY_DEL) {
            keyDEL();
        }
        
        if (key==OF_KEY_LEFT){
            keyLEFT();
        }
        
        if (key==OF_KEY_RIGHT){
            keyRIGHT();
        }
        
        if (key==OF_KEY_UP){
            keyUP();
        }
        if (key==OF_KEY_DOWN){
            keyDOWN();
        }
	}
    
//    cout << "lineNum: " << lineNum << endl;
//    cout << "numOfChar: " << cNumOfLines[lineNum] << endl;
//    cout << "posInLine: " << posInLine << endl;
//    cout << "textPos: " << textPos << endl;
//    cout << "1st. Pos: " << getFirstPos(lineNum, text) << endl;
//    cout << "text.size(): " << text.size() <<'\n' << endl;
}

void TextInput::clear() {
	text.clear();
	textPos = 0;
}

void
TextInput::keyUP(){
    if (textPos>0 && lineNum > 0){
        int prevPos = getFirstPos(lineNum-1, text) + posInLine;
        int prevEnd = getFirstPos(lineNum-1, text) + cNumOfLines[lineNum-1] - 1;
        //                cout << "prevPos: " << prevPos << "/ " << "prevEnd: " << prevEnd << endl;
        textPos = MIN(prevPos, prevEnd);
        posInLine = MIN(posInLine, cNumOfLines[lineNum-1] - 1);
        --lineNum;
    }
}

void
TextInput::keyDOWN(){
    if (textPos<text.size() && cNumOfLines[lineNum+1] != -1){
        int nextPos = getFirstPos(lineNum+1, text) + posInLine;
        int nextEnd = getFirstPos(lineNum+1, text) + cNumOfLines[lineNum+1] - 1;
        //                cout << "nextPos: " << nextPos << "/ " << "nextEnd: " << nextEnd << endl;
        textPos = MIN(nextPos, nextEnd);
        posInLine = MIN(posInLine, cNumOfLines[lineNum+1] - 1);
        ++lineNum;
    }
}

void
TextInput::keyLEFT(){
    if (textPos > 0){
        textPos--;
        posInLine--;
        //                if(*(text.begin()+textPos) == '\n'){
        if(posInLine == -1){
            lineNum--;
            posInLine = cNumOfLines[lineNum] - 1;
        }
    }
}

void
TextInput::keyRIGHT(){
    if (textPos < text.size()){
        textPos++;
        posInLine++;
        //                if(*(text.begin()+textPos) == '\n'){
        if(posInLine == cNumOfLines[lineNum]){
            lineNum++;
            posInLine = 0;
        }
    }
}

void
TextInput::keyRETURN(){
    text.insert(text.begin()+textPos, '\n');
    
    cNumOfLines[lineNum] = getCharNumOfLine(lineNum, text);
    ++textPos;
    ++lineNum;
    vector<int>::iterator it = cNumOfLines.begin()+lineNum;
    cNumOfLines.insert(it, getCharNumOfLine(lineNum, text));
    posInLine = 0;
}

void
TextInput::keyBACKSPACE(){ // erase + keyLEFT()
    if (textPos>0) {
        text.erase(text.begin() + (textPos - 1));
        textPos--;
        posInLine--;
        if(posInLine == -1){
            //            cout << "LINE UP" << endl;
            lineNum--;
            posInLine = cNumOfLines[lineNum] - 1;
        }
    }
}

void
TextInput::keyDEL(){
    if (text.size() > textPos) {
        text.erase(text.begin()+textPos);
    }
}

void
TextInput::viewStringInChar(string text){
    size_t size = text.size();
    for(size_t i = 0; i < size; i++){
        cout << "char idx: " << i << ": " << (char)text[i] << endl;
    }
}

int
TextInput::getCharNumOfLine(int lineNum, string text){
    int nCR = 0;
    int nChar = 0;
    size_t size = text.size();
    
    for (size_t i = 0; i < size; ++i){
        if(text[i] == '\n'){
            nCR++;
        }
        if (lineNum == nCR) {
            if(text[i] != '\n'){
                ++nChar;
            }
        }
    }
    return nChar + 1; // include '\n'
}

int
TextInput::getFirstPos(int lineNum, string text){
    int rslt = 0;
    for (size_t i = 0; i < lineNum; i++) {
        rslt += getCharNumOfLine(i, text);
    }
    return rslt;
}

//----------------Mouse event----------------
void
TextInput::mousePressedEvent(ofMouseEventArgs &m){
    mousePressed(m.x, m.y, m.button);
}

void
TextInput::mousePressed(int x, int y, int button){
    if(getIsMouseOver(ofPoint(x, y))){
        setFocus(FORCUS);
    }else{
        setFocus(NOT_FORCUS);
    }
}


// OSC
void
TextInput::sendOSC(string destAddr, string cmd){
    ofxOscMessage m;
    m.setAddress(destAddr);
    m.addStringArg(cmd);
    sender.sendMessage(m);
}



