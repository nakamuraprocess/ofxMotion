#pragma once
#include "MotionTransformBase.h"

class SignWaveNoise : public MotionTransformBase {
private:
	float timeRecently;
	vec2 radius;
	float velocity;
	vec2 posOffset;
	vec2 posNoiseCursor;

public:
	void update(const float currentTime) {
		this->currentTime = currentTime;
		if (parameter.state == RUNNING) {
			float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
				parameter.state = DONE;
				});

			float timeDestination = currentTime - timeRecently;
			timeDestination = ofClamp(timeDestination, 0.0, 0.1);
			timeRecently = currentTime;

			posNoiseCursor += velocity * timeDestination;
			pos.x = ofSignedNoise(posNoiseCursor.x) * radius.x + posOffset.x;
			pos.y = ofSignedNoise(posNoiseCursor.y) * radius.y + posOffset.y;
		}
	}

	void startSignWaveNoise(vec2 radius, float velociry, vec2 posOffset, float duration) {
		posNoiseCursor = pos;
		this->radius = radius;
		velocity = velociry;
		this->posOffset = posOffset;
		parameter.startTime = currentTime;
		parameter.durationTime = duration;
		parameter.state = RUNNING;
	}
};