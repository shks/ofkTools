
#ifndef _ofkMultiTouchEvent_
#define _ofkMultiTouchEvent_

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
    float angleDif;
    float pinchLength;
    float pinchLengthDif;
    float pinchLengthFromStart;
    ofPoint centroidPos;
    ofPoint centroidPosDif;
};

class ofkMultiTouchEvent{
    
public:
	ofkMultiTouchEvent();
    
    //THIS FUNCTION can be override
    virtual void setTouchPos(int index, float x, float y);

	void enable(){
        //send touchDownEvent into touchDownMulti to check  multi touch Event

        ofAddListener(ofEvents().touchDown, this, &ofkMultiTouchEvent::touchDownMulti);
        ofAddListener(ofEvents().touchMoved, this, &ofkMultiTouchEvent::touchMoveMulti);
        ofAddListener(ofEvents().touchUp, this, &ofkMultiTouchEvent::touchUpMulti);
    }
    
	void disable(){
        //remove touchDownEvent
        ofRemoveListener(ofEvents().touchDown, this, &ofkMultiTouchEvent::touchDownMulti);
        ofRemoveListener(ofEvents().touchMoved, this, &ofkMultiTouchEvent::touchMoveMulti);     
        ofRemoveListener(ofEvents().touchUp, this, &ofkMultiTouchEvent::touchUpMulti);
        
	}

    virtual void touchDownMulti(ofTouchEventArgs &touch);
    virtual void touchMoveMulti(ofTouchEventArgs &touch);
    virtual void touchUpMulti(ofTouchEventArgs &touch);
    
	ofEvent<ofkMultiTouchEventArgs> touchTwoFingerEvent;
    
    void debugDraw();
    
protected:
    
    //calclate touch event and nofify event
    // this function is actually most important
    void calcAndNotifyTouchEvent();
    
    void changeFingerNumber();
    
    const static int TOUCHNUMMAX = 5;
    ofVec2f mTouchPos[TOUCHNUMMAX];  
    int mCurrentTouchPointNum;
 
    ofVec2f mVecBetweenTwoFingerStart;
    ofVec2f mVecBetweenTwoFinger;
    ofVec2f mAvarageVector;
    float mDegTwoFinger;

};

#endif /* OFXEVENTSADDON_H_ */
