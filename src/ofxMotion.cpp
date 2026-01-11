#include "ofxMotion.h"

void ofxMotion::setMotionTransformPtr(MotionTransformBase* ptr) {
	motionTransform = ptr;
}

void ofxMotion::setMotionColorPtr(MotionColorBase* ptr) {
	motionColor = ptr;
}

void ofxMotion::setup(DrawMode drawMode, vec2 pos, vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionTransform->setup();
	motionColor->setup(color, color);
}

void ofxMotion::setup(DrawMode drawMode, ofImage* image, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->image = image;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionTransform->setup();
	motionColor->setup(ofColor(255), ofColor(255));
}

void ofxMotion::setup(DrawMode drawMode, ofTexture* texture, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->texture = texture;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionTransform->setup();
	motionColor->setup(ofColor(255), ofColor(255));
}

void ofxMotion::setup(DrawMode drawMode, ofTrueTypeFont* ttf, string strText, vec2 pos, vec2 scale, float degrees, ofColor color, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->ttf = ttf;
	this->strText = strText;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	ofRectangle rectangle = ttf->getStringBoundingBox(strText, 0, 0);
	motionTransform->setup(pos, pos, scale, rectangle.getWidth(), rectangle.getHeight(), rectangle.getWidth(), rectangle.getHeight(), degrees);
	motionTransform->setup();
	motionColor->setup(color, color);
}

void ofxMotion::setup(vec2 pos, vec2 scale, float width, float height) {
	this->drawMode = NONE;
	setPointsInterpolatedSize(0);
	motionTransform->setup(pos, pos, scale, width, height, width, height, 0.0);
	motionTransform->setup();
	motionColor->setup(ofColor(0, 0), ofColor(0, 0));
}

void ofxMotion::update(const float currentTime) {
	motionTransform->update(currentTime);
	motionColor->update(currentTime);
	updateInterpolatedPoints();
}

void ofxMotion::draw() {
	if (motionTransform->getState() == MotionTransformBase::RUNNING || motionColor->getState() == MotionColorBase::RUNNING || bStateDisplay) {
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
		float drawRectangleX = getPoint(POINT_TOP_LEFT).x;
		float drawRectangleY = getPoint(POINT_TOP_LEFT).y;
		float width = motionTransform->getWidth();
		float height = motionTransform->getHeight();

		if (motionTransform->isRotate()) {
			if (drawMode == IMAGE || drawMode == TEXTURE || drawMode == FBO) {
				ofSetRectMode(OF_RECTMODE_CORNER);
			}
			else {
				ofSetRectMode(OF_RECTMODE_CENTER);
			}
			ofTranslate(motionTransform->getPos());
			ofRotateDeg(motionTransform->getDegrees());
			x = drawRectangleX = motionTransform->getAnchorPosForRotation();
			y = drawRectangleY = motionTransform->getAnchorPosForRotation();
		}

		if (drawMode == RECT) {
			ofDrawRectangle(drawRectangleX, drawRectangleY, width, height);
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

vec2 ofxMotion::getPoint(PointLocation pointLocation) {
	float width = motionTransform->getWidth();
	float height = motionTransform->getHeight();
	vec2 anchorPos = getAnchorPos(width, height);

	vec2 point = vec2(0, 0);
	if (pointLocation == POINT_TOP_LEFT) {
		point = motionTransform->getPos() - anchorPos;
	}
	else if (pointLocation == POINT_TOP_RIGHT) {
		point = motionTransform->getPos() - anchorPos + vec2(width, 0);
	}
	else if (pointLocation == POINT_BOTTOM_LEFT) {
		point = motionTransform->getPos() - anchorPos + vec2(0, height);
	}
	else if (pointLocation == POINT_BOTTOM_RIGHT) {
		point = motionTransform->getPos() - anchorPos + vec2(width, height);
	}
	return point;
}

MotionTransformBase::MotionState ofxMotion::getStateMotionTransform() {
	return motionTransform->getState();
}

MotionColorBase::MotionState ofxMotion::getStateMotionColor() {
	return motionColor->getState();
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

vector <vec2> ofxMotion::getPointsInterpolated() {
	return pointsInterpolated;
}

void ofxMotion::setStateMotionTransform(MotionTransformBase::MotionState state) {
	motionTransform->setState(state);
}

void ofxMotion::setPos(vec2 pos) {
	motionTransform->setPos(pos);
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
	return polyline.inside(x, y);
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
	return polyline.inside(pos.x, pos.y);;
}

void ofxMotion::setStateInside(bool b) {
	bStateInside = b;
}

void ofxMotion::setStateDisplay(bool b) {
	bStateDisplay = b;
}

void ofxMotion::updateInterpolatedPoints() {
	polyline.clear();
	for (int i = 0; i < POINT_MAX_SIZE; i++) {
		PointLocation pointLocation = PointLocation(i);
		vec2 tmpPos;
		float radianInit = atan2(getPoint(pointLocation).y - getPos().y, getPoint(pointLocation).x - getPos().x);
		float radianRotate = radians(motionTransform->getDegrees()) + radianInit;
		float radius = distance(getPos(), getPoint(pointLocation));
		tmpPos.x = cos(radianRotate) * radius;
		tmpPos.y = sin(radianRotate) * radius;
		pointsRotated[i] = tmpPos + getPos();
		polyline.addVertex(pointsRotated[i].x, pointsRotated[i].y);
		pointsInterpolated[i] = pointsRotated[i];
	}
	polyline.close();

	for (int i = 4; i < pointsInterpolated.size(); i++) {
		float percent = float(i) / (pointsInterpolated.size() - 1);
		pointsInterpolated[i] = polyline.getPointAtPercent(percent);
	}
}

void ofxMotion::setText(string text) {
	strText = text;
}

void ofxMotion::setPointsInterpolatedSize(int size) {
	int maxSize = size + (int)POINT_MAX_SIZE;
	pointsInterpolated.assign(maxSize, vec2(0, 0));
}