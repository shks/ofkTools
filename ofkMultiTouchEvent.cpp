//
//  MultiTouchEvent.cpp
//  advancedEventsExample
//
//  Created by 俊一 笠原 on 12/03/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofkMultiTouchEvent.h"

void ofkMultiTouchEvent::touchDownMulti(ofTouchEventArgs &touch)
{
    
    string mes = "ofTouchEventArgs event: id" + ofToString(touch.id) + "pos" + ofToString(touch.x);
    cout << mes << "\n";
    
    //CHECK VAILED TOUCH NUM
    if(touch.id < TOUCHNUMMAX)
    {
        mTouchPos[touch.id].x = touch.x;
        mTouchPos[touch.id].y = touch.y;        
    }
    
    //2 FINEGR
    if(1 == touch.id)
    {
        //when 2 finger interaction start  
        //initialize two finger diference vector 
        mVecBetweenTwoFingerStart = mVecBetweenTwoFinger = mTouchPos[1] - mTouchPos[0];        
        //init average vector
        mAvarageVector = ( mTouchPos[1] + mTouchPos[0] ) / 2.0f;
        
        cout << "2 FINEGR event" << "\n"; 
    }
    
    //3 FINGER
    /*
    if(2 == touch.id)
    {
        //when 3 finger interaction start  
        //init average vector
        mAvarageVector = ( mTouchPos[2] + mTouchPos[1] + mTouchPos[0] ) / 3.0f;
        
        cout << "3 FINEGR event" << "\n";
    }*/
    
}

void ofkMultiTouchEvent::touchMoveMulti(ofTouchEventArgs &touch)
{        
    //CHECK VAILED TOUCH NUM
    //THIS WILL BECAME BUG 
    if(touch.id < TOUCHNUMMAX)
    {
        mTouchPos[touch.id].x = touch.x;
        mTouchPos[touch.id].y = touch.y;        
    }
    
    if(2 == touch.numTouches)
    {
        ofVec2f updateBetweenVector;
        //WHEN we tracking 2 finger
        
        updateBetweenVector = mTouchPos[1] - mTouchPos[0];
        
        ofkMultiTouchEventArgs arg;
        arg.time = ofGetSystemTimeMicros();
        arg.angle = 0;
        arg.pinchLength = (updateBetweenVector).length();
        arg.pinchLengthDif = updateBetweenVector.length() - mVecBetweenTwoFinger.length();
        arg.pinchLengthFromStart = updateBetweenVector.length() - mVecBetweenTwoFingerStart.length();
        
        ofNotifyEvent(touchTwoFingerEvent , arg , this);
        
        mVecBetweenTwoFinger = updateBetweenVector;
    }
}

void ofkMultiTouchEvent::touchUpMulti(ofTouchEventArgs &touch)
{        
   
    
}