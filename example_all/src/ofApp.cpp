#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	motionColor.setMotionTransformPtr(new NoTransform());
	motionColor.setMotionColorPtr(new ColorGradation());
	motionColor.setup(ofxMotion::DrawMode::RECT, vec2(560, 37), vec2(1.0, 1.0), 15, 275, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	for (int i = 0; i < 6; i++) {
		motionMoveLiner[i].setMotionTransformPtr(new MoveLiner());
		motionMoveLiner[i].setMotionColorPtr(new NoColor());
		motionMoveLiner[i].setup(ofxMotion::DrawMode::RECT, vec2(100, i * 50 + 50), vec2(1.0, 1.0), 25, 25, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	for (int i = 0; i < 6; i++) {
		motionMoveCurve[i].setMotionTransformPtr(new MoveCurve());
		motionMoveCurve[i].setMotionColorPtr(new NoColor());
		motionMoveCurve[i].setup(ofxMotion::DrawMode::CIRCLE, vec2(100, i * 50 + 50), vec2(1.0, 1.0), 10, 0, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	for (int i = 0; i < 5; i++) {
		motionRadialNoise[i].setMotionTransformPtr(new RadialNoise());
		motionRadialNoise[i].setMotionColorPtr(new NoColor());
		motionRadialNoise[i].setup(ofxMotion::DrawMode::RECT, vec2(ofRandom(0, 5), ofRandom(0, 5)), vec2(1.0, 1.0), 100, 10, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER);
		motionRadialNoise[i].getMotionTransform()->startRadialNoise(275, 0.425, vec2(880, 200), 9999.0);
	}

	for (int i = 0; i < 3; i++) {
		motionRotate[i].setMotionTransformPtr(new Rotate());
		motionRotate[i].setMotionColorPtr(new NoColor());
		motionRotate[i].setup(ofxMotion::DrawMode::RECT, vec2(1350, 170), vec2(1.0, 1.0), 250, 10, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	for (int i = 3; i < 5; i++) {
		motionRotate[i].setMotionTransformPtr(new Rotate());
		motionRotate[i].setMotionColorPtr(new NoColor());
		motionRotate[i].setup(ofxMotion::DrawMode::CIRCLE, vec2(1350, 170), vec2(1.0, 1.0), ofRandom(5, 12), 0, ofRandom(0.1, 180.0), ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);
	}

	ofBackground(255);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	auto now = ofGetElapsedTimef();
	timer(now);

	motionColor.update(now);

	for (int i = 0; i < 6; i++) {
		motionMoveLiner[i].update(now);
	}

	for (int i = 0; i < 5; i++) {
		motionRadialNoise[i].update(now);
	}

	for (int i = 0; i < 6; i++) {
		motionMoveCurve[i].update(now);
	}

	for (int i = 0; i < 5; i++) {
		motionRotate[i].update(now);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	motionColor.draw();

	for (int i = 0; i < 6; i++) {
		motionMoveLiner[i].draw();
	}

	for (int i = 0; i < 5; i++) {
		motionRadialNoise[i].draw();
	}

	for (int i = 0; i < 6; i++) {
		motionMoveCurve[i].draw();
	}

	for (int i = 0; i < 5; i++) {
		motionRotate[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::timer(float now) {
	float timer = now - timerLapTime;
	if (timer >= timerSleepTime) {
		timerLapTime = now;

		motionColor.getMotionColor()->startColorGradation(1.0, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxeasing::quart::easeOut);

		motionMoveLiner[0].getMotionTransform()->startMoveLiner(vec2(100, 50), vec2(500, 50), 1.0, 0, ofxeasing::quart::easeOut);
		motionMoveLiner[1].getMotionTransform()->startMoveLiner(vec2(100, 100), vec2(500, 100), 1.0, 0, ofxeasing::quad::easeOut);
		motionMoveLiner[2].getMotionTransform()->startMoveLiner(vec2(100, 150), vec2(500, 150), 1.0, 0, ofxeasing::linear::easeNone);
		motionMoveLiner[3].getMotionTransform()->startMoveLiner(vec2(100, 200), vec2(500, 200), 1.0, 0, ofxeasing::quart::easeIn);
		motionMoveLiner[4].getMotionTransform()->startMoveLiner(vec2(100, 250), vec2(500, 250), 1.0, 0, ofxeasing::exp::easeIn);
		motionMoveLiner[5].getMotionTransform()->startMoveLiner(vec2(100, 300), vec2(500, 300), 1.0, 0, ofxeasing::back::easeIn);

		motionMoveCurve[0].getMotionTransform()->startMoveCurve(vec2(100, 50), vec2(500, 50), 100, -1, 1.0, 0, ofxeasing::quart::easeOut);
		motionMoveCurve[1].getMotionTransform()->startMoveCurve(vec2(100, 100), vec2(500, 100), 100, -1, 1.0, 0, ofxeasing::quad::easeOut);
		motionMoveCurve[2].getMotionTransform()->startMoveCurve(vec2(100, 150), vec2(500, 150), 100, -1, 1.0, 0, ofxeasing::linear::easeNone);
		motionMoveCurve[3].getMotionTransform()->startMoveCurve(vec2(100, 200), vec2(500, 200), 100, 1, 1.0, 0, ofxeasing::quart::easeIn);
		motionMoveCurve[4].getMotionTransform()->startMoveCurve(vec2(100, 250), vec2(500, 250), 100, 1, 1.0, 0, ofxeasing::exp::easeIn);
		motionMoveCurve[5].getMotionTransform()->startMoveCurve(vec2(100, 300), vec2(500, 300), 100, 1, 1.0, 0, ofxeasing::back::easeIn);

		motionRotate[0].getMotionTransform()->startRotate(5.0, vec2(0, 0), 0.5, ofxeasing::quart::easeOut);
		motionRotate[1].getMotionTransform()->startRotate(30.0, vec2(0, 0), 0.5, ofxeasing::quart::easeOut);
		motionRotate[2].getMotionTransform()->startRotate(30.0, vec2(0, 0), 3.0, ofxeasing::linear::easeNone);
		motionRotate[3].getMotionTransform()->startRotate(180.0, vec2(100, 100), 3.0, ofxeasing::linear::easeNone);
		motionRotate[4].getMotionTransform()->startRotate(45.0, vec2(120, 120), 3.0, ofxeasing::linear::easeNone);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
