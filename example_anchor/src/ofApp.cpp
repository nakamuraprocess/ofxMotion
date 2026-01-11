#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	fps = 60;
	ofSetFrameRate(fps);
	ofSetVerticalSync(true);
	delta = 1.0f / fps;
	ofSetBackgroundColor(255, 255, 255);
	ofSetCircleResolution(48);

	for (int i = 0; i < 6; i++) {
		motion[i].setMotionTransformPtr(new MoveLiner());
		motion[i].setMotionColorPtr(new DefaultColor());
	}

	motion[0].setup(ofxMotion2D::DrawMode::RECT, glm::vec2(200, 200), glm::vec2(1.0, 1.0), 200, 200, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion2D::AnchorMode::ANCHOR_CENTER, 0, true);
	motion[1].setup(ofxMotion2D::DrawMode::CIRCLE, glm::vec2(200 + 200, 200), glm::vec2(1.0, 1.0), 200, 200, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion2D::AnchorMode::ANCHOR_CENTER, 0, true);
	motion[2].setup(ofxMotion2D::DrawMode::TRIANGLE, glm::vec2(200 + 400, 200), glm::vec2(1.0, 1.0), 200, 200, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion2D::AnchorMode::ANCHOR_CENTER, 0, true);

	image.load("image_fx_1.jpg");
	motion[3].setup(ofxMotion2D::DrawMode::IMAGE, &image, glm::vec2(200, 400), glm::vec2(1.0, 1.0), image.getWidth(), image.getHeight(), 0.0f, ofxMotion2D::AnchorMode::ANCHOR_CENTER, 0, true);

	pixels.allocate(200, 200, OF_PIXELS_RGB);
	for (int y = 0; y < 200; y++) {
		for (int x = 0; x < 200; x++) {
			pixels.setColor(x, y, ofColor(x, y, 0));
		}
	}
	texture.allocate(pixels);
	motion[4].setup(ofxMotion2D::DrawMode::TEXTURE, &texture, glm::vec2(200 + 200, 400), glm::vec2(1.0, 1.0), texture.getWidth(), texture.getHeight(), 0.0f, ofxMotion2D::AnchorMode::ANCHOR_CENTER, 0, true);

	font.load("NotoSansCJKjp-Regular.otf", 20);
	motion[5].setup(ofxMotion2D::DrawMode::TEXT, &font, "ABCDEFG", glm::vec2(200 + 200, 400), glm::vec2(1.0, 1.0), 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion2D::AnchorMode::ANCHOR_CENTER, 0, true);
}

//--------------------------------------------------------------
void ofApp::update(){
	now += delta;
	for (int i = 0; i < 6; i++) {
		motion[i].update(now);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < 6; i++) {
		motion[i].draw();
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
			motion[i].setAnchorMode(ofxMotion2D::AnchorMode::ANCHOR_CENTER);
		}
	}
	else if (key == '2') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion2D::AnchorMode::ANCHOR_BOTTOM_CENTER);
		}
	}
	else if (key == '3') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion2D::AnchorMode::ANCHOR_TOP_LEFT);
		}
	}
	else if (key == '4') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion2D::AnchorMode::ANCHOR_TOP_RIGHT);
		}
	}
	else if (key == '5') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion2D::AnchorMode::ANCHOR_BOTTOM_LEFT);
		}
	}
	else if (key == '6') {
		for (int i = 0; i < 6; i++) {
			motion[i].setAnchorMode(ofxMotion2D::AnchorMode::ANCHOR_BOTTOM_RIGHT);
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
