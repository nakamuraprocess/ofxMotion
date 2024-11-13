#pragma once
#include "MotionTransformBase.h"

class MoveCircle : public MotionTransformBase {
private:
	float radianInit;
	vec2 radius;
	int direction = 1;
	bool bEndless;

public:
	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				if (bEndless) {
					parameter.startTime = currentTime;
				}
				else {
					parameter.state = DONE;
				}
				});

			float radian = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, 0.0, TWO_PI, parameter.easing) * direction + radianInit;

			pos.x = cos(radian) * radius.x + posInitial.x;
			pos.y = sin(radian) * radius.y + posInitial.y;
		}
	}

	void startMoveCircle(float radian, vec2 radius, float duration, int direction, float delay, ofxeasing::function easing, bool bEndless = false) {
		radianInit = radian;
		this->radius = radius;
		this->direction = direction;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
		this->bEndless = bEndless;
	}

	void startMoveCircle(vec2 pos, float radian, vec2 radius, float duration, int direction, float delay, ofxeasing::function easing, bool bEndless = false) {
		this->posInitial = pos;
		radianInit = radian;
		this->radius = radius;
		this->direction = direction;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
		this->bEndless = bEndless;
	}
};