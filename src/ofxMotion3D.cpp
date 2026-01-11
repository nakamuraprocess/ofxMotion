#include "ofxMotion3D.h"

void ofxMotion3D::setMotionTransformPtr(MotionTransform3D* ptr) {
	motionTransform = ptr;
}

void ofxMotion3D::setMotionColorPtr(MotionColor* ptr) {
	motionColor = ptr;
}

void ofxMotion3D::setup(glm::vec3 pos, glm::vec3 scale, float width, float height) {
	motionTransform->setup(pos, pos, scale, width, height, width, height, 0.0);
	motionColor->setup(ofColor(0, 0), ofColor(0, 0));
}

void ofxMotion3D::update(const float currentTime) {
	motionTransform->update(currentTime);
	motionColor->update(currentTime);
}

glm::vec3 ofxMotion3D::getPos() {
	return motionTransform->getPos();
}

MotionTransform3D::MotionState ofxMotion3D::getStateMotionTransform() {
	return motionTransform->getState();
}

MotionColor::MotionState ofxMotion3D::getStateMotionColor() {
	return motionColor->getState();
}

MotionTransform3D* ofxMotion3D::getMotionTransform() {
	return motionTransform;
}

MotionColor* ofxMotion3D::getMotionColor() {
	return motionColor;
}

void ofxMotion3D::setStateMotionTransform(MotionTransform3D::MotionState state) {
	motionTransform->setState(state);
}

void ofxMotion3D::setPos(glm::vec3 pos) {
	motionTransform->setPos(pos);
}