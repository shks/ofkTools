//
//  MultiTouchEvent.cpp
//  advancedEventsExample
//
//  Created by Shunichi Kasahara on 12/03/22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "ofkMultiTouchEvent.h"


ofkMultiTouchEvent::ofkMultiTouchEvent():mCurrentTouchPointNum(0)
{
    
}

void ofkMultiTouchEvent::setTouchPos(int index, float x, float y)
{
    //CHECK VAILED TOUCH NUM
    if(index< TOUCHNUMMAX)
    {
        mTouchPos[index].x = x;
        mTouchPos[index].y = y;        
    }
}

void ofkMultiTouchEvent::touchDownMulti(ofTouchEventArgs &touch)
{
    mCurrentTouchPointNum = touch.numTouches;

    /*
    string mes = "ofTouchEventArgs event: id" + ofToString(touch.id) + "in " + ofToString(mCurrentTouchPointNum) + " pos" + ofToString(touch.x);
    cout << mes << "\n";
    */
    
    //CHECK VAILED TOUCH NUM
    if(touch.id < TOUCHNUMMAX)
    {
        setTouchPos(touch.id,touch.x, touch.y);
        //mTouchPos[touch.id].x = touch.x;
        //mTouchPos[touch.id].y = touch.y;        
    }
    
    //2 FINEGR
    if(1 == touch.id)
    {
        //when 2 finger interaction start  
        //initialize two finger diference vector 
        mVecBetweenTwoFingerStart = mVecBetweenTwoFinger = mTouchPos[1] - mTouchPos[0];        
        //init average vector
        mAvarageVector = ( mTouchPos[1] + mTouchPos[0] ) / 2.0f;
        
        ofVec3f Diffvec =  ( mTouchPos[1] - mTouchPos[0] );
        mDegTwoFinger = -180.0f * ((float)atan(Diffvec.y / Diffvec.x)) / PI;        
    }    
}

void ofkMultiTouchEvent::touchMoveMulti(ofTouchEventArgs &touch)
{        
    mCurrentTouchPointNum = touch.numTouches;
    
    //CHECK VAILED TOUCH NUM
    //THIS WILL BECAME BUG 
    if(touch.id < TOUCHNUMMAX)
    {
        setTouchPos(touch.id,touch.x, touch.y);  
    }
    
    if(2 == touch.numTouches)
    {
        calcAndNotifyTouchEvent();
    }
}

void ofkMultiTouchEvent::touchUpMulti(ofTouchEventArgs &touch)
{        
    mCurrentTouchPointNum = touch.numTouches;  
    
}

void ofkMultiTouchEvent::calcAndNotifyTouchEvent()
{
    
    ofVec2f updateBetweenVector;
    updateBetweenVector = mTouchPos[1] - mTouchPos[0];
    
    ofVec3f Diffvec =  ( mTouchPos[1] - mTouchPos[0] );
    float updateAngle = -180.0f * ((float)atan(Diffvec.y / Diffvec.x)) / PI;
    
    //this is new update two finger ave point;
    ofVec2f updateTwoFingerAve = ( mTouchPos[1] + mTouchPos[0] ) / 2.0f;
    
    ofkMultiTouchEventArgs arg;
    arg.time = ofGetSystemTimeMicros();
    
    if(updateAngle - mDegTwoFinger > 150)
    {
        arg.angleDif = (updateAngle -180 - mDegTwoFinger) ;
    }
    else if(updateAngle - mDegTwoFinger < -150)
    {
        arg.angleDif = updateAngle + 180 - mDegTwoFinger;
    }
    else
    {
        arg.angleDif = updateAngle  - mDegTwoFinger;
    }
    
    /*
    string mes = "ANGEL DIF" + ofToString(arg.angleDif);
    cout << mes << "\n";
    */
    
    arg.angle = updateAngle;
    arg.pinchLength = (updateBetweenVector).length();
    arg.pinchLengthDif = updateBetweenVector.length() - mVecBetweenTwoFinger.length();
    arg.pinchLengthFromStart = updateBetweenVector.length() - mVecBetweenTwoFingerStart.length();
    arg.centroidPosDif = (updateTwoFingerAve - mAvarageVector);
    arg.centroidPos = mAvarageVector = updateTwoFingerAve;
    ofNotifyEvent(touchTwoFingerEvent , arg , this);
    
    mVecBetweenTwoFinger = updateBetweenVector;
    mDegTwoFinger = updateAngle;
}

void ofkMultiTouchEvent::debugDraw()
{
    ofPushMatrix();
    ofPushStyle();
    ofSetupScreen();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableSmoothing();
    
    if(2 == mCurrentTouchPointNum)
    {
        ofSetColor(255,25,100,20);
        //REDNER PINCH CIRCLE
        ofVec3f Centvec =  ( mTouchPos[1] + mTouchPos[0] ) / 2.0;
        ofCircle(Centvec.x, Centvec.y, ( mTouchPos[1] - mTouchPos[0] ).length() / 2);      
        
        ofSetColor(255,25,100,50);
        ofVec3f Diffvec =  ( mTouchPos[1] - mTouchPos[0] );
        ofLine(mTouchPos[1].x, mTouchPos[1].y, mTouchPos[0].x, mTouchPos[0].y);
        
        ofSetColor(255,100,100,50);
        string str;
        str = "angle " + ofToString(mDegTwoFinger);
        ofDrawBitmapString(str, Centvec);
        
        //ave finger pos rendering 
        ofSetColor(25,100, 255, 20);
        ofCircle(mAvarageVector.x, mAvarageVector.y, 30);      

    }
        
    //RENDER TWO FINGER ANGLE
    ofPopStyle();
    ofPopMatrix();

}