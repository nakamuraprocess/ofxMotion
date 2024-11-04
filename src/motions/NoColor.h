#pragma once
#include "MotionColorBase.h"

class NoColor : public MotionColorBase {
public:

	NoColor(string str) {
		name = str;
	}
};