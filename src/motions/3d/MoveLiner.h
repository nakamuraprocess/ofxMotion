#pragma once
#include "MotionTransform3D.h"

namespace OFX_MOTION_3D {
	class MoveLiner : public MotionTransform3D {
	public:
		void update(const float currentTime) {
			this->currentTime = currentTime;
			if (parameter.state == RUNNING) {
				float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
					parameter.state = DONE;
					});

				pos.x = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.x, posEnd.x, parameter.easing);
				pos.y = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.y, posEnd.y, parameter.easing);
				pos.z = ofxeasing::map_clamp(time, 0.0, parameter.durationTime, posStart.z, posEnd.z, parameter.easing);
			}
		}

		void startMoveLiner(glm::vec3 distance, float duration, float delay, ofxeasing::function easing) {
			posStart = pos;
			posEnd = pos + distance;
			parameter.startTime = currentTime + delay;
			parameter.durationTime = duration;
			parameter.easing = easing;
			parameter.state = RUNNING;
		}

		void startMoveLiner(glm::vec3 posStart, glm::vec3 posEnd, float duration, float delay, ofxeasing::function easing) {
			this->posStart = posStart;
			this->posEnd = posEnd;
			parameter.startTime = currentTime + delay;
			parameter.durationTime = duration;
			parameter.easing = easing;
			parameter.state = RUNNING;
		}
	};
}