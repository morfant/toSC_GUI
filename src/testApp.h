#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "MyTextInput.h"
#include "pianoRoll.h"

#define HOST "localhost"
#define PORT 57120

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
    
    void sendOSC(string destAddr, string cmd);

		ofTrueTypeFont font;
		ofxOscSender sender;
    
    MyTextInput textInput = MyTextInput(10, 100);
    PianoRoll pianoRoll = PianoRoll(0,0);
    
    int playSpeed = 0;

};

