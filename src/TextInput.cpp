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
    bgBlockCol = ofColor(0, 60, 100, 100);
    bgBlockCol_warn = ofColor(150, 20, 40, 80);
    
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
    
        // bgBlock(if needed)
    makeBgBlockRange(blockBegin, blockEnd);

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
            chkBracketsOpen(key);
            chkBracketsClose(key);
//            makeBgBlock(textPos);
            ++textPos;
            ++posInLine;
            cNumOfLines[lineNum] = getCharNumOfLine(lineNum, text); //include '\n'
            

            
        }
        
        if (key==OF_KEY_RETURN) {
            keyRETURN();
//            cout<< "sumOfArray: " <<
//            sumOfArray(lineNum, &cNumOfLines)
//            << endl;
            insertIndention(nTab);
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
    
//    cout << "textPos to PosX: " <<
//    textPosToPixel(textPos)
//    << endl;
    
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
    nTabBool = false;
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


//----------------Calculate text pos----------------
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


//----------------Make blocks----------------
void
TextInput::makeBgBlockRange(int bPos, int ePos){
    if(bPos < ePos){
        for (size_t i = bPos; i < ePos; i++) {
            makeBgBlock(i);
        }
    }else{
        for (size_t i = bPos; i > ePos; i--) {
            makeBgBlock(i);
        }
    }
}

void
TextInput::makeBgBlock(int textPos){
    ofPushStyle();
    ofSetColor(bgBlockCol);
    ofRect(textPosToPixel(textPos), fontWidth, fontHeight);
    ofPopStyle();
}

ofPoint
TextInput::textPosToPixel(int textPos){
    int i = 0; // lineNum
    ofPoint rsltPoint = ofPoint(0, 0);
    
    while (i < cNumOfLines.size()) {
        if(sum(i, &cNumOfLines) > textPos){
            rsltPoint.x = padL +
            (fontWidth * (cNumOfLines[i] - (sum(i, &cNumOfLines) - textPos)));
            
            rsltPoint.y = padT + (i * fontHeight);
            return rsltPoint;
            break;
        }else{
            i++;
        }
    }
}

//----------------Auto Indentation----------------
bool
TextInput::chkBracketsOpen(int key){
if(key == '(' || key == '[' || key == '{'){
    BRACKET tBr;
    tBr.pos = textPos;
    if(key == '(' ){
        tBr.bracketType = ROUND_BRACKET;
    }else if(key == '['){
        tBr.bracketType = SQUARE_BRACKET;
    }else{
        tBr.bracketType = BRACE;
    }
    openBrackets.push_back(tBr);

    if (nTabBool == false) {
        nTab++;
        nTabBool = true;
        cout << nTab << endl;
    }
}
//    if(posOfBrackets.size() > 0){
//        cout << "p1: " << posOfBrackets[0] << endl;
//        cout << "p2: " << posOfBrackets[1] << endl;
//    }
}

bool
TextInput::chkBracketsClose(int key){
    if(key == ')' || key == ']' || key == '}'){
        BRACKET tBr;
        tBr.pos = textPos;
        if(key == ')' ){
            tBr.bracketType = ROUND_BRACKET;
            cout << "round c" << endl;
        }else if(key == ']'){
            tBr.bracketType = SQUARE_BRACKET;
            cout << "square c" << endl;
        }else{
            tBr.bracketType = BRACE;
            cout << "brace c" << endl;
        }

        closeBrackets.push_back(tBr); // insert to end.
        
        int tFlag = isSameShapeBracket();
        if(tFlag == -1){
            if (nTabBool == false && nTab > 0) {
                nTab--;
                nTabBool = true;
                cout << nTab << endl;
            }
        }else{
            blockEnd = textPos;
            blockBegin = tFlag;
            closeBrackets.pop_back();
            
            // make warning block from textPos to wrong open bracket.
        }
    }
    //    if(posOfBrackets.size() > 0){
    //        cout << "p1: " << posOfBrackets[0] << endl;
    //        cout << "p2: " << posOfBrackets[1] << endl;
    //    }
}

int
TextInput::isSameShapeBracket(){
    size_t size = closeBrackets.size();
    if (size > 0) {
        int idx = size;
        if(closeBrackets.back().bracketType == (*(openBrackets.end() - idx)).bracketType){
            cout << "same close bracket." << endl;
            return -1;
        }else{
            cout << "not same close bracket." << (*(openBrackets.end() - idx)).pos << endl;
            return (*(openBrackets.end() - idx)).pos;
        }
    }
}

void
TextInput::insertIndention(int nTab){
    // 4 spaces
    while (nTab > 0) {
        int i = 4;
        while (i > 0) {
            text.insert(text.begin()+textPos, ' ');
            --i;
            ++textPos;
            ++posInLine;
        }
        --nTab;
    }

    // 1 tab = 8 spaces
    //    while (nTab > 0) {
    //        text.insert(text.begin()+textPos, '\t');
    //        ++textPos;
    //        --nTab;
    //        cout << "indent" << endl;
    //    }
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



