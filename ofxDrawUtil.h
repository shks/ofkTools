#pragma once

#include "ofMain.h"

class ofxDrawUtil
{
public:
	static void arcLineBars(float degStart, float deg, float r, float w);

private:

	static void _init();
	static bool _isInitialized;

};