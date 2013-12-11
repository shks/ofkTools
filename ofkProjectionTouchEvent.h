

#ifndef _ofkProjectionTouchEvent_
#define _ofkProjectionTouchEvent_

#include "ofMain.h"
#include "ofkARMatrixUtil.h"

/*
 PLEASE create this function in testApp class
 
 testAPp.h ________________
 
 void touchTwoFinger ( ofkMultiTouchEventArgs &touch );
 ofkMultiTouchEvent multiTouchEvent;

 testAPp.cpp ________________
 
 INSIDE [ void testApp :: setup() ] 

 multiTouchEvent.enable();
 ofAddListener(multiTouchEvent.touchTwoFingerEvent, this, &testApp::touchTwoFinger) ;
 
 void testApp :: touchTwoFinger ( ofkMultiTouchEventArgs &multiTouch )
 {
    
 }
 
 */


class ofkProjectionTouchEvent : public ofkMultiTouchEvent
{
public:
    
    //THIS FUNCTION can be override
    virtual void setTouchPos(int index, float x, float y)
    {
        ofPoint pos;
        pos.x = x;
        pos.y = y;
        
        if(index < 2)
        {
            //Store Original Touch Position
            frameBufferTouch[index] = pos;
        }
        
        ofVec3f propos = ofkARMatrixUtil::getProjectionPoint(pos,  modelViewMatrix,  projectoinMatrix);
        ofkMultiTouchEvent::setTouchPos(index, propos.x, propos.y);
        //calcAndNotifyTouchEvent();
    }
    void updateModelViewMatrix(ofMatrix4x4 mat)
    {
        modelViewMatrix = mat;
        
        if(2 == mCurrentTouchPointNum)
        {
            //Using stored frame buffer touch position
            setTouchPos(0, frameBufferTouch[0].x, frameBufferTouch[0].y);
            setTouchPos(1, frameBufferTouch[1].x, frameBufferTouch[1].y);
            calcAndNotifyTouchEvent();
        }
    }
    void updateProjectionMatrix(ofMatrix4x4 mat)
    {
        projectoinMatrix = mat;
    }
    
private:
    
    ofMatrix4x4 modelViewMatrix;
    ofMatrix4x4 projectoinMatrix;
    ofPoint frameBufferTouch[2];
    
    
};

#endif /* OFXEVENTSADDON_H_ */
