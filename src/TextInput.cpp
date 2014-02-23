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
    
    sel_boxCol = ofColor(255);
    nsel_boxCol = ofColor(0, 100, 200);
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
    //    ofFill();
    ofNoFill();
    
    if(isForcus == FORCUS){
        ofSetColor(sel_boxCol);
    }else{
        ofSetColor(nsel_boxCol);
    }
    
    ofRect(posX, posY, width, height);
    ofPopStyle();
    
    ofPushMatrix();
    ofTranslate(posX, posY);
    
    // Cursor
    ofPushStyle();
    ofSetColor(0, 0, 0, 255);

    int cursorX = padL + (fontWidth * posInLine);
    int linePos = padT + (lineNum * fontHeight);
    ofRect(cursorX, linePos, cursorThickness, fontHeight);
//    ofLine(cursorX, linePos, cursorX, linePos + fontHeight);
    ofPopStyle();
    
    // Text
    //x=left, y=bottom of a letter.
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
        //add charachter (non unicode sorry!)
        if (key >=32 && key <=126) {
            text.insert(text.begin()+textPos, key);
            ++textPos;
            ++posInLine;
        }
        
        if (key==OF_KEY_RETURN) {
            text.insert(text.begin()+textPos, '\n');
            ++textPos;
            ++lineNum;
            cNumOfLines.push_back(posInLine);
            posInLine = 0;
            //        cout<<"text: " << text<<endl;
            
            sendOSC("/test", text);
        }
        
        if (key==OF_KEY_BACKSPACE) {
            if (textPos>0) {
                if(*(text.begin()+textPos-1) == '\n'){
                    text.erase(text.begin() + (textPos - 1));
                    --textPos;
                    --lineNum;
                    posInLine = cNumOfLines.back(); //access last element
                    cNumOfLines.pop_back();
                }else{
                    text.erase(text.begin() + (textPos - 1));
                    --textPos;
                    --posInLine;
                }
            }
        }
        
        if (key==OF_KEY_DEL) {
            if (text.size() > textPos) {
                text.erase(text.begin()+textPos);
            }
        }
        
        if (key==OF_KEY_LEFT)
            if (textPos>0)
                --textPos;
        --posInLine;
        
        if (key==OF_KEY_RIGHT)
            if (textPos<text.size()+1)
                ++textPos;
        ++posInLine;
	}
}

void TextInput::clear() {
	text.clear();
	textPos = 0;
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



