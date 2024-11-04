#include "ofxMotion.h"

void ofxMotion::setup(DrawMode drawMode, vec2 pos, vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->anchor = anchor;
	this->width = width;
	this->height = height;
	this->bStateDisplay = bStateDisplay;
	motionTransform->setup(pos, scale, width, height, degrees);
	motionColor->setup(color, color);
}


void ofxMotion::setup(DrawMode drawMode, ofImage* image, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->image = image;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	this->width = width;
	this->height = height;
	motionTransform->setup(pos, scale, width, height, degrees);
	motionColor->setup(ofColor(255), ofColor(255));
}


void ofxMotion::setup(DrawMode drawMode, ofTrueTypeFont* ttf, string strText, vec2 pos, vec2 scale, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->ttf = ttf;
	this->strText = strText;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	textureText = ttf->getStringTexture(strText);
	rectangle = ttf->getStringBoundingBox(strText, 0, 0);
	motionTransform->setup(pos, scale, rectangle.getWidth(), rectangle.getHeight(), degrees);
	motionColor->setup(color, color);
}


void ofxMotion::update(const float currentTime) {
	motionTransform->update(currentTime);
	motionColor->update(currentTime);
	setRect(motionTransform->getPos().x, motionTransform->getPos().y, motionTransform->getWidth(), motionTransform->getHeight());

	vec2 anchor = getAnchor(width, height);
	if (image != nullptr) {
		image->setAnchorPoint(anchor.x, anchor.y);
	}
	if (textureText.isAllocated()) {
		textureText.setAnchorPoint(anchor.x, anchor.y * 0.8);
	}
}


void ofxMotion::draw() {
	stateTransform = motionTransform->getState();
	stateColor = motionColor->getState();
	if (stateTransform == MotionTransformBase::RUNNING || stateColor == MotionColorBase::RUNNING || bStateDisplay) {
		ofPushMatrix();
		ofScale(motionTransform->getScale().x, motionTransform->getScale().y, 1.0);
		ofRotateDeg(motionTransform->getDegrees());
		ofPushStyle();
		
		ofSetColor(motionColor->getColor());

		if (drawMode == RECT) {
			ofDrawRectangle(rectangle);
		}
		else if (drawMode == CIRCLE) {
			ofDrawCircle(motionTransform->getPos(), width + height);
		}
		else if (drawMode == TRIANGLE) {
			ofDrawTriangle(motionTransform->getPos(), vec2(width, height), vec2(width, height));
		}
		else if (drawMode == TEXT) {
			textureText.draw(motionTransform->getPos());
		}
		else {
			ofSetColor(255, motionColor->getColor().a);
			image->draw(motionTransform->getPos(), width, height);
		}

		ofPopStyle();
		ofPopMatrix();
	}
}


vec2 ofxMotion::getPos() {
	return motionTransform->getPos();
}


ofxMotion::DirectionMode ofxMotion::getDirectionMode() {
	return directionMode;
}


MotionTransformBase::MotionState ofxMotion::getStateMotionTransform() {
	return motionTransform->getState();
}


MotionColorBase::MotionState ofxMotion::getStateMotionColor() {
	return motionColor->getState();
}

ofRectangle ofxMotion::getRectangle() {
	return rectangle;
}


void ofxMotion::setMotionTransformPtr(MotionTransformBase* ptr) {
	motionTransform = ptr;
}


void ofxMotion::setMotionColorPtr(MotionColorBase* ptr) {
	motionColor = ptr;
}


void ofxMotion::setStateStateMotionTransform(MotionTransformBase::MotionState state) {
	motionTransform->setState(state);
}


void ofxMotion::setPosMotionTransform(vec2 pos) {
	motionTransform->setPos(pos);
}


void ofxMotion::setDirectionMode(DirectionMode mode) {
	directionMode = mode;
}


void ofxMotion::setMirrorMode(bool vertical, bool horizon) {
	image->mirror(vertical, horizon);
}


void ofxMotion::setImage(ofImage* _image) {
	image = _image;
}


bool ofxMotion::inside(int x, int y) {
	if (!bStateInside) {
		return false;
	}
	return rectangle.inside(x, y);
}

bool ofxMotion::collision(int x, int y) {
	return rectangle.inside(x, y);
}


void ofxMotion::setStateInside(bool b) {
	bStateInside = b;
}


void ofxMotion::reset() {
	motionTransform->reset();
}


void ofxMotion::setRect(float x, float y, float width, float height) {
	if (anchor == ANCOR_CENTER) {
		rectangle.set(x - width * 0.5, y - height * 0.5, width, height);
	}
	else if (anchor == ANCOR_BOTTOM_CENTER) {
		rectangle.set(x - width * 0.5, y, width, -height);
	}
	else if (anchor == ANCOR_BOTTOM_LEFT) {
		rectangle.set(x, y, width, -height);
	}
	else if (anchor == ANCOR_BOTTOM_RIGHT) {
		rectangle.set(x, y, -width, -height);
	}
	else if (anchor == ANCOR_TOP_LEFT) {
		rectangle.set(x, y, width, height);
	}
	else if (anchor == ANCOR_TOP_RIGHT) {
		rectangle.set(x, y, -width, height);
	}
}


vec2 ofxMotion::getAnchor(float width, float height) {
	vec2 anchorPos = vec2(0, 0);
	if (anchor == ANCOR_CENTER) {
		anchorPos = vec2(width * 0.5, height * 0.5);
	}
	else if (anchor == ANCOR_BOTTOM_CENTER) {
		anchorPos = vec2(width * 0.5, height);
	}
	else if (anchor ==  ANCOR_BOTTOM_LEFT) {
		anchorPos = vec2(0, height);
	}
	else if (anchor == ANCOR_BOTTOM_RIGHT) {
		anchorPos = vec2(width, height);
	}
	else if (anchor == ANCOR_TOP_LEFT) {
		anchorPos = vec2(0, 0);
	}
	else if (anchor == ANCOR_TOP_RIGHT) {
		anchorPos = vec2(width, 0);
	}
	return anchorPos;
}