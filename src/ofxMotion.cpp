#include "ofxMotion.h"

void ofxMotion::setup(DrawMode drawMode, vec2 pos, vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	motionTransform->setup(pos, scale, width, height, degrees);
	motionColor->setup(color, color);
}

void ofxMotion::setup(DrawMode drawMode, ofImage* image, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->image = image;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
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

	vec2 anchorPos = getAnchorPos(motionTransform->getWidth(), motionTransform->getHeight());
	if (image != nullptr) {
		image->setAnchorPoint(anchorPos.x, anchorPos.y);
	}
	if (textureText.isAllocated()) {
		textureText.setAnchorPoint(anchorPos.x, anchorPos.y);
	}
}

void ofxMotion::draw() {
	stateTransform = motionTransform->getState();
	stateColor = motionColor->getState();
	if (stateTransform == MotionTransformBase::RUNNING || stateColor == MotionColorBase::RUNNING || bStateDisplay) {
		ofPushStyle();
		if (drawMode == IMAGE) {
			ofSetColor(255, motionColor->getColor().a);
		}
		else {
			ofSetColor(motionColor->getColor());
		}
		
		ofPushMatrix();
		float x = motionTransform->getPos().x;
		float y = motionTransform->getPos().y;
		float width = motionTransform->getWidth();
		float height = motionTransform->getHeight();

		if (motionTransform->getDegrees() != 0.0) {
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofTranslate(motionTransform->getPos());
			ofRotateDeg(motionTransform->getDegrees());
			x = motionTransform->getAnchorPosForRotation();
			y = motionTransform->getAnchorPosForRotation();
			rectangle.setX(x);
			rectangle.setY(y);
		}

		if (drawMode == RECT) {
			ofDrawRectangle(rectangle);
		}
		else if (drawMode == CIRCLE) {
			ofDrawCircle(x, y, width * 0.5 + height * 0.5);
		}
		else if (drawMode == TRIANGLE) {
			ofDrawTriangle(x, y, x - width, y + height, x + width, y + height);
		}
		else if (drawMode == TEXT) {
			textureText.draw(x, y, width, height);
		}
		else {
			image->draw(x, y, width, height);
		}

		ofPopMatrix();
		ofPopStyle();
	}
}

vec2 ofxMotion::getAnchorPos(float width, float height) const {
	vec2 anchorPos = vec2(0, 0);
	if (anchor == ANCHOR_CENTER) {
		anchorPos = vec2(width * 0.5, height * 0.5);
	}
	else if (anchor == ANCHOR_BOTTOM_CENTER) {
		anchorPos = vec2(width * 0.5, height);
	}
	else if (anchor == ANCHOR_BOTTOM_LEFT) {
		anchorPos = vec2(0, height);
	}
	else if (anchor == ANCHOR_BOTTOM_RIGHT) {
		anchorPos = vec2(width, height);
	}
	else if (anchor == ANCHOR_TOP_LEFT) {
		anchorPos = vec2(0, 0);
	}
	else if (anchor == ANCHOR_TOP_RIGHT) {
		anchorPos = vec2(width, 0);
	}
	return anchorPos;
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

MotionTransformBase* ofxMotion::getMotionTransform() {
	return motionTransform;
}

MotionColorBase* ofxMotion::getMotionColor() {
	return motionColor;
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

void ofxMotion::setImage(ofImage* image) {
	this->image = image;
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
	if (anchor == ANCHOR_CENTER) {
		rectangle.set(x - width * 0.5, y - height * 0.5, width, height);
	}
	else if (anchor == ANCHOR_BOTTOM_CENTER) {
		rectangle.set(x - width * 0.5, y, width, -height);
	}
	else if (anchor == ANCHOR_BOTTOM_LEFT) {
		rectangle.set(x, y, width, -height);
	}
	else if (anchor == ANCHOR_BOTTOM_RIGHT) {
		rectangle.set(x, y, -width, -height);
	}
	else if (anchor == ANCHOR_TOP_LEFT) {
		rectangle.set(x, y, width, height);
	}
	else if (anchor == ANCHOR_TOP_RIGHT) {
		rectangle.set(x, y, -width, height);
	}
}