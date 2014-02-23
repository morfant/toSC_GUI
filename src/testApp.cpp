#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(40, 100, 40);
    
    pTrack = new Track();
    
//    textInput = new TextInput(10, 100, 250, 100);
//    aPianoRoll = new PianoRoll(0, 0);
    // TextInput
}

//--------------------------------------------------------------
void testApp::update(){
    pTrack->update();
//    textInput->update();
//    aPianoRoll->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    pTrack->draw();
//    aPianoRoll->draw();
//    textInput->draw();
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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

