#pragma once

#include "ofMain.h"
#include "ofxMotion.h"

class ofApp : public ofBaseApp, ofThread {

public:
	~ofApp();
	void setup();
	void update();
	void draw();
	void keyReleased(int key);
	void threadedFunction();


	static const int motionMaxSize = 200;
	ofxMotion motionFloating[motionMaxSize];
	ofxMotion motionBackground[motionMaxSize];
	ofxMotion motionMoveLiner[motionMaxSize];
	ofColor colorMds[motionMaxSize];


	ofFbo fbo;

	float fboWidth;
	float fboHeight;
	float screenWidth;
	float screenHeight;
};
