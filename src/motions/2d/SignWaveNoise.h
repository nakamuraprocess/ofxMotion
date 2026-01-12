#pragma once
#include "MotionTransform2D.h"

namespace OFX_MOTION_2D {
	class SignWaveNoise : public MotionTransform2D {
	private:
		float timeRecently;
		glm::vec2 radius;
		float velocity;
		glm::vec2 posOffset;
		glm::vec2 posNoiseCursor;

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

		void startSignWaveNoise(glm::vec2 radius, float velociry, glm::vec2 posOffset, float duration) {
			posNoiseCursor = pos;
			this->radius = radius;
			velocity = velociry;
			this->posOffset = posOffset;
			parameter.startTime = currentTime;
			parameter.durationTime = duration;
			parameter.state = RUNNING;
		}
	};
}