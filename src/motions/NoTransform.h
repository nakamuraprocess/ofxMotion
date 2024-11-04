#pragma once
#include "MotionTransformBase.h"

class NoTransform : public MotionTransformBase {
public:

	NoTransform(string str) {
		name = str;
	}
};