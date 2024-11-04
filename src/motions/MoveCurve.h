#pragma once
#include "MotionTransformBase.h"

class MoveCurve : public MotionTransformBase {
private:
	int direction = 1;
	float radius;
	float radian = 0.0;


public:
	MoveCurve(string str) {
		name = str;
	}

	void update(const float currentTime) {
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			pos.x = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.x, posEnd.x, parameter.easing);
			pos.y = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.y, posEnd.y, parameter.easing);
			radian = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, 0.0, PI, parameter.easing);

			float theta = PI / 2.0;
			vec2 targetDirection = normalize(posEnd - posStart);
			vec2 normalizeDirection = vec2(targetDirection.x * cos(theta) - targetDirection.y * sin(theta), targetDirection.x * sin(theta) + targetDirection.y * cos(theta));
			normalizeDirection = normalize(normalizeDirection);
			pos += sin(radian) * radius * normalizeDirection * direction;
		}
	}

	void start(vec2 distance, float radius, int direction, float duration, float delay, ofxeasing::function easing) {
		posStart = pos;
		this->radius = radius;
		this->direction = direction;
		posEnd = pos + distance;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}

	void start(vec2 posStart, vec2 posEnd, float radius, int direction, float duration, float delay, ofxeasing::function easing) {
		posStart = posStart;
		this->posEnd = posEnd;
		this->radius = radius;
		this->direction = direction;
		parameter.startTime = ofGetElapsedTimef() + delay;
		parameter.durationTime = duration;
		parameter.easing = easing;
		parameter.state = RUNNING;
	}
};