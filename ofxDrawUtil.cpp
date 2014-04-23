#include "ofxDrawUtil.h"


#define SINCOS_PRECISION 2.0
#define SINCOS_LENGTH (int((360.0/SINCOS_PRECISION)))
float sinLUT[SINCOS_LENGTH];
float cosLUT[SINCOS_LENGTH];

bool ofxDrawUtil::_isInitialized = false;

void ofxDrawUtil::arcLineBars(float degStart, float deg, float r, float w)
{
	if(!_isInitialized)
	{
		//if initialized
		_init();
		_isInitialized = true;
	}

    int a = (int)(degStart/SINCOS_PRECISION) % (int)SINCOS_LENGTH;
    int b = (int)((degStart + deg)/SINCOS_PRECISION) % (int)SINCOS_LENGTH;

    ofEnableSmoothing();
    
    for (int i=a; i<b-1; i+=1) {
        
        ofBeginShape();
        ofVertex(cosLUT[i]*(r), sinLUT[i]*(r));
        ofVertex(cosLUT[i]*(r+w), sinLUT[i]*(r+w));
        ofVertex(cosLUT[i+1]*(r+w), sinLUT[i+1]*(r+w));
        ofVertex(cosLUT[i+1]*(r), sinLUT[i+1]*(r));
         ofEndShape();
    }
}

void ofxDrawUtil::_init()
{
    for (int i = 0; i < SINCOS_LENGTH; i++) {
        sinLUT[i]= (float)sin(i*DEG_TO_RAD*SINCOS_PRECISION);
        cosLUT[i]= (float)cos(i*DEG_TO_RAD*SINCOS_PRECISION);
	}
}
