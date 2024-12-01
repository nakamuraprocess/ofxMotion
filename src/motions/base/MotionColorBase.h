#pragma once
#include "ofMain.h"
#include "ofxEasing.h"

using namespace glm;

class MotionColorBase {
public:
	// ColorGradation
	virtual void startColorGradation(float duration, ofColor colorEnd, ofxeasing::function easing) {}
	virtual void startColorGradation(float duration, ofColor colorStart, ofColor colorEnd, ofxeasing::function easing) {}

	// FadeInFadeOut
	virtual void startFadeInFadeOut(int startAlpha, int targetAlpha, float durationFadeIn, float durationChroma, float durationfadeOut, ofxeasing::function easing) {}
	virtual void startFadeOutForce(int alphaEnd, float durationfadeOut, ofxeasing::function easing) {}

	virtual void reset() {
		color = colorStart;
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

	void setup(ofColor color, ofColor colorInitial) {
		this->colorStart = this->color = color;
		this->colorInitial = colorInitial;
	}

	virtual void update(const float currentTime) {}

	ofColor getColor() const {
		return color;
	}

	ofColor getColorInitial() const {
		return colorInitial;
	}

	ofColor getcolorStart() const {
		return colorStart;
	}

	ofColor getcolorEnd() const {
		return colorEnd;
	}

	MotionState getState() const {
		return parameter.state;
	}

	MotionParameter getParameter() {
		return parameter;
	}

	void setColor(ofColor color) {
		this->color = color;
	}

	void setcolorStart(ofColor color) {
		colorStart = color;
	}

	void setcolorEnd(ofColor color) {
		colorEnd = color;
	}

	void setState(MotionState state) {
		parameter.state = state;
	}

	void setParameter(MotionParameter parameter) {
		this->parameter = parameter;
	}


protected:
	// color parameter
	ofColor color;
	ofColor colorInitial;
	ofColor colorStart;
	ofColor colorEnd;

	// for sub class.
	MotionParameter parameter;
};