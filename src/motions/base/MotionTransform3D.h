#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
#include "MotionBase.h"

class MotionTransform3D : public MotionBase {
public:
	void setup(glm::vec3 pos, glm::vec3 posInitial, glm::vec3 scale, float width, float height, float widthInitial, float heightInitial, float degrees) {
		this->pos = pos;
		this->posInitial = posInitial;
		this->scale = scale;
		this->width = widthInitial * scale.x;
		this->height = heightInitial * scale.y;
		this->widthInitial = widthInitial;
		this->heightInitial = heightInitial;
		this->degrees = degreesStart = degrees;
		if (degrees != 0.0f) this->bRotate = true;
	}

	virtual void update(const float currentTime) {}

	glm::vec3 getPos() {
		return pos;
	}

	glm::vec3 getPosInitial() {
		return posInitial;
	}

	glm::vec3 getPosStart() {
		return posStart;
	}

	glm::vec3 getPosEnd() {
		return posEnd;
	}

	float getWidth() const {
		return width;
	}

	float getHeight() const {
		return height;
	}

	float getWidthInitial() const {
		return widthInitial;
	}

	float getHeightInitial() const {
		return heightInitial;
	}

	glm::vec3 getScale() const {
		return scale;
	}

	bool isRotate() const {
		return bRotate;
	}

	float getDegrees() const {
		return degrees;
	}

	float getAnchorPosForRotation() const {
		return anchorPosForRotation;
	}

	MotionState getState() const {
		return parameter.state;
	}

	MotionParameter getParameter() {
		return parameter;
	}

	void setPos(glm::vec3 pos) {
		this->pos = pos;
	}

	void setPosStart(glm::vec3 pos) {
		posStart = pos;
	}

	void setPosEnd(glm::vec3 pos) {
		posEnd = pos;
	}

	void setState(MotionState state) {
		parameter.state = state;
	}

	void setParameter(MotionParameter parameter) {
		this->parameter = parameter;
	}

	void setWidthHeight(float w, float h) {
		width = w;
		height = h;
	}

	void setPosInitial() {
		pos = posInitial;
	}

	// MoveLiner
	virtual void startMoveLiner(glm::vec3 distance, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveLiner(glm::vec3 posStart, glm::vec3 posEnd, float duration, float delay, ofxeasing::function easing) {}



protected:
	// translate parameter
	glm::vec3 pos;
	glm::vec3 posInitial;
	glm::vec3 posStart;
	glm::vec3 posEnd;

	// scale parameter
	float width;
	float height;
	float widthInitial;
	float heightInitial;
	glm::vec3 scale;
	glm::vec3 scaleStart;
	glm::vec3 scaleEnd;

	// rotate parameter
	bool bRotate = false;
	float degrees;
	float degreesStart;
	float degreesEnd;
	float anchorPosForRotation;
};