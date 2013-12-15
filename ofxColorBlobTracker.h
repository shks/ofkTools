//
//  ofxColorBlobTracker.h
//  Created by Shunichi Kasahara on 12/16/13.
//
//

#ifndef __opencvExample__ofxColorBlobTracker__
#define __opencvExample__ofxColorBlobTracker__

#include "ofMain.h"

#include "ofxOpenCv.h"
#include <opencv/highgui.h>
#include <opencv/cv.h>
/*
 
libs file path.
../../../addons/ofxOpenCv/libs/opencv/lib/osx/opencv.a
 
 
for header search path...
 
 ../../../addons/ofxOpenCv/libs ../../../addons/ofxOpenCv/libs/opencv ../../../addons/ofxOpenCv/libs/opencv/include ../../../addons/ofxOpenCv/libs/opencv/include/opencv ../../../addons/ofxOpenCv/libs/opencv/include/opencv2 ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/calib3d ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/contrib ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/core ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/features2d ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/flann ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/gpu ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/highgui ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/imgproc ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/legacy ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/ml ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/objdetect ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/ts ../../../addons/ofxOpenCv/libs/opencv/include/opencv2/video ../../../addons/ofxOpenCv/libs/opencv/lib ../../../addons/ofxOpenCv/libs/opencv/lib/linuxarmv6l ../../../addons/ofxOpenCv/libs/opencv/lib/linuxarmv7l ../../../addons/ofxOpenCv/libs/opencv/lib/osx ../../../addons/ofxOpenCv/src src
 */

class HSBColor {
public:
	float hue, sat, bri;
	ofVec2f pos;
};

class ofxColorBlobTracker
{
    
public:
    void init(int width, int height);
    void update(ofPixelsRef pixelRef);
    void draw();
    
    void setTrackColor(HSBColor col);
    HSBColor pickupColor(int x, int y);
    void mousePressed(int x, int y);

    bool isTrack;
    ofPoint pos;
    
private:
    
    // TODO tracking tolerance
    
    int camWidth;
	int camHeight;
    
	ofxCvColorImage colorImg;
	ofxCvColorImage colorImgHSV;
    
	ofxCvGrayscaleImage hueImg;
	ofxCvGrayscaleImage satImg;
	ofxCvGrayscaleImage briImg;
    
	ofxCvGrayscaleImage reds;
    
    //Tracking Color
	HSBColor one;
    
    //Boolena pixel similar then 255
	unsigned char * colorTrackedPixelsRed;
    
    //Binary Image
	ofTexture trackedTextureRed;
    
	ofxCvContourFinder finderRed;
};


#endif /* defined(__opencvExample__ofxColorBlobTracker__) */
