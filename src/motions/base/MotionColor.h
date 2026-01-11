#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
#include "MotionBase.h"

class MotionColor : public MotionBase {
public:
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

	ofColor getColorStart() const {
		return colorStart;
	}

	ofColor getColorEnd() const {
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

	virtual void reset() {
		color = colorStart;
		parameter.state = IDLING;
	}

	// ColorGradation
	virtual void startColorGradation(ofColor colorEnd, float duration, ofxeasing::function easing) {}
	virtual void startColorGradation(ofColor colorStart, ofColor colorEnd, float duration, ofxeasing::function easing) {}

	// FadeInFadeOut
	virtual void startFadeInFadeOut(int startAlpha, int targetAlpha, float durationFadeIn, float durationChroma, float durationfadeOut, ofxeasing::function easing) {}
	virtual void startFadeOutForce(int alphaEnd, float durationfadeOut, ofxeasing::function easing) {}


protected:
	// color parameter
	ofColor color;
	ofColor colorInitial;
	ofColor colorStart;
	ofColor colorEnd;
};