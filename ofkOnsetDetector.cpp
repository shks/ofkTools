//
//  ofkglImageRenderer.coo.cpp
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/07/01.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "ofkOnsetDetector.h"

#define BABYKICK (0.015463)
#define DEFAULT_ONSET_INTERVAL_THRESH (400)

ofkOnsetDetector::ofkOnsetDetector():
mIsActive(false)
{
    mOnsetThreshInterval = DEFAULT_ONSET_INTERVAL_THRESH;
}

void ofkOnsetDetector::update(ofVec3f acc)
{
    mAccDif = acc - mAccVec;
    mAccVec = acc;
    mRecogSignal = (abs(mAccDif.x) + abs(mAccDif.y) + abs(mAccDif.z)) / 3.0f;
    
    if(!mIsActive){
        return ;
    }
    
    //check Thresh
    //if(0.015463 < mRecogSignal)
    if(BABYKICK < mRecogSignal )
    {
        if(ofGetSystemTime() - mLastOnsetTime > mOnsetThreshInterval)
        {
            //WOW
            ofkOnsetEventArgs arg;
            arg.time = ofGetSystemTime();
            arg.signal = mRecogSignal;
            ofNotifyEvent(onsetEvent , arg , this);
            
            mLastOnsetTime = ofGetSystemTime();            
            
        }
    }
}

void ofkOnsetDetector::enable()
{
    mIsActive = true;
}

void ofkOnsetDetector::disable()
{
    
}

