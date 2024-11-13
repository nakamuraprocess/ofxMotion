#pragma once
#include "MotionTransformBase.h"
#include "MotionColorBase.h"
#include "Bounce.h"
#include "ColorGradation.h"
#include "FadeInFadeOut.h"
#include "MoveCircle.h"
#include "MoveLiner.h"
#include "MoveCurve.h"
#include "DefaultColor.h"
#include "DefaultTransform.h"
#include "RadialNoise.h"
#include "Rotate.h"
#include "Scale.h"

class ofxMotion  {
public:
	enum DrawMode {
		RECT = 0,
		CIRCLE = 1,
		TRIANGLE = 2,
		IMAGE = 3,
		TEXTURE = 4,
		TEXT = 5
	};

	enum AnchorMode {
		ANCHOR_CENTER = 0,
		ANCHOR_BOTTOM_CENTER = 1,
		ANCHOR_TOP_LEFT = 2,
		ANCHOR_TOP_RIGHT = 3,
		ANCHOR_BOTTOM_LEFT = 4,
		ANCHOR_BOTTOM_RIGHT = 5,
	};

	enum DirectionMode {
		LEFT = 0,
		RIGHT = 1,
		TOP = 2,
		BOTTOM = 3,
		TOP_LEFT = 4,
		TOP_RIGHT = 5,
		BOTTOM_LEFT = 6,
		BOTTOM_RIGHT = 7,
	};

	void setMotionTransformPtr(MotionTransformBase* ptr);
	void setMotionColorPtr(MotionColorBase* ptr);

	void setup(DrawMode drawMode, vec2 pos, vec2 scale, float width, float height, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay = false);
	void setup(DrawMode drawMode, ofImage* image, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, bool bStateDisplay = false);
	void setup(DrawMode drawMode, ofTexture* texture, vec2 pos, vec2 scale, float width, float height, float degrees, AnchorMode anchor, bool bStateDisplay = false);
	void setup(DrawMode drawMode, ofTrueTypeFont* ttf, string strText, vec2 pos, vec2 scale, float degrees, ofColor color, AnchorMode anchor, bool bStateDisplay = false);
	void update(const float currentTime);
	void draw();

	vec2 getPos();
	ofRectangle getRectangle();
	DirectionMode getDirectionMode();
	MotionTransformBase::MotionState getStateMotionTransform();
	MotionColorBase::MotionState getStateMotionColor();
	MotionTransformBase* getMotionTransform();
	MotionColorBase* getMotionColor();

	void setStateStateMotionTransform(MotionTransformBase::MotionState state);
	void setPosMotionTransform(vec2 pos);
	void setDirectionMode(DirectionMode mode);
	void setMirrorMode(bool vertical, bool horizon);
	void setAnchorMode(AnchorMode anchor);
	void setImage(ofImage* image);
	void setDrawSubsection(float sx, float sy, float sw, float sh);
	bool insideRect(int x, int y);
	bool insideCircle(int x, int y);
	bool collision(int x, int y);
	void setStateInside(bool b);
	void setStateDisplay(bool b);
	

private:
	MotionTransformBase* motionTransform = nullptr;
	MotionColorBase* motionColor = nullptr;
	MotionTransformBase::MotionState stateTransform;
	MotionColorBase::MotionState stateColor;
	bool bStateDisplay = false;
	bool bStateInside = true;
	DrawMode drawMode;
	ofRectangle rectangle;
	AnchorMode anchor;
	DirectionMode directionMode;
	ofImage* image = nullptr;
	ofTexture* texture = nullptr;
	ofTrueTypeFont* ttf = nullptr;
	string strText = "";
	
	vec2 getAnchorPos(float width, float height) const;
	void setRect(float x, float y, float width, float height);

	struct DrawSubsection {
		bool bState;
		float x;
		float y;
		float width;
		float height;
	}drawSubsection;

};