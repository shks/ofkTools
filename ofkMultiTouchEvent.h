/*
 * ofxEventsAddon.h
 *
 *  Created on: 17-dic-2008
 *      Author: art
 */

#ifndef OFXEVENTSADDON_H_
#define OFXEVENTSADDON_H_

#include "ofMain.h"


/*
 PLEASE create this function in testApp class
 
 testAPp.h ________________
 
 void touchTwoFinger ( ofkMultiTouchEventArgs &touch );
 ofkMultiTouchEvent multiTouchEvent;

 testAPp.cpp ________________
 
 INSIDE [ void testApp :: setup() ] 

 multiTouchEvent.enable();
 ofAddListener(multiTouchEvent.touchTwoFingerEvent, this, &testApp::touchTwoFinger) ;
 
 ///
 void testApp :: touchTwoFinger ( ofkMultiTouchEventArgs &multiTouch )
 {
    //multiTouch.pinchLengthDif
    
 }
 ///
 
 */


class ofkMultiTouchEventArgs  : public ofEventArgs
{
public:
    int time;
    float angle;
    float pinchLength;
    float pinchLengthDif;
    float pinchLengthFromStart;
};

class ofkMultiTouchEvent{
    
public:
	ofkMultiTouchEvent(){
	}

	void enable(){
        //send touchDownEvent into touchDownMulti to check  multi touch Event
        ofAddListener(ofEvents.touchDown, this, &ofkMultiTouchEvent::touchDownMulti);     
        ofAddListener(ofEvents.touchMoved, this, &ofkMultiTouchEvent::touchMoveMulti);     
        ofAddListener(ofEvents.touchUp, this, &ofkMultiTouchEvent::touchUpMulti);     
	}

	void disable(){
        //remove touchDownEvent        
        ofRemoveListener(ofEvents.touchDown, this, &ofkMultiTouchEvent::touchDownMulti);     
        ofRemoveListener(ofEvents.touchMoved, this, &ofkMultiTouchEvent::touchMoveMulti);     
        ofRemoveListener(ofEvents.touchUp, this, &ofkMultiTouchEvent::touchUpMulti);     
	}

    void touchDownMulti(ofTouchEventArgs &touch);
    void touchMoveMulti(ofTouchEventArgs &touch);
    void touchUpMulti(ofTouchEventArgs &touch);
    
	ofEvent<ofkMultiTouchEventArgs> touchTwoFingerEvent;
    
private:
    
    void changeFingerNumber();
    
    const static int TOUCHNUMMAX = 5;
    ofVec2f mTouchPos[TOUCHNUMMAX];    
 
    ofVec2f mVecBetweenTwoFingerStart;
    ofVec2f mVecBetweenTwoFinger;
    ofVec2f mAvarageVector;
    
};

#endif /* OFXEVENTSADDON_H_ */
