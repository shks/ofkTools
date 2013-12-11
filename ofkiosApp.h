#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

//ofkTools
#include "ofkMultiTouchEvent.h"
#include "ofkglImageRenderer.h"
//Addons
#include "ofxUI.h"
#include "ofxTweener.h"
#include "ofkXMLProperties.h"


class ofkiosApp : public ofxiPhoneApp{
	
    public:
        virtual void setup();
        virtual void update();
        virtual void draw();
        virtual void exit();
	
        virtual void touchDown(ofTouchEventArgs & touch);
        virtual void touchMoved(ofTouchEventArgs & touch);
        virtual void touchUp(ofTouchEventArgs & touch);
        virtual void touchDoubleTap(ofTouchEventArgs & touch);
        virtual void touchCancelled(ofTouchEventArgs & touch);

        virtual void lostFocus();
        virtual void gotFocus();
        virtual void gotMemoryWarning();
        virtual void deviceOrientationChanged(int newOrientation);

        virtual void touchTwoFinger ( ofkMultiTouchEventArgs &touch );
        ofkMultiTouchEvent multiTouchEvent;    
    
    // -------------------------- //
    
    /// ----------- Touch interactions ------------//
    bool isTouched;
    ofPoint mTouchPos;
    ofPoint mTouchPosEx;
    ofPoint mTouchDownPos;
    bool isRitghDragOneDirection;
    unsigned int mTouchOnTime;
    static const int TAP_THRESH = 800;

    
    // ------------ GUI event (Not Used) ----------//
    virtual void guiEvent(ofxUIEventArgs &e);
    
    
protected:
    virtual void initGUILayout();
    ofxUICanvas *guiCanvas;
    
private:
    
    ofxUILabel *label;
    
    enum WidgetState
    {
        WidgetOpened,
        WidgetClosed
    };
    
    WidgetState mWidgetState;
    float mGUISlidePos;
    bool isGUIWidgetActive();
    void changeWidgetState( WidgetState nextState );
  
    
    ofkglImageRenderer mSplashImage;
    ofkglImageRenderer mHelpImage;
    
    
};


