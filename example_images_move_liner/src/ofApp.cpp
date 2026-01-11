#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	fps = 60;
	ofSetFrameRate(fps);
	ofSetVerticalSync(true);
	delta = 1.0f / fps;

	for (int i = 0; i < fishMaxSize; i++) {
		imageFish[i].load("image_fx_"+ ofToString(i+1) + ".png");
	}

	posFish[0] = glm::vec2(-200, 980);
	posFish[1] = glm::vec2(640, 980);
	posFish[2] = glm::vec2(1280, 980);
	posFish[3] = glm::vec2(0, 350);
	posFish[4] = glm::vec2(640, 350);
	posFish[5] = glm::vec2(1280, 350);
	posFish[6] = glm::vec2(320, 500);
	posFish[7] = glm::vec2(960, 500);
	posFish[8] = glm::vec2(1600, 500);
	posFish[9] = glm::vec2(640, 650);
	posFish[10] = glm::vec2(1280, 650);
	posFish[11] = glm::vec2(1920, 650);
	posFish[12] = glm::vec2(320, 800);
	posFish[13] = glm::vec2(960, 800);
	posFish[14] = glm::vec2(1600, 800);

	int groupLeft[9] = { 0, 1, 2, 3, 4, 5, 9, 10, 11 };

	for (int i = 0; i < fishMaxSize; i++) {
		motion[i].setMotionTransformPtr(new MoveLiner());
		motion[i].setMotionColorPtr(new DefaultColor());
		motion[i].setup(ofxMotion2D::DrawMode::IMAGE, &imageFish[i], posFish[i], glm::vec2(1.0, 1.0), imageFish[i].getWidth(), imageFish[i].getHeight(), 0.0f, ofxMotion2D::AnchorMode::ANCHOR_CENTER, 0);
		
		auto itr = find(begin(groupLeft), end(groupLeft), i);
		if (itr != end(groupLeft)) {
			motion[i].setMirrorMode(false, false);
			moveDirection[i] = LEFT;
		}
		else {
			motion[i].setMirrorMode(false, true);
			moveDirection[i] = RIGHT;
		}
	}

	for (int i = 0; i < fishMaxSize; i++) {
		float duration = ofRandom(2.0, 5.0);
		float delay = 0.0;
		if (duration < 3.5) {
			delay = 1.5;
		}
		if (moveDirection[i] == RIGHT) {
			motion[i].getMotionTransform()->startMoveLiner(glm::vec2(100, 0), duration, delay, ofxeasing::quint::easeOut);
		}
		if (moveDirection[i] == LEFT) {
			motion[i].getMotionTransform()->startMoveLiner(glm::vec2(-100, 0), duration, delay, ofxeasing::quint::easeOut);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	now += delta;

	for (int i = 0; i < fishMaxSize; i++) {
		motion[i].update(now);
	}

	for (int i = 0; i < fishMaxSize; i++) {
		if (motion[i].getStateMotionTransform() == MotionTransform2D::MotionState::DONE) {
			if (moveDirection[i] == RIGHT) {
				if (motion[i].getPos().x > ofGetWidth() + imageFish[i].getWidth() * 0.5) {
					motion[i].setPos(glm::vec2(-imageFish[i].getWidth() * 0.5, motion[i].getPos().y));
				}
			}
			if (moveDirection[i] == LEFT) {
				if (motion[i].getPos().x < 0 -imageFish[i].getWidth() * 0.5) {
					motion[i].setPos(glm::vec2(ofGetWidth() + imageFish[i].getWidth() * 0.5, motion[i].getPos().y));
				}
			}
			
			float duration = ofRandom(2.0, 5.0);
			float delay = 0.0;
			if (duration < 3.5) {
				delay = 1.5;
			}
			if (moveDirection[i] == RIGHT) {
				motion[i].getMotionTransform()->startMoveLiner(glm::vec2(100, 0), duration, delay, ofxeasing::quint::easeOut);
			}
			else if (moveDirection[i] == LEFT) {
				motion[i].getMotionTransform()->startMoveLiner(glm::vec2(-100, 0), duration, delay, ofxeasing::quint::easeOut);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(96, 148, 192), ofColor(19, 25, 192), OF_GRADIENT_LINEAR);

	for (int i = 0; i < fishMaxSize; i++) {
		motion[i].draw();
	}
}