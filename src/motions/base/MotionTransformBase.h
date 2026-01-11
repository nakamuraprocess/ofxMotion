#pragma once
#include "ofMain.h"
#include "ofxEasing.h"

class MotionTransformBase {
public:
	enum MotionState {
		IDLING = 0,
		RUNNING = 1,
		DONE = 2
	};

	struct MotionParameter {
		float startTime;
		float durationTime;
		MotionState state = IDLING;
		ofxeasing::function easing;
	};

	float timer(const float duration, const float currentTime, const float startTime, function<void()> const callback) {
		float time = currentTime - startTime;
		time = ofClamp(time, 0.0, duration);
		if (time == duration) {
			callback();
		}
		return time;
	}

	void setup(glm::vec2 pos, glm::vec2 posInitial, glm::vec2 scale, float width, float height, float widthInitial, float heightInitial, float degrees) {
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

	//virtual void setup() {}

	virtual void update(const float currentTime) {}

	glm::vec2 getPos() {
		return pos;
	}

	glm::vec2 getPosInitial() {
		return posInitial;
	}

	glm::vec2 getPosStart() {
		return posStart;
	}

	glm::vec2 getPosEnd() {
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

	glm::vec2 getScale() const {
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

	void setPos(glm::vec2 pos) {
		this->pos = pos;
	}

	void setPosStart(glm::vec2 pos) {
		posStart = pos;
	}

	void setPosEnd(glm::vec2 pos) {
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


	// Bounce
	virtual void startBounce() {}

	// MoveCircle
	virtual void startMoveCircle(float radian, glm::vec2 radius, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveCircle(glm::vec2 pos, float radian, glm::vec2 radius, float duration, float delay, ofxeasing::function easing) {}

	// MoveLiner
	virtual void startMoveLiner(glm::vec2 distance, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveLiner(glm::vec2 posStart, glm::vec2 posEnd, float duration, float delay, ofxeasing::function easing) {}

	// MoveRadial
	virtual void startMoveRadial(float radian, glm::vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveRadial(float radian, glm::vec2 radiusStart, glm::vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {}

	// MoveCurve
	virtual void startMoveCurve(glm::vec2 distance, float radius, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveCurve(glm::vec2 posStart, glm::vec2 posEnd, float radius, float duration, float delay, ofxeasing::function easing) {}

	// SignWaveNoise
	virtual void startSignWaveNoise(glm::vec2 radius, float velociry, glm::vec2 posOffset, float duration) {}

	// Rotate
	virtual void startRotate(float degreesEnd, float anchorPosForRotation, float duration, ofxeasing::function easing) {}
	virtual void startRotate(float start, float target, float anchorPosForRotation, float duration, ofxeasing::function easing) {}

	// Scale
	virtual void startScale(glm::vec2 scaleEnd, float duration, float delay, ofxeasing::function easing) {}
	virtual void startScale(glm::vec2 start, glm::vec2 target, float duration, float delay, ofxeasing::function easing) {}


protected:
	float currentTime = 0.0;

	// translate parameter
	glm::vec2 pos;
	glm::vec2 posInitial;
	glm::vec2 posStart;
	glm::vec2 posEnd;

	// scale parameter
	float width;
	float height;
	float widthInitial;
	float heightInitial;
	glm::vec2 scale;
	glm::vec2 scaleStart;
	glm::vec2 scaleEnd;

	// rotate parameter
	bool bRotate = false;
	float degrees;
	float degreesStart;
	float degreesEnd;
	float anchorPosForRotation;

	// for sub class.
	MotionParameter parameter;
};