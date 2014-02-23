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


void
TextInput::viewStringInChar(string text){
    int size = text.size();
    for(int i = 0; i < size; i++){
        cout << "char idx: " << i << ": " << (char)text[i] << endl;
    }
}

int
TextInput::getCharNumOfLine(int lineNum, string text){
    
    int nCR = 0;
    int nChar = 0;
    size_t size = text.size();
//    string tStr;
    
//    for (size_t i = 0; i < size-1; ++i) {
//        tStr[i] = text[i];
//    }
    
    for (size_t i = 0; i < size; ++i) {
        if(text[i] == '\n'){
            nCR++;
            cout<<"idx: " << i << "NN" <<endl;
        }
        if (lineNum == nCR) {
            if(text[i] != '\n'){
                ++nChar;
            }
        }
    }
    
    return nChar + 1; //include '\n'
    
    
}

//----------------Key event----------------
void
TextInput::keyUP(){

}

void
TextInput::keyDOWN(){

}

void
TextInput::keyLEFT(){
}

void
TextInput::keyRIGHT(){
}


void
TextInput::keyPressedEvent(ofKeyEventArgs &a) {
	keyPressed(a.key);
}

void
TextInput::keyPressed(int key) {
    if(isForcus == FORCUS){
        //add charachter (non unicode sorry!)
        if (key >=33 && key <=126) {
            text.insert(text.begin()+textPos, key);
            ++textPos;
            ++posInLine;
//            cNumOfLines[lineNum] = posInLine + 1; //include '\n'
            cNumOfLines[lineNum] = getCharNumOfLine(lineNum, text); //include '\n'
        }
        
        if (key==OF_KEY_RETURN) {
            text.insert(text.begin()+textPos, '\n');
//            if(lineNum != 0){
//                cNumOfLines.push_back(posInLine + 1); //include '\n'
//            }
            cNumOfLines[lineNum] = getCharNumOfLine(lineNum, text);
            ++textPos;
            ++lineNum;
            
            if(cNumOfLines[lineNum] == -1){
                cNumOfLines[lineNum] = 0;
                posInLine = 0;
            }else{
                cNumOfLines[lineNum] = getCharNumOfLine(lineNum, text);
            }
            
//            for(int i = 0; i < cNumOfLines.size(); i++){
//                cout << "ccc: " << cNumOfLines[i] << endl;
//            }
//            cout << "lineNum: " << lineNum << endl;
            
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
        
        if (key==OF_KEY_LEFT){
            if (textPos>0 && posInLine > 0){
                --textPos;
                --posInLine;
            }
        }
        
        if (key==OF_KEY_RIGHT){
            if (textPos<text.size()){
                if(posInLine < cNumOfLines[lineNum]-1){
                    ++textPos;
                    ++posInLine;
                }
            }
        }
        
        if (key==OF_KEY_UP){
            if (textPos>0 && lineNum > 0){
                if(cNumOfLines[lineNum - 1] > posInLine){ // to larger
                    textPos = textPos - (cNumOfLines[lineNum-1]);
                }else{ // to smaller
                    textPos = textPos - (posInLine + 1);
                    posInLine = MAX(0, cNumOfLines[lineNum - 1] - 1);
                }
//                cout << "posInLine: " << posInLine << endl;
//                --posInLine;
//                cout << "cNumOfLines[lineNum-1]: "
//                << lineNum << " / " << cNumOfLines[lineNum-1] << endl;
                --lineNum;
//                cout << "lineNum: " << lineNum << endl;
            }
        }
        if (key==OF_KEY_DOWN){
            if (textPos<text.size()){
                if(cNumOfLines[lineNum+1] > posInLine){ // to larger
//                    cout << "++" << endl;
                    textPos = textPos + (cNumOfLines[lineNum]);
                }else{ // to smaller
//                    cout << "--" << endl;
                    textPos = textPos + cNumOfLines[lineNum+1] + (cNumOfLines[lineNum] - posInLine - 1);
                    posInLine = MAX(0, cNumOfLines[lineNum+1] - 1);
                }
                if(cNumOfLines[lineNum+1] != -1){
                    ++lineNum;
                }
            }
        }
	}
    
    cout << "lineNum: " << lineNum << endl;
    cout << "numOfChar: " << cNumOfLines[lineNum] << endl;
    cout << "posInLine: " << posInLine << endl;
    cout << "textPos: " << textPos << endl;
    cout << "text.size(): " << text.size() <<'\n' << endl;
    //            cout << "text: " << text <<'\n'<< endl;
    //            viewStringInChar(text);
    
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



