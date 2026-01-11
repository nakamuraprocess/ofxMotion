#pragma once
#include "MotionTransformBase.h"

class MoveCircle : public MotionTransformBase {
private:
	float radianInit;
	glm::vec2 radius;

public:
	void update(const float currentTime) {
		this->currentTime = currentTime;
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
					parameter.state = DONE;
				});

			float radian = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, 0.0, TWO_PI, parameter.easing) + radianInit;

			pos.x = cos(radian) * radius.x + posInitial.x;
			pos.y = sin(radian) * radius.y + posInitial.y;
		}
	}

	void startMoveCircle(float radian, glm::vec2 radius, float duration, float delay, ofxeasing::function easing) {
		radianInit = radian;
		this->radius = radius;
		parameter.startTime = currentTime + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void startMoveCircle(glm::vec2 pos, float radian, glm::vec2 radius, float duration, float delay, ofxeasing::function easing) {
		this->posInitial = pos;
		radianInit = radian;
		this->radius = radius;
		parameter.startTime = currentTime + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};