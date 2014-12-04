#pragma once

#include "ofMain.h"
#include "opencv2/opencv.hpp"
#include "ofxCvUtilities.h"

/*
 //as is function
 */
 
class ofxImagePreProcess : public ofBaseApp{

public:
	void setup();
	void update(const cv::UMat & src, cv::UMat & dst);
    void draw(float w, float h);

    void calcHist(const cv::UMat & mat);

    
    // - - - - - - - - For Module API private member- - - -
private:

public:
    // - - - - - - GUI Optical FLow control - - - - - - //

    cv::UMat mUMat;
    cv::UMat mMaskOperated;
    cv::UMat mMaskOperatedAndDym;
    
    cv::UMat difMat;
    cv::UMat difMatBinary;
    
    bool isInitial;
    cv::UMat tempFilteredDifMat;
    cv::UMat regionMask;
};

