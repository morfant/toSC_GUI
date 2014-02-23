#pragma once

#include "ofMain.h"
//#include "ofxOsc.h"
#include "Track.h"
//#include "TextInput.h"
//#include "pianoRoll.h"

//--------------------------------------------------------
class testApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
		ofTrueTypeFont font;
    
//    TextInput* textInput;
//    PianoRoll* aPianoRoll;
    
    Track* pTrack; // Manage PianoRoll, TextInput and OSC
    
    int playSpeed = 0;

};

