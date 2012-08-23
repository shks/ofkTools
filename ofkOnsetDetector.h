//
//  ofkOnsetDetector.cpp
//  eventsExample
//
//  Created by Shunichi Kasahara on 12/07/01.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.


/*
 
 testAPp.h ________________
 
 void onSet ( ofkOnsetEventArgs &onset );
 ofkOnsetDetector onsetEvent;
 
 testAPp.cpp ________________
 
 INSIDE [ void testApp :: setup() ] 
 
 onsetEvent.enable();
 ofAddListener(onsetEvent.onsetEvent, this, &testApp::onSet) ;
 
 ///
 void testApp :: onSet ( ofkOnsetEventArgs &onset )
 {

 }
 ///

 
 */

#ifndef eventsExample_ofkOnsetDetector_h
#define eventsExample_ofkOnsetDetector_h

#include "ofMain.h"


class ofkOnsetEventArgs  : public ofEventArgs
{
public:
    int time;
    float signal;
};

class ofkOnsetDetector
{
public:
    ofkOnsetDetector();
    void update(ofVec3f acc);
    void enable();
    void disable();
    
    ofEvent<ofkOnsetEventArgs> onsetEvent;
    
    void setOnsetIntervalThresh(unsigned long intervalTime);
    
private:
    
    bool    mIsActive;
    
    unsigned long mOnsetThreshInterval;
    unsigned long mLastOnsetTime;
    
    ofVec3f mAccVec;
    ofVec3f mAccDif;
    float   mRecogSignal;
    
 };
#endif
