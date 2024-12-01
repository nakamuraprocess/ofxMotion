#pragma once
#include "ofMain.h"
#include "ofxEasing.h"

using namespace glm;

class MotionTransformBase {
public:
	// Bounce
	virtual void startBounce() {}

	// MoveCircle
	virtual void startMoveCircle(float radian, vec2 radius, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveCircle(vec2 pos, float radian, vec2 radius, float duration, float delay, ofxeasing::function easing) {}

	// MoveLiner
	virtual void startMoveLiner(vec2 distance, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveLiner(vec2 posStart, vec2 posEnd, float duration, float delay, ofxeasing::function easing) {}

	// MoveRadial
	virtual void startMoveRadial(float radian, vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveRadial(float radian, vec2 radiusStart, vec2 radiusEnd, float duration, float delay, ofxeasing::function easing) {}

	// MoveCurve
	virtual void startMoveCurve(vec2 distance, float radius, float duration, float delay, ofxeasing::function easing) {}
	virtual void startMoveCurve(vec2 posStart, vec2 posEnd, float radius, float duration, float delay, ofxeasing::function easing) {}

	// SignWaveNoise
	virtual void startSignWaveNoise(vec2 radius, float velociry, vec2 posOffset, float duration) {}

	// Rotate
	virtual void startRotate(float degreesEnd, float anchorPosForRotation, float duration, ofxeasing::function easing) {}
	virtual void startRotate(float start, float target, float anchorPosForRotation, float duration, ofxeasing::function easing) {}

	// Scale
	virtual void startScale(vec2 scaleEnd, float duration, float delay, ofxeasing::function easing) {}
	virtual void startScale(vec2 start, vec2 target, float duration, float delay, ofxeasing::function easing) {}

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

	void setup(vec2 pos, vec2 posInitial, vec2 scale, float width, float height, float widthInitial, float heightInitial, float degrees) {
		this->pos = posStart = pos;
		this->posInitial = posInitial;
		this->scale = scaleStart = scale;
		this->width = width * scale.x;
		this->height = height * scale.y;
		this->widthInitial = widthInitial;
		this->heightInitial = heightInitial;
		this->degrees = degreesStart = degrees;
		if (degrees != 0.0f) this->bRotate = true;
	}

	virtual void update(const float currentTime) {}

	vec2 getPos() {
		return pos;
	}

	vec2 getPosInitial() {
		return posInitial;
	}

	vec2 getposStart() {
		return posStart;
	}

	vec2 getposEnd() {
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

	vec2 getScale() const {
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

	void setPos(vec2 pos) {
		this->pos = pos;
	}

	void setPosStart(vec2 pos) {
		posStart = pos;
	}

	void setPosEnd(vec2 pos) {
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


protected:
	// translate parameter
	vec2 pos;
	vec2 posInitial;
	vec2 posStart;
	vec2 posEnd;

	// scale parameter
	float width;
	float height;
	float widthInitial;
	float heightInitial;
	vec2 scale;
	vec2 scaleStart;
	vec2 scaleEnd;

	// rotate parameter
	bool bRotate = false;
	float degrees;
	float degreesStart;
	float degreesEnd;
	float anchorPosForRotation;

	// for sub class.
	MotionParameter parameter;
};