#pragma once
#include "ofMain.h"
#include "ofxEasing.h"

using namespace glm;

class MotionTransformBase {
public:
	// Bounce
	virtual void start() {}

	// MoveLiner
	virtual void start(vec2 distance, float duration, float delay, ofxeasing::function easing) {}
	virtual void start(vec2 posStart, vec2 posEnd, float duration, float delay, ofxeasing::function easing) {}

	// MoveCurve
	virtual void start(vec2 distance, float radius, int direction, float duration, float delay, ofxeasing::function easing) {}
	virtual void start(vec2 posStart, vec2 posEnd, float radius, int direction, float duration, float delay, ofxeasing::function easing) {}

	// RadialNoise
	virtual void start(float radius, float velociry, vec2 posOffset, float duration) {}

	// Rotate
	virtual void start(float start, float target, float duration, ofxeasing::function easing) {}

	// Scale
	virtual void start(vec2 scaleEnd, float duration, ofxeasing::function easing) {}
	virtual void start(vec2 start, vec2 target, float duration, ofxeasing::function easing) {}

	virtual void reset() {
		pos = posStart;
		scale = scaleStart;
		degrees = degreesStart;
		parameter.state = IDLING;
	}

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

	void setup(vec2 pos, vec2 scale, float width, float height, float degrees) {
		this->pos = posStart = pos;
		this->scale = scaleStart = scale;
		this->width = width;
		this->height = height;
		this->degrees = degreesStart = degrees;
	}

	virtual void update(const float currentTime) {}


	string getName() const {
		return name;
	}

	vec2 getPos() {
		return pos;
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

	vec2 getScale() const {
		return scale;
	}

	float getDegrees() const {
		return degrees;
	}

	MotionState getState() const {
		return parameter.state;
	}

	MotionParameter getParameter() {
		return parameter;
	}

	void setPos(vec2 _pos) {
		pos = _pos;
	}

	void setposStart(vec2 pos) {
		posStart = pos;
	}

	void setposEnd(vec2 pos) {
		posEnd = pos;
	}

	void setState(MotionState state) {
		parameter.state = state;
	}

	void setParameter(MotionParameter _parameter) {
		parameter = _parameter;
	}


protected:
	string name;

	//translate parameter
	vec2 pos;
	vec2 posStart;
	vec2 posEnd;

	//scale parameter
	float width;
	float height;
	vec2 scale;
	vec2 scaleStart;
	vec2 scaleEnd;

	//rotate parameter
	float degrees;
	float degreesStart;
	float degreesEnd;

	//for sub class.
	MotionParameter parameter;
};