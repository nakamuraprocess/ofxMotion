#include "ofxMotion.h"

void ofxMotion::setMotionTransformPtr(MotionTransformBase* ptr) {
	if (motionTransform != nullptr) {
		ptr->setup(motionTransform->getPos(), motionTransform->getPosInitial(), motionTransform->getScale(), 
			motionTransform->getWidth(), motionTransform->getHeight(), motionTransform->getWidthInitial(), motionTransform->getHeightInitial(), motionTransform->getDegrees());
	}
	motionTransform = ptr;
}

void ofxMotion::setMotionColorPtr(MotionColorBase* ptr) {
	if (motionColor != nullptr) {
		ptr->setup(motionColor->getColor(), motionColor->getColorInitial());
	}
	motionColor = ptr;
}

void ofxMotion::setup(DrawMode drawMode, vec2 pos, vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionColor->setup(color, color);
}

void ofxMotion::setup(DrawMode drawMode, ofImage* image, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->image = image;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionColor->setup(ofColor(255), ofColor(255));
}

void ofxMotion::setup(DrawMode drawMode, ofTexture* texture, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->texture = texture;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionColor->setup(ofColor(255), ofColor(255));
}

void ofxMotion::setup(DrawMode drawMode, ofTrueTypeFont* ttf, string strText, vec2 pos, vec2 scale, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->ttf = ttf;
	this->strText = strText;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	rectangle = ttf->getStringBoundingBox(strText, 0, 0);
	motionTransform->setup(pos, pos, scale, rectangle.getWidth(), rectangle.getHeight(), rectangle.getWidth(), rectangle.getHeight(), degrees);
	motionColor->setup(color, color);
}

void ofxMotion::setup(vec2 pos, vec2 scale, float width, float height) {
	this->drawMode = NONE;
	motionTransform->setup(pos, pos, scale, width, height, width, height, 0.0);
	motionColor->setup(ofColor(0,0), ofColor(0, 0));
}

void ofxMotion::update(const float currentTime) {
	motionTransform->update(currentTime);
	motionColor->update(currentTime);
	setRect(motionTransform->getPos().x, motionTransform->getPos().y, motionTransform->getWidth(), motionTransform->getHeight());
}

void ofxMotion::draw() {
	stateTransform = motionTransform->getState();
	stateColor = motionColor->getState();
	if (stateTransform == MotionTransformBase::RUNNING || stateColor == MotionColorBase::RUNNING || bStateDisplay) {
		ofPushStyle();
		if (drawMode == IMAGE || drawMode == TEXTURE || drawMode == FBO) {
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
			if (drawMode == IMAGE || drawMode == TEXTURE || drawMode == FBO) {
				ofSetRectMode(OF_RECTMODE_CORNER);
			}
			else {
				ofSetRectMode(OF_RECTMODE_CENTER);
			}
			ofTranslate(motionTransform->getPos());
			ofRotateDeg(motionTransform->getDegrees());
			x = motionTransform->getAnchorPosForRotation();
			y = motionTransform->getAnchorPosForRotation();
			rectangle.set(x, y, width, height);
		}

		if (drawMode == RECT) {
			ofDrawRectangle(rectangle);
		}
		else if (drawMode == CIRCLE) {
			float radius = width * 0.25 + height * 0.25;
			vec2 anchorPos = getAnchorPos(width * 0.5 + height * 0.5, width * 0.5 + height * 0.5);
			ofDrawCircle(x + radius - anchorPos.x, y + radius - anchorPos.y, radius);
		}
		else if (drawMode == TRIANGLE) {
			float triBase = width * 0.5;
			float triHeight = height;
			vec2 anchorPos = getAnchorPos(width, height);
			ofDrawTriangle(x + triBase - anchorPos.x, y - anchorPos.y, x - anchorPos.x, y + triHeight - anchorPos.y, x + triBase * 2 - anchorPos.x, y + triHeight - anchorPos.y);
		}
		else if (drawMode == TEXT) {
			vec2 anchorPos = getAnchorPos(width, height);
			ttf->drawString(strText, x - anchorPos.x, y + height - anchorPos.y);
		}
		else if (drawMode == TEXTURE) {
			vec2 anchorPos = getAnchorPos(width, height);
			texture->setAnchorPoint(anchorPos.x, anchorPos.y);
			if (drawSubsection.bState) {
				texture->drawSubsection(x, y, drawSubsection.width, drawSubsection.height, drawSubsection.x, drawSubsection.y, drawSubsection.width, drawSubsection.height);
			}
			else {
				texture->draw(x, y, width, height);
			}
		}
		else if (drawMode == IMAGE) {
			vec2 anchorPos = getAnchorPos(width, height);
			image->setAnchorPoint(anchorPos.x, anchorPos.y);
			if (drawSubsection.bState) {
				image->drawSubsection(x, y, drawSubsection.width, drawSubsection.height, drawSubsection.x, drawSubsection.y, drawSubsection.width, drawSubsection.height);
			}
			else {
				image->draw(x, y, width, height);
			}
		}
		else if (drawMode == FBO) {
			vec2 anchorPos = getAnchorPos(width, height);
			fbo->setAnchorPoint(anchorPos.x, anchorPos.y);
			fbo->draw(x, y, width, height);
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

vec2 ofxMotion::getPos(PosMode posMode) {
	float width = motionTransform->getWidth();
	float height = motionTransform->getHeight();
	vec2 anchorPos = getAnchorPos(width, height);

	vec2 pos = vec2(0, 0);
	if (posMode == POS_TOP_LEFT) {
		pos = motionTransform->getPos() - anchorPos;
	}
	else if (posMode == POS_TOP_RIGHT) {
		pos = motionTransform->getPos() - anchorPos + vec2(width, 0);
	}
	else if (posMode == POS_TOP_CENTER) {
		pos = motionTransform->getPos() - anchorPos + vec2(width * 0.5, 0);
	}
	else if (posMode == POS_BOTTOM_LEFT) {
		pos = motionTransform->getPos() - anchorPos + vec2(0, height);
	}
	else if (posMode == POS_BOTTOM_RIGHT) {
		pos = motionTransform->getPos() - anchorPos + vec2(width, height);
	}
	else if (posMode == POS_BOTTOM_CENTER) {
		pos = motionTransform->getPos() - anchorPos + vec2(width * 0.5, height);
	}
	else if (posMode == POS_LEFT_CENTER) {
		pos = motionTransform->getPos() - anchorPos + vec2(0, height * 0.5);
	}
	else if (posMode == POS_RIGHT_CENTER) {
		pos = motionTransform->getPos() - anchorPos + vec2(width, height * 0.5);
	}
	return pos;
}

ofxMotion::DirectionMode ofxMotion::getDirectionMode() const {
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

string ofxMotion::getText() {
	return strText;
}



void ofxMotion::setStateStateMotionTransform(MotionTransformBase::MotionState state) {
	motionTransform->setState(state);
}

void ofxMotion::setPos(vec2 pos) {
	motionTransform->setPos(pos);
}

void ofxMotion::setDirectionMode(DirectionMode mode) {
	directionMode = mode;
}

void ofxMotion::setMirrorMode(bool vertical, bool horizon) {
	image->mirror(vertical, horizon);
}

void ofxMotion::setAnchorMode(AnchorMode anchor) {
	this->anchor = anchor;
}

void ofxMotion::setImage(ofImage* image) {
	this->image = image;
}

void ofxMotion::setDrawSubsection(float sx, float sy, float sw, float sh) {
	drawSubsection.bState = true;
	drawSubsection.x = sx;
	drawSubsection.y = sy;
	drawSubsection.width = sw;
	drawSubsection.height = sh;
	motionTransform->setWidthHeight(sw, sh);
}

bool ofxMotion::insideRect(int x, int y) {
	if (!bStateInside) {
		return false;
	}
	return rectangle.inside(x, y);
}

bool ofxMotion::insideCircle(int x, int y) {
	if (!bStateInside) {
		return false;
	}
	float width = motionTransform->getWidth();
	float height = motionTransform->getHeight();
	float radius = width * 0.25 + height * 0.25;
	if (radius > ofDist(motionTransform->getPos().x, motionTransform->getPos().y, x, y)) {
		return true;
	}
	return false;
}

bool ofxMotion::collision(vec2 pos) {
	return rectangle.inside(pos.x, pos.y);
}

void ofxMotion::setStateInside(bool b) {
	bStateInside = b;
}

void ofxMotion::setStateDisplay(bool b) {
	bStateDisplay = b;
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

void ofxMotion::setText(string text) {
	strText = text;
}