#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	margin = 50;
	rectMoveArea.set(0 + margin, 0 + margin, ofGetWidth() - margin * 2, ofGetHeight() - margin * 2);

	xCanMove = 500;
	yCanMove = 500;

	for (int c = 0; c < 4; c++) {
		for (int r = 0; r < 10; r++) {
			int row = ((rectMoveArea.getWidth() - margin) / 10) * r + 175;
			int col = ((rectMoveArea.getHeight() - margin) / 4) * c + 200;
			int index = r + (c * 10);
			posInit[index] = vec2(row, col);
			sizeInit[index] = 0.13;
			if (ofRandomf() > 0.5) {
				sizeInit[index] = 0.17;
			}
		}
	}

	for (int i = 0; i < itemMaxSize; i++) {
		imageItems[i].load("image_fx_" + ofToString(i + 1) + ".jpg");
		imagePanels[i] = imageItems[i];
		imageItems[i].resize(imageItems[i].getWidth() * sizeInit[i], imageItems[i].getHeight() * sizeInit[i]);
		motions[i].setMotionTransformPtr(new MoveCurve());
		motions[i].setMotionColorPtr(new DefaultColor());
		motions[i].setup(ofxMotion::DrawMode::IMAGE, &imageItems[i], posInit[i], vec2(1.0, 1.0), imageItems[i].getWidth(), imageItems[i].getHeight(), 0.0f, ofxMotion::AnchorMode::ANCHOR_CENTER, true);
	}

	motionPanel.setMotionTransformPtr(new DefaultTransform());
	motionPanel.setMotionColorPtr(new FadeInFadeOut());
	motionPanel.setup(ofxMotion::DrawMode::IMAGE, &imagePanels[0], vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5), vec2(1.0, 1.0), imagePanels[0].getWidth() * 0.8, imagePanels[0].getHeight() * 0.8, 0.0f, ofxMotion::AnchorMode::ANCHOR_CENTER);

	motionModal.setMotionTransformPtr(new DefaultTransform());
	motionModal.setMotionColorPtr(new FadeInFadeOut());
	motionModal.setup(ofxMotion::DrawMode::RECT, vec2(0, 0), vec2(1.0, 1.0), ofGetWidth(), ofGetHeight(), 0.0f, ofColor(0), ofxMotion::AnchorMode::ANCHOR_TOP_LEFT);

	imageClose.load("close.png");
	motionClose.setMotionTransformPtr(new DefaultTransform());
	motionClose.setMotionColorPtr(new FadeInFadeOut());
	motionClose.setup(ofxMotion::DrawMode::IMAGE, &imageClose, vec2(ofGetWidth() * 0.5 + 410, 130), vec2(1.0, 1.0), imageClose.getWidth(), imageClose.getHeight(), 0.0f, ofxMotion::AnchorMode::ANCHOR_CENTER);

	for (int i = 0; i < itemMaxSize; i++) {
		startMove(i, -1, 1, -1, 1);
	}

	ofBackground(200);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update() {
	float now = ofGetElapsedTimef();

	for (int i = 0; i < itemMaxSize; i++) {
		motions[i].update(now);
		motionModal.update(now);
		motionPanel.update(now);
		motionClose.update(now);
	}

	for (int i = 0; i < itemMaxSize; i++) {
		for (int k = i + 1; k < itemMaxSize; k++) {
			if (motions[k].collision(motions[i].getPos(ofxMotion::POS_BOTTOM_RIGHT))) {
				startMove(i, -1, 0, -1, 0);
				startMove(k, 0, 1, 0, 1);
			}
			else if (motions[k].collision(motions[i].getPos(ofxMotion::POS_RIGHT_CENTER))) {
				startMove(i, -1, 0, 0, 0);
				startMove(k, 0, 1, 0, 0);
			}
			else if (motions[k].collision(motions[i].getPos(ofxMotion::POS_TOP_RIGHT))) {
				startMove(i, -1, 0, 0, 1);
				startMove(k, 0, 1, -1, 0);
			}
			else if (motions[k].collision(motions[i].getPos(ofxMotion::POS_TOP_CENTER))) {
				startMove(i, 0, 0, 0, 1);
				startMove(k, 0, 0, -1, 0);
			}
			else if (motions[k].collision(motions[i].getPos(ofxMotion::POS_TOP_LEFT))) {
				startMove(i, 0, 1, 0, 1);
				startMove(k, -1, 0, -1, 0);
			}
			else if (motions[k].collision(motions[i].getPos(ofxMotion::POS_LEFT_CENTER))) {
				startMove(i, 0, 1, 0, 0);
				startMove(k, -1, 0, 0, 0);
			}
			else if (motions[k].collision(motions[i].getPos(ofxMotion::POS_BOTTOM_LEFT))) {
				startMove(i, 0, 1, -1, 0);
				startMove(k, -1, 0, 0, 1);
			}
			else if (motions[k].collision(motions[i].getPos(ofxMotion::POS_BOTTOM_CENTER))) {
				startMove(i, 0, 0, -1, 0);
				startMove(k, 0, 0, 0, 1);
			}
		}
	}

	for (int i = 0; i < itemMaxSize; i++) {
		if (motions[i].getPos(ofxMotion::POS_BOTTOM_RIGHT).x > rectMoveArea.getX() + rectMoveArea.getWidth()) {
			startMove(i, -1, 0, -1, 1);
		}
		else if (motions[i].getPos(ofxMotion::POS_BOTTOM_RIGHT).y > rectMoveArea.getY() + rectMoveArea.getHeight()) {
			startMove(i, -1, 1, -1, 0);
		}
		else if (motions[i].getPos(ofxMotion::POS_TOP_LEFT).x < rectMoveArea.getX()) {
			startMove(i, 0, 1, -1, 1);
		}
		else if (motions[i].getPos(ofxMotion::POS_TOP_LEFT).y < rectMoveArea.getY()) {
			startMove(i, -1, 1, 0, 1);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(240);
	ofDrawRectangle(rectMoveArea);

	for (int i = 0; i < itemMaxSize; i++) {
		motions[i].draw();
	}
	motionModal.draw();
	motionPanel.draw();
	motionClose.draw();
}

//--------------------------------------------------------------
void ofApp::startMove(int index, int xDirMin, int xDirMax, int yDirMin, int yDirMax) {
	float x = ofRandom(xDirMin, xDirMax) * xCanMove;
	float y = ofRandom(yDirMin, yDirMax) * yCanMove;
	motions[index].getMotionTransform()->startMoveCurve(vec2(x, y), 100, 1, 60.0, 0.0, ofxeasing::linear::easeNone);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (bStateDisplayPanel) {
		if (motionClose.insideCircle(x, y)) {
			bStateDisplayPanel = false;
			motionPanel.getMotionColor()->startFadeOutForce(0, 0.5, ofxeasing::quart::easeOut);
			motionModal.getMotionColor()->startFadeOutForce(0, 0.5, ofxeasing::quart::easeOut);
			motionClose.getMotionColor()->startFadeOutForce(0, 0.5, ofxeasing::quart::easeOut);
			for (int j = 0; j < itemMaxSize; j++){
				motions[j].setStateInside(true);
			}
		}
	}
	else {
		for (int i = 0; i < itemMaxSize; i++) {
			if (motions[i].insideRect(x, y)) {
				bStateDisplayPanel = true;
				motionPanel.setImage(&imagePanels[i]);
				motionPanel.getMotionColor()->startFadeInFadeOut(0, 255, 0.5, 60, 0.5, ofxeasing::quart::easeOut);
				motionModal.getMotionColor()->startFadeInFadeOut(0, 200, 0.5, 60, 0.5, ofxeasing::quart::easeOut);
				motionClose.getMotionColor()->startFadeInFadeOut(0, 255, 0.5, 60, 0.5, ofxeasing::quart::easeOut);
				for (int j = 0; j < itemMaxSize; j++){
					motions[j].setStateInside(false);
				}
			}
		}
	}
}