#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	fps = 60;
	ofSetFrameRate(fps);
	ofSetVerticalSync(true);
	delta = 1.0f / fps;
	ofBackground(255);

	motion.setMotionTransformPtr(new MoveCurve());
	motion.setMotionColorPtr(new DefaultColor());
	motion.setup(ofxMotion::DrawMode::CIRCLE, glm::vec2(500, 500), glm::vec2(1.0, 1.0), 4, 4, 0.0f, ofColor(19, 20, 192), ofxMotion::AnchorMode::ANCHOR_CENTER, 0, true);
	posHistory.push_back(glm::vec2(500, 500));
}

//--------------------------------------------------------------
void ofApp::update(){
	now += delta;
	motion.update(now);
	posHistory.push_back(motion.getPos());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushStyle();
	ofSetColor(150, 150, 150);
	for (int i = 0; i < 100; i++) {
		ofLine(0, i * 20, ofGetWidth(), i * 20);
		ofLine(i * 20, 0, i * 20, ofGetHeight());
	}
	ofSetColor(50, 50, 50);
	ofLine(ofGetWidth() * 0.5, 0, ofGetWidth() * 0.5, ofGetHeight());
	ofLine(0, ofGetHeight() * 0.5, ofGetWidth(), ofGetHeight() * 0.5);
	ofPopStyle();

	ofSetColor(255, 0, 0, 50);
	for (int i = 0; i < posHistory.size(); i++) {
		ofDrawCircle(posHistory[i], 5);
	}
	
	motion.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == '1') {
		motion.getMotionTransform()->startMoveCurve(glm::vec2(500, 500), glm::vec2(1000, 500), 100, 1.0, 0.0, ofxeasing::quart::easeOut);
	}
	else if (key == '2') {
		motion.getMotionTransform()->startMoveCurve(glm::vec2(500, 500), glm::vec2(500, 0), 100, 1.0, 0.0, ofxeasing::quart::easeOut);
	}
	else if (key == '3') {
		motion.getMotionTransform()->startMoveCurve(glm::vec2(500, 500), glm::vec2(0, 500), 100, 1.0, 0.0, ofxeasing::quart::easeOut);
	}
	else if (key == '4') {
		motion.getMotionTransform()->startMoveCurve(glm::vec2(500, 500), glm::vec2(500, 1000), 100, 1.0, 0.0, ofxeasing::quart::easeOut);
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
