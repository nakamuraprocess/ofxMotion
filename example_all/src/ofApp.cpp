#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	motionColor.setMotionTransformPtr(new NoTransform());
	motionColor.setMotionColorPtr(new ColorGradation());
	motionColor.setup(ofxMotion::DrawMode::RECT, vec2(100, 350), vec2(1.0, 1.0), 550, 15, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	for (int i = 0; i < 6; i++) {
		motionMoveLiner[i].setMotionTransformPtr(new MoveLiner());
		motionMoveLiner[i].setMotionColorPtr(new NoColor());
		motionMoveLiner[i].setup(ofxMotion::DrawMode::RECT, vec2(50, i * 50 + 50), vec2(1.0, 1.0), 25, 25, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);
	}

	for (int i = 0; i < 5; i++) {
		motionRadialNoise[i].setMotionTransformPtr(new RadialNoise());
		motionRadialNoise[i].setMotionColorPtr(new NoColor());
		motionRadialNoise[i].setup(ofxMotion::DrawMode::RECT, vec2(ofRandom(0, 5), ofRandom(0, 5)), vec2(1.0, 1.0), 100, 10, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER);
		motionRadialNoise[i].getMotionTransform()->startRadialNoise(275, 0.425, vec2(960, 200), 9999.0);
	}

	for (int i = 0; i < 6; i++) {
		motionMoveCurve[i].setMotionTransformPtr(new MoveCurve());
		motionMoveCurve[i].setMotionColorPtr(new NoColor());
		motionMoveCurve[i].setup(ofxMotion::DrawMode::CIRCLE, vec2(62, i * 50 + 50 + 350), vec2(1.0, 1.0), 10, 0, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	for (int i = 0; i < 3; i++) {
		motionRotate[i].setMotionTransformPtr(new Rotate());
		motionRotate[i].setMotionColorPtr(new NoColor());
		motionRotate[i].setup(ofxMotion::DrawMode::RECT, vec2(1350, 175), vec2(1.0, 1.0), 200, 10, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
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

	for (int i = 0; i < 3; i++) {
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

	for (int i = 0; i < 3; i++) {
		motionRotate[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::timer(float now) {
	float timer = now - timerLapTime;
	if (timer >= timerSleepTime) {
		timerLapTime = now;

		motionColor.getMotionColor()->startColorGradation(1.0, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxeasing::linear::easeNone);

		motionMoveLiner[0].getMotionTransform()->startMoveLiner(vec2(50, 50), vec2(675, 50), 0.5, 0, ofxeasing::quart::easeOut);
		motionMoveLiner[1].getMotionTransform()->startMoveLiner(vec2(50, 100), vec2(675, 100), 0.5, 0, ofxeasing::quad::easeOut);
		motionMoveLiner[2].getMotionTransform()->startMoveLiner(vec2(50, 150), vec2(675, 150), 0.5, 0, ofxeasing::linear::easeNone);
		motionMoveLiner[3].getMotionTransform()->startMoveLiner(vec2(50, 200), vec2(675, 200), 0.5, 0, ofxeasing::quart::easeIn);
		motionMoveLiner[4].getMotionTransform()->startMoveLiner(vec2(50, 250), vec2(675, 250), 0.5, 0, ofxeasing::exp::easeIn);
		motionMoveLiner[5].getMotionTransform()->startMoveLiner(vec2(50, 300), vec2(675, 300), 0.5, 0, ofxeasing::back::easeIn);

		motionMoveCurve[0].getMotionTransform()->startMoveCurve(vec2(62, 400), vec2(688, 400), 100, -1, 1.5, 0, ofxeasing::quart::easeOut);
		motionMoveCurve[1].getMotionTransform()->startMoveCurve(vec2(62, 450), vec2(688, 450), 100, -1, 1.5, 0, ofxeasing::quad::easeOut);
		motionMoveCurve[2].getMotionTransform()->startMoveCurve(vec2(62, 500), vec2(688, 500), 100, -1, 1.5, 0, ofxeasing::linear::easeNone);
		motionMoveCurve[3].getMotionTransform()->startMoveCurve(vec2(62, 550), vec2(688, 550), 100, 1, 1.5, 0, ofxeasing::quart::easeIn);
		motionMoveCurve[4].getMotionTransform()->startMoveCurve(vec2(62, 600), vec2(688, 600), 100, 1, 1.5, 0, ofxeasing::exp::easeIn);
		motionMoveCurve[5].getMotionTransform()->startMoveCurve(vec2(62, 650), vec2(688, 650), 100, 1, 1.5, 0, ofxeasing::back::easeIn);

		motionRotate[0].getMotionTransform()->startRotate(5.0, 0.5, ofxeasing::quart::easeOut);
		motionRotate[1].getMotionTransform()->startRotate(30.0, 0.5, ofxeasing::quart::easeOut);
		motionRotate[2].getMotionTransform()->startRotate(30.0, 3.0, ofxeasing::linear::easeNone);
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
