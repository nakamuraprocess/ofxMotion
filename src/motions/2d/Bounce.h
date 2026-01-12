#pragma once
#include "MotionTransform2D.h"

namespace OFX_MOTION_2D {
	class Bounce : public MotionTransform2D {
	public:
		void update(const float currentTime) {
			this->currentTime = currentTime;
			if (parameter.state == RUNNING) {
				float time = timer(parameter.durationTime, currentTime, parameter.startTime, [&]() {
					parameter.state = DONE;
					});

				if (time < 0.15) {
					scale.y = ofxeasing::map_clamp(time, 0.0, 0.15, 1.0, 2.0, &ofxeasing::circ::easeIn);
				}
				else if (time >= 0.15 && time < 0.6) {
					scale.y = ofxeasing::map_clamp(time, 0.15, 0.6, 2.0, 1.0, &ofxeasing::elastic::easeOut);
				}

				width = widthInitial * scale.x;
				height = heightInitial * scale.y;
			}
		}

		void startBounce() {
			parameter.durationTime = 0.6;
			parameter.startTime = currentTime;
			parameter.state = RUNNING;
		}
	};
}