#pragma once
#include "MotionTransformBase.h"
#include "MoveLiner.h"
#include "Rotate.h"
#include "Scale.h"

class MoveLinerRotateScale : public MotionTransformBase {
public:
	void setup() {
		moveLiner.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
		rotateTo.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
		scaleTo.setup(pos, posInitial, scale, width, height, widthInitial, heightInitial, degrees);
	}

	void update(const float currentTime) {
		moveLiner.update(currentTime);
		rotateTo.update(currentTime);
		scaleTo.update(currentTime);

		pos = moveLiner.getPos();
		degrees = rotateTo.getDegrees();
		width = widthInitial * scaleTo.getScale().x;
		height = heightInitial * scaleTo.getScale().y;
	}

	void startMoveLiner(vec2 distance, float duration, float delay, ofxeasing::function easing) {
		moveLiner.startMoveLiner(distance, duration, delay, easing);
	}

	void startRotate(float distance, float anchorPosForRotation, float duration, ofxeasing::function easing) {
		rotateTo.startRotate(distance, anchorPosForRotation, duration, easing);
	}

	void startScale(vec2 scaleEnd, float duration, float delay, ofxeasing::function easing) {
		scaleTo.startScale(scaleEnd, duration, delay, easing);
	}

private:
	MoveLiner moveLiner;
	Rotate rotateTo;
	Scale scaleTo;
};