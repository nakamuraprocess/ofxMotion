#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	waitForThread();
	stopThread();
}

//--------------------------------------------------------------
void ofApp::setup() {
	screenWidth = ofGetWidth();
	screenHeight = ofGetHeight();
	fboWidth = 1080;
	fboHeight = 1920;

	fbo.allocate(fboWidth, fboHeight, GL_RGB);

	for (int i = 0; i < motionMaxSize; i++) {
		motionBackground[i].setMotionTransformPtr(new NoTransform("NoTransform"));
		motionBackground[i].setMotionColorPtr(new ColorGradation("ColorGradation"));
		float x = 0;
		float y = i * float(fboHeight / motionMaxSize);
		float width = fboWidth;
		float height = float(fboHeight / motionMaxSize);
		motionBackground[i].setup(ofxMotion::DrawMode::RECT, vec2(x, y), vec2(1.0, 1.0), width, height, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::TOP_CORNER_LEFT, true);
	}

	for (int i = 0; i < motionMaxSize; i++) {
		motionMoveLiner[i].setMotionTransformPtr(new MoveLiner("MoveLiner"));
		motionMoveLiner[i].setMotionColorPtr(new ColorGradation("ColorGradation"));
		float x = -fboWidth;
		float y =  i * float(fboHeight / motionMaxSize);
		float width = fboWidth;
		float height = float(fboHeight / motionMaxSize);
		motionMoveLiner[i].setup(ofxMotion::DrawMode::RECT, vec2(x, y), vec2(1.0, 1.0), width, height, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::TOP_CORNER_LEFT, true);
	}

	for (int i = 0; i < motionMaxSize; i++) {
		motionFloating[i].setMotionTransformPtr(new RadialNoise("RadialNoise"));
		motionFloating[i].setMotionColorPtr(new ColorGradation("ColorGradation"));
		float x = ofRandom(0, motionMaxSize);
		float y = ofRandom(0, motionMaxSize);
		float width = ofRandom(40, 300);
		float height = float(fboHeight / motionMaxSize);
		int r = ofRandom(0, 255);
		int g = ofRandom(0, 255);
		int b = ofRandom(0, 255);
		ofColor color = ofColor(r, g, b);
		motionFloating[i].setup(ofxMotion::DrawMode::RECT, vec2(x, y), vec2(1.0, 1.0), width, height, 0.0f, color, ofxMotion::AnchorMode::CENTER);
	}

	for (int i = 0; i < motionMaxSize; i++) {
		motionFloating[i].startMotion("RadialNoise", 600, 0.2, vec2(500, 960), 60.0);
	}


	ofSetFrameRate(60);
	ofSetVerticalSync(true);

	startThread();
}

//--------------------------------------------------------------
void ofApp::update() {
	auto now = ofGetElapsedTimef();
	
	for (int i = 0; i < motionMaxSize; i++) {
		motionBackground[i].update(now);
		motionMoveLiner[i].update(now);
		motionFloating[i].update(now);
	}

	fbo.begin();
	ofClear(255);
	for (int i = 0; i < motionMaxSize; i++) {
		motionBackground[i].draw();
		motionMoveLiner[i].draw();
		motionFloating[i].draw();
	}
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	fbo.draw(0, 0, screenWidth, screenHeight);
}

//--------------------------------------------------------------
void ofApp::threadedFunction() {
	while (isThreadRunning()) {
		
		for (int i = 0; i < motionMaxSize; i++) {
			int r = ofRandom(0, 255);
			int g = ofRandom(0, 255);
			int b = ofRandom(0, 255);
			colorMds[i] = ofColor(r, g, b);

			float startX = -fboWidth;
			float startY = i * float(fboHeight / motionMaxSize);
			float targetX = 0;
			float targetY = startY;
			motionMoveLiner[i].startColor("ColorGradation", 0.1, colorMds[i], ofxeasing::linear::easeNone);
			motionMoveLiner[i].startMotion("MoveLiner", vec2(startX, startY), vec2(targetX, targetY), 0.5, 0, ofxeasing::quart::easeIn);
		}

		sleep(900);
		for (int i = 0; i < motionMaxSize; i++) {
			motionBackground[i].startColor("ColorGradation", 0.1, colorMds[i], ofxeasing::linear::easeNone);
		}
		sleep(100);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	
}