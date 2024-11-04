#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	imageFish[0].load("akaei.png");
	imageFish[1].load("amimehagi.png");
	imageFish[2].load("gonzui.png");
	imageFish[3].load("ishigarei.png");
	imageFish[4].load("kagokidai.png");
	imageFish[5].load("korodai.png");
	imageFish[6].load("kurodai.png");
	imageFish[7].load("kyuusen.png");
	imageFish[8].load("maaji.png");
	imageFish[9].load("nanyoutsubameuo.png");
	imageFish[10].load("oyabiccha.png");
	imageFish[11].load("shirogisu.png");
	imageFish[12].load("soushihagi.png");
	imageFish[13].load("togechouchouuo.png");
	imageFish[14].load("tsubakuroei.png");

	posFish[0] = vec2(-200, 980);
	posFish[1] = vec2(640, 980);
	posFish[2] = vec2(1280, 980);
	posFish[3] = vec2(0, 350);
	posFish[4] = vec2(640, 350);
	posFish[5] = vec2(1280, 350);
	posFish[6] = vec2(320, 500);
	posFish[7] = vec2(960, 500);
	posFish[8] = vec2(1600, 500);
	posFish[9] = vec2(640, 650);
	posFish[10] = vec2(1280, 650);
	posFish[11] = vec2(1920, 650);
	posFish[12] = vec2(320, 800);
	posFish[13] = vec2(960, 800);
	posFish[14] = vec2(1600, 800);

	int groupLeft[9] = { 0, 1, 2, 3, 4, 5, 9, 10, 11 };

	for (int i = 0; i < fishMaxSize; i++) {
		motion[i].setMotionTransformPtr(new MoveLiner("MoveLiner"));
		motion[i].setMotionColorPtr(new NoColor("NoColor"));
		motion[i].setup(ofxMotion::DrawMode::IMAGE, &imageFish[i], posFish[i], vec2(1.0, 1.0), imageFish[i].getWidth(), imageFish[i].getHeight(), 0.0f, ofxMotion::AnchorMode::ANCOR_CENTER);
		
		auto itr = find(begin(groupLeft), end(groupLeft), i);
		if (itr != end(groupLeft)) {
			motion[i].setMirrorMode(false, false);
			motion[i].setDirectionMode(ofxMotion::DirectionMode::LEFT);
		}
		else {
			motion[i].setMirrorMode(false, true);
			motion[i].setDirectionMode(ofxMotion::DirectionMode::RIGHT);
		}
	}

	for (int i = 0; i < fishMaxSize; i++) {
		float duration = ofRandom(2.0, 5.0);
		float delay = 0.0;
		if (duration < 3.5) {
			delay = 1.5;
		}
		if (motion[i].getDirectionMode() == ofxMotion::DirectionMode::RIGHT) {
			motion[i].startMotion("MoveLiner", vec2(100, 0), duration, delay, ofxeasing::quint::easeOut);
		}
		else if (motion[i].getDirectionMode() == ofxMotion::DirectionMode::LEFT) {
			motion[i].startMotion("MoveLiner", vec2(-100, 0), duration, delay, ofxeasing::quint::easeOut);
		}
	}


	ofSetFrameRate(60);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	auto now = ofGetElapsedTimef();

	for (int i = 0; i < fishMaxSize; i++) {
		motion[i].update(now);
	}

	for (int i = 0; i < fishMaxSize; i++) {
		if (motion[i].getStateMotionTransform() == MotionTransformBase::MotionState::DONE) {
			if (motion[i].getDirectionMode() == ofxMotion::DirectionMode::RIGHT) {
				if (motion[i].getPos().x > ofGetWidth() + imageFish[i].getWidth() * 0.5) {
					motion[i].setPosMotionTransform(vec2(-imageFish[i].getWidth() * 0.5, motion[i].getPos().y));
				}
			}
			if (motion[i].getDirectionMode() == ofxMotion::DirectionMode::LEFT) {
				if (motion[i].getPos().x < 0 -imageFish[i].getWidth() * 0.5) {
					motion[i].setPosMotionTransform(vec2(ofGetWidth() + imageFish[i].getWidth() * 0.5, motion[i].getPos().y));
				}
			}
			
			float duration = ofRandom(2.0, 5.0);
			float delay = 0.0;
			if (duration < 3.5) {
				delay = 1.5;
			}
			if (motion[i].getDirectionMode() == ofxMotion::DirectionMode::RIGHT) {
				motion[i].startMotion("MoveLiner", vec2(100, 0), duration, delay, ofxeasing::quint::easeOut);
			}
			else if (motion[i].getDirectionMode() == ofxMotion::DirectionMode::LEFT) {
				motion[i].startMotion("MoveLiner", vec2(-100, 0), duration, delay, ofxeasing::quint::easeOut);
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