#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetCircleResolution(48);

	for (int i = 0; i < 6; i++) {
		motionMoveLiner[i].setMotionTransformPtr(new MoveLiner());
		motionMoveLiner[i].setMotionColorPtr(new DefaultColor());
		motionMoveLiner[i].setup(ofxMotion::DrawMode::RECT, vec2(100, i * 50 + 50), vec2(1.0, 1.0), 25, 25, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	for (int i = 0; i < 6; i++) {
		motionMoveCurve[i].setMotionTransformPtr(new MoveCurve());
		motionMoveCurve[i].setMotionColorPtr(new DefaultColor());
		motionMoveCurve[i].setup(ofxMotion::DrawMode::CIRCLE, vec2(100, i * 50 + 50), vec2(1.0, 1.0), 10, 10, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	motionColor.setMotionTransformPtr(new DefaultTransform());
	motionColor.setMotionColorPtr(new ColorGradation());
	motionColor.setup(ofxMotion::DrawMode::RECT, vec2(560, 37), vec2(1.0, 1.0), 15, 275, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	for (int i = 0; i < 5; i++) {
		motionSignedNoise[i].setMotionTransformPtr(new SignWaveNoise());
		motionSignedNoise[i].setMotionColorPtr(new DefaultColor());
		motionSignedNoise[i].setup(ofxMotion::DrawMode::RECT, vec2(ofRandom(0, 5), ofRandom(0, 5)), vec2(1.0, 1.0), 100, 10, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER);
		motionSignedNoise[i].getMotionTransform()->startSignWaveNoise(vec2(275, 275), 0.425, vec2(960, 200), 9999.0);
	}

	for (int i = 0; i < 3; i++) {
		motionRotate[i].setMotionTransformPtr(new Rotate());
		motionRotate[i].setMotionColorPtr(new DefaultColor());
		motionRotate[i].setup(ofxMotion::DrawMode::RECT, vec2(1550, 170), vec2(1.0, 1.0), 250, 10, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	motionRotate[3].setMotionTransformPtr(new Rotate());
	motionRotate[3].setMotionColorPtr(new DefaultColor());
	motionRotate[3].setup(ofxMotion::DrawMode::TRIANGLE, vec2(1550, 170), vec2(1.0, 1.0), 30, 30, ofRandom(0.1, 180.0), ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	motionRotate[4].setMotionTransformPtr(new Rotate());
	motionRotate[4].setMotionColorPtr(new DefaultColor());
	motionRotate[4].setup(ofxMotion::DrawMode::TRIANGLE, vec2(1550, 170), vec2(1.0, 1.0), 22, 22, ofRandom(0.1, 180.0), ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT, true);

	motionScale[0].setMotionTransformPtr(new Scale());
	motionScale[1].setMotionTransformPtr(new Bounce());
	motionScale[2].setMotionTransformPtr(new Bounce());
	for (int i = 0; i < 3; i++) {
		motionScale[i].setMotionColorPtr(new DefaultColor());
	}
	motionScale[0].setup(ofxMotion::DrawMode::CIRCLE, vec2(300, 600), vec2(1.0, 1.0), 99, 34, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	motionScale[1].setup(ofxMotion::DrawMode::CIRCLE, vec2(300, 600), vec2(1.0, 1.0), 100, 50, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	motionScale[2].setup(ofxMotion::DrawMode::CIRCLE, vec2(300, 600), vec2(1.0, 1.0), 60, 30, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);

	for (int i = 0; i < 10; i++) {
		motionMoveRadial[i].setMotionTransformPtr(new MoveRadial());
		motionMoveRadial[i].setMotionColorPtr(new DefaultColor());
		motionMoveRadial[i].setup(ofxMotion::DrawMode::CIRCLE, vec2(300, 600), vec2(1.0, 1.0), 14, 14, 0.0f, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	image.load("image_fx_1.jpg");
	motionImage.setMotionTransformPtr(new DefaultTransform());
	motionImage.setMotionColorPtr(new FadeInFadeOut());
	motionImage.setup(ofxMotion::DrawMode::IMAGE, &image, vec2(960, 600), vec2(1.0, 1.0), image.getWidth() * 0.3, image.getHeight() * 0.3, 0.0f, ofxMotion::AnchorMode::ANCHOR_CENTER);

	font.load("NotoSansCJKjp-Regular.otf", 20);
	for (int i = 0; i < 10; i++) {
		motionText[i].setMotionTransformPtr(new MoveCircle());
		motionText[i].setMotionColorPtr(new DefaultColor());
		string text = ofToString(100001 + i);
		motionText[i].setup(ofxMotion::DrawMode::TEXT, &font, text, vec2(1550, 600), vec2(1.0, 1.0), 0.0, ofColor(65, 56, 56, 200), ofxMotion::AnchorMode::ANCHOR_CENTER, true);
		float radian = (TWO_PI / 10) * i;
		motionText[i].getMotionTransform()->startMoveCircle(radian, vec2(100, 150), 3.0, 0.0, ofxeasing::cubic::easeOut);
	}

	ofBackground(255);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	float now = ofGetElapsedTimef();
	timer(now);

	for (int i = 0; i < 6; i++) {
		motionMoveLiner[i].update(now);
	}
	for (int i = 0; i < 6; i++) {
		motionMoveCurve[i].update(now);
	}
	motionColor.update(now);
	for (int i = 0; i < 5; i++) {
		motionSignedNoise[i].update(now);
	}
	for (int i = 0; i < 5; i++) {
		motionRotate[i].update(now);
	}
	for (int i = 0; i < 3; i++) {
		motionScale[i].update(now);
	}
	for (int i = 0; i < 10; i++) {
		motionMoveRadial[i].update(now);
	}
	motionImage.update(now);
	for (int i = 0; i < 10; i++) {
		motionText[i].update(now);
	}

	for (int i = 0; i < 10; i++) {
		if (motionText[i].getStateMotionTransform() == MotionTransformBase::MotionState::DONE) {
			float radian = (TWO_PI / 10) * i;
			motionText[i].getMotionTransform()->startMoveCircle(radian, vec2(100, 150), 3.0, 0.0, ofxeasing::cubic::easeOut);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < 6; i++) {
		motionMoveLiner[i].draw();
	}
	for (int i = 0; i < 6; i++) {
		motionMoveCurve[i].draw();
	}
	motionColor.draw();
	for (int i = 0; i < 5; i++) {
		motionSignedNoise[i].draw();
	}
	for (int i = 0; i < 5; i++) {
		motionRotate[i].draw();
	}
	for (int i = 0; i < 3; i++) {
		motionScale[i].draw();
	}
	for (int i = 0; i < 10; i++) {
		motionMoveRadial[i].draw();
	}
	motionImage.draw();
	for (int i = 0; i < 10; i++) {
		motionText[i].draw();
	}
}

//--------------------------------------------------------------
void ofApp::timer(float now) {
	float timer = now - timerLapTime;
	if (timer >= timerSleepTime) {
		timerLapTime = now;

		motionMoveLiner[0].getMotionTransform()->startMoveLiner(vec2(100, 50), vec2(500, 50), 1.0, 0, ofxeasing::quart::easeOut);
		motionMoveLiner[1].getMotionTransform()->startMoveLiner(vec2(100, 100), vec2(500, 100), 1.0, 0, ofxeasing::quad::easeOut);
		motionMoveLiner[2].getMotionTransform()->startMoveLiner(vec2(100, 150), vec2(500, 150), 1.0, 0, ofxeasing::linear::easeNone);
		motionMoveLiner[3].getMotionTransform()->startMoveLiner(vec2(100, 200), vec2(500, 200), 1.0, 0, ofxeasing::quart::easeIn);
		motionMoveLiner[4].getMotionTransform()->startMoveLiner(vec2(100, 250), vec2(500, 250), 1.0, 0, ofxeasing::exp::easeIn);
		motionMoveLiner[5].getMotionTransform()->startMoveLiner(vec2(100, 300), vec2(500, 300), 1.0, 0, ofxeasing::back::easeIn);

		motionMoveCurve[0].getMotionTransform()->startMoveCurve(vec2(100, 50), vec2(500, 50), -100, 1.0, 0, ofxeasing::quart::easeOut);
		motionMoveCurve[1].getMotionTransform()->startMoveCurve(vec2(100, 100), vec2(500, 100), -100, 1.0, 0, ofxeasing::quad::easeOut);
		motionMoveCurve[2].getMotionTransform()->startMoveCurve(vec2(100, 150), vec2(500, 150), -100, 1.0, 0, ofxeasing::linear::easeNone);
		motionMoveCurve[3].getMotionTransform()->startMoveCurve(vec2(100, 200), vec2(500, 200), 100, 1.0, 0, ofxeasing::quart::easeIn);
		motionMoveCurve[4].getMotionTransform()->startMoveCurve(vec2(100, 250), vec2(500, 250), 100, 1.0, 0, ofxeasing::exp::easeIn);
		motionMoveCurve[5].getMotionTransform()->startMoveCurve(vec2(100, 300), vec2(500, 300), 100, 1.0, 0, ofxeasing::back::easeIn);

		motionColor.getMotionColor()->startColorGradation(1.0, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)), ofxeasing::quart::easeOut);

		motionRotate[0].getMotionTransform()->startRotate(5.0, 0.0, 0.5, ofxeasing::quart::easeOut);
		motionRotate[1].getMotionTransform()->startRotate(30.0, 0.0, 0.5, ofxeasing::quart::easeOut);
		motionRotate[2].getMotionTransform()->startRotate(30.0, 0.0, 3.0, ofxeasing::linear::easeNone);
		motionRotate[3].getMotionTransform()->startRotate(180.0, 90.0, 3.0, ofxeasing::linear::easeNone);
		motionRotate[4].getMotionTransform()->startRotate(45.0, 140.0, 3.0, ofxeasing::linear::easeNone);

		motionScale[0].getMotionTransform()->startScale(vec2(1.0, 1.0), vec2(4.0, 4.0), 0.5, 0.0, ofxeasing::quart::easeOut);
		motionScale[1].getMotionTransform()->startBounce();
		motionScale[2].getMotionTransform()->startBounce();

		for (int i = 0; i < 10; i++) {
			float radian = (TWO_PI / 10) * i;
			motionMoveRadial[i].getMotionTransform()->startMoveRadial(radian, vec2(0, 0), vec2(160, 160), 1.5, 0.1 * i, ofxeasing::quart::easeOut);
		}

		motionImage.getMotionColor()->startFadeInFadeOut(0, 255, 1.0, 1.0, 1.0, ofxeasing::quart::easeOut);
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
