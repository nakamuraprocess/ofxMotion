#pragma once
#include "MotionTransformBase.h"

class MoveCircle : public MotionTransformBase {
private:
	float radianInit;
	vec2 radius;

public:
	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			float radian = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, 0.0, TWO_PI, parameter.easing) + radianInit;

			pos.x = cos(radian) * radius.x + posInitial.x;
			pos.y = sin(radian) * radius.y + posInitial.y;
		}
	}

	void startMoveCircle(float radian, vec2 radius, float duration, ofxeasing::function easing) {
		radianInit = radian;
		this->radius = radius;
		parameter.startTime = ofGetElapsedTimef();
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};