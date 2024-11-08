#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetCircleResolution(48);

	for (int i = 0; i < 6; i++) {
		motion[i].setMotionTransformPtr(new MoveLiner());
		motion[i].setMotionColorPtr(new NoColor());
	}

	motion[0].setup(ofxMotion::DrawMode::RECT, vec2(200, 200), vec2(1.0, 1.0), 200, 200, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);
	motion[1].setup(ofxMotion::DrawMode::CIRCLE, vec2(200 + 200, 200), vec2(1.0, 1.0), 200, 200, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);
	motion[2].setup(ofxMotion::DrawMode::TRIANGLE, vec2(200 + 400, 200), vec2(1.0, 1.0), 200, 200, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	image.load("image_fx_1.jpg");
	motion[3].setup(ofxMotion::DrawMode::IMAGE, &image, vec2(200, 400), vec2(1.0, 1.0), image.getWidth(), image.getHeight(), 0.0f, ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	pixels.allocate(200, 200, OF_PIXELS_RGB);
	for (int y = 0; y < 200; y++) {
		for (int x = 0; x < 200; x++) {
			pixels.setColor(x, y, ofColor(x, y, 0));
		}
	}
	texture.allocate(pixels);
	motion[4].setup(ofxMotion::DrawMode::TEXTURE, &texture, vec2(200 + 200, 400), vec2(1.0, 1.0), texture.getWidth(), texture.getHeight(), 0.0f, ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	font.load("NotoSansCJKjp-Regular.otf", 20);
	motion[5].setup(ofxMotion::DrawMode::TEXT, &font, "ABCDEFG", vec2(200 + 200, 400), vec2(1.0, 1.0), 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	ofBackground(255);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	float now = ofGetElapsedTimef();
	for (int i = 0; i < 6; i++) {
		motion[i].update(now);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < 6; i++) {
		motion[i].draw();
	}

	for (int i = 0; i < 6; i++) {
		ofSetColor(0, 100);
		ofDrawRectangle(motion[i].getRectangle());
	}

	ofSetColor(255, 0, 0);
	ofDrawLine(0, 200, ofGetWidth(), 200);
	ofDrawLine(0, 400, ofGetWidth(), 400);
	ofDrawLine(0, 600, ofGetWidth(), 600);
	ofDrawLine(200, 0, 200, ofGetHeight());
	ofDrawLine(400, 0, 400, ofGetHeight());
	ofDrawLine(600, 0, 600, ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == '1') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion::AnchorMode::ANCHOR_CENTER);
		}
	}
	else if (key == '2') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion::AnchorMode::ANCHOR_BOTTOM_CENTER);
		}
	}
	else if (key == '3') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion::AnchorMode::ANCHOR_TOP_LEFT);
		}
	}
	else if (key == '4') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion::AnchorMode::ANCHOR_TOP_RIGHT);
		}
	}
	else if (key == '5') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion::AnchorMode::ANCHOR_BOTTOM_LEFT);
		}
	}
	else if (key == '6') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion::AnchorMode::ANCHOR_BOTTOM_RIGHT);
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
