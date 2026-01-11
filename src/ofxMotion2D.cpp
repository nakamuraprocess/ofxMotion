#include "ofxMotion2D.h"

void ofxMotion2D::setMotionTransformPtr(MotionTransform2D* ptr) {
	motionTransform = ptr;
}

void ofxMotion2D::setMotionColorPtr(MotionColor* ptr) {
	motionColor = ptr;
}

void ofxMotion2D::setup(DrawMode drawMode, glm::vec2 pos, glm::vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionColor->setup(color, color);
}

void ofxMotion2D::setup(DrawMode drawMode, ofImage* image, glm::vec2 pos, glm::vec2 scale, float width, float height, float degrees, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->image = image;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionColor->setup(ofColor(255), ofColor(255));
}

void ofxMotion2D::setup(DrawMode drawMode, ofTexture* texture, glm::vec2 pos, glm::vec2 scale, float width, float height, float degrees, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->texture = texture;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	motionTransform->setup(pos, pos, scale, width, height, width, height, degrees);
	motionColor->setup(ofColor(255), ofColor(255));
}

void ofxMotion2D::setup(DrawMode drawMode, ofTrueTypeFont* ttf, string strText, glm::vec2 pos, glm::vec2 scale, float degrees, ofColor color, AnchorMode anchor, int pointsInterpolatedMaxSize, bool bStateDisplay) {
	this->drawMode = drawMode;
	this->ttf = ttf;
	this->strText = strText;
	this->anchor = anchor;
	this->bStateDisplay = bStateDisplay;
	setPointsInterpolatedSize(pointsInterpolatedMaxSize);
	ofRectangle rectangle = ttf->getStringBoundingBox(strText, 0, 0);
	motionTransform->setup(pos, pos, scale, rectangle.getWidth(), rectangle.getHeight(), rectangle.getWidth(), rectangle.getHeight(), degrees);
	motionColor->setup(color, color);
}

void ofxMotion2D::setup(glm::vec2 pos, glm::vec2 scale, float width, float height) {
	this->drawMode = NONE;
	setPointsInterpolatedSize(0);
	motionTransform->setup(pos, pos, scale, width, height, width, height, 0.0);
	motionColor->setup(ofColor(0, 0), ofColor(0, 0));
}

void ofxMotion2D::update(const float currentTime) {
	motionTransform->update(currentTime);
	motionColor->update(currentTime);
	updateInterpolatedPoints();
}

void ofxMotion2D::draw() {
	if (motionTransform->getState() == MotionTransform2D::RUNNING || motionColor->getState() == MotionColor::RUNNING || bStateDisplay) {
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
			glm::vec2 anchorPos = getAnchorPos(width * 0.5 + height * 0.5, width * 0.5 + height * 0.5);
			ofDrawCircle(x + radius - anchorPos.x, y + radius - anchorPos.y, radius);
		}
		else if (drawMode == TRIANGLE) {
			float triBase = width * 0.5;
			float triHeight = height;
			glm::vec2 anchorPos = getAnchorPos(width, height);
			ofDrawTriangle(x + triBase - anchorPos.x, y - anchorPos.y, x - anchorPos.x, y + triHeight - anchorPos.y, x + triBase * 2 - anchorPos.x, y + triHeight - anchorPos.y);
		}
		else if (drawMode == TEXT) {
			glm::vec2 anchorPos = getAnchorPos(width, height);
			ttf->drawString(strText, x - anchorPos.x, y + height - anchorPos.y);
		}
		else if (drawMode == TEXTURE) {
			glm::vec2 anchorPos = getAnchorPos(width, height);
			texture->setAnchorPoint(anchorPos.x, anchorPos.y);
			if (drawSubsection.bState) {
				texture->drawSubsection(x, y, drawSubsection.width, drawSubsection.height, drawSubsection.x, drawSubsection.y, drawSubsection.width, drawSubsection.height);
			}
			else {
				texture->draw(x, y, width, height);
			}
		}
		else if (drawMode == IMAGE) {
			glm::vec2 anchorPos = getAnchorPos(width, height);
			image->setAnchorPoint(anchorPos.x, anchorPos.y);
			if (drawSubsection.bState) {
				image->drawSubsection(x, y, drawSubsection.width, drawSubsection.height, drawSubsection.x, drawSubsection.y, drawSubsection.width, drawSubsection.height);
			}
			else {
				image->draw(x, y, width, height);
			}
		}
		else if (drawMode == FBO) {
			glm::vec2 anchorPos = getAnchorPos(width, height);
			fbo->setAnchorPoint(anchorPos.x, anchorPos.y);
			fbo->draw(x, y, width, height);
		}
		ofPopMatrix();
		ofPopStyle();
	}
}

glm::vec2 ofxMotion2D::getAnchorPos(float width, float height) const {
	glm::vec2 anchorPos = glm::vec2(0, 0);
	if (anchor == ANCHOR_CENTER) {
		anchorPos = glm::vec2(width * 0.5, height * 0.5);
	}
	else if (anchor == ANCHOR_BOTTOM_CENTER) {
		anchorPos = glm::vec2(width * 0.5, height);
	}
	else if (anchor == ANCHOR_BOTTOM_LEFT) {
		anchorPos = glm::vec2(0, height);
	}
	else if (anchor == ANCHOR_BOTTOM_RIGHT) {
		anchorPos = glm::vec2(width, height);
	}
	else if (anchor == ANCHOR_TOP_LEFT) {
		anchorPos = glm::vec2(0, 0);
	}
	else if (anchor == ANCHOR_TOP_RIGHT) {
		anchorPos = glm::vec2(width, 0);
	}
	return anchorPos;
}

glm::vec2 ofxMotion2D::getPos() {
	return motionTransform->getPos();
}

glm::vec2 ofxMotion2D::getPoint(PointLocation pointLocation) {
	float width = motionTransform->getWidth();
	float height = motionTransform->getHeight();
	glm::vec2 anchorPos = getAnchorPos(width, height);

	glm::vec2 point = glm::vec2(0, 0);
	if (pointLocation == POINT_TOP_LEFT) {
		point = motionTransform->getPos() - anchorPos;
	}
	else if (pointLocation == POINT_TOP_RIGHT) {
		point = motionTransform->getPos() - anchorPos + glm::vec2(width, 0);
	}
	else if (pointLocation == POINT_BOTTOM_LEFT) {
		point = motionTransform->getPos() - anchorPos + glm::vec2(0, height);
	}
	else if (pointLocation == POINT_BOTTOM_RIGHT) {
		point = motionTransform->getPos() - anchorPos + glm::vec2(width, height);
	}
	return point;
}

MotionTransform2D::MotionState ofxMotion2D::getStateMotionTransform() {
	return motionTransform->getState();
}

MotionColor::MotionState ofxMotion2D::getStateMotionColor() {
	return motionColor->getState();
}

MotionTransform2D* ofxMotion2D::getMotionTransform() {
	return motionTransform;
}

MotionColor* ofxMotion2D::getMotionColor() {
	return motionColor;
}

string ofxMotion2D::getText() {
	return strText;
}

vector <glm::vec2> ofxMotion2D::getPointsInterpolated() {
	return pointsInterpolated;
}

void ofxMotion2D::setStateMotionTransform(MotionTransform2D::MotionState state) {
	motionTransform->setState(state);
}

void ofxMotion2D::setPos(glm::vec2 pos) {
	motionTransform->setPos(pos);
}

void ofxMotion2D::setMirrorMode(bool vertical, bool horizon) {
	image->mirror(vertical, horizon);
}

void ofxMotion2D::setAnchorMode(AnchorMode anchor) {
	this->anchor = anchor;
}

void ofxMotion2D::setImage(ofImage* image) {
	this->image = image;
}

void ofxMotion2D::setDrawSubsection(float sx, float sy, float sw, float sh) {
	drawSubsection.bState = true;
	drawSubsection.x = sx;
	drawSubsection.y = sy;
	drawSubsection.width = sw;
	drawSubsection.height = sh;
	motionTransform->setWidthHeight(sw, sh);
}

bool ofxMotion2D::insideRect(int x, int y) {
	return polyline.inside(x, y);
}

bool ofxMotion2D::insideCircle(int x, int y) {
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

bool ofxMotion2D::collision(glm::vec2 pos) {
	return polyline.inside(pos.x, pos.y);;
}

void ofxMotion2D::setStateInside(bool b) {
	bStateInside = b;
}

void ofxMotion2D::setStateDisplay(bool b) {
	bStateDisplay = b;
}

void ofxMotion2D::updateInterpolatedPoints() {
	polyline.clear();
	for (int i = 0; i < POINT_MAX_SIZE; i++) {
		PointLocation pointLocation = PointLocation(i);
		glm::vec2 tmpPos;
		float radianInit = atan2(getPoint(pointLocation).y - getPos().y, getPoint(pointLocation).x - getPos().x);
		float radianRotate = glm::radians(motionTransform->getDegrees()) + radianInit;
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

void ofxMotion2D::setText(string text) {
	strText = text;
}

void ofxMotion2D::setPointsInterpolatedSize(int size) {
	int maxSize = size + (int)POINT_MAX_SIZE;
	pointsInterpolated.assign(maxSize, glm::vec2(0, 0));
}